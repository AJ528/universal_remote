/*
 * IR_lib.c
 *
 *  Created on: Jan 12, 2023
 *      Author: adevries
 */


#include "IR_lib.h"
#include "timer.h"
#include "SPI.h"
#include "GPIO.h"
#include "cmd_assoc_structs.h"
#include "device_protocol_structs.h"

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define LONG_PRESS_THRESH   150
#define OUTPUT_BUF_SIZE     32

uint8_t output_buf[OUTPUT_BUF_SIZE] = {0};

uint8_t TXData_index = 0;
uint16_t TXData_size;

static struct command const *prev_cmd = 0;

static bool button_is_long_pressed(uint16_t button_num);
static void append_bits(uint8_t *output, uint16_t *output_index,
                        uint8_t *output_bit_index, const uint8_t *input,
                        uint16_t input_bit_len);

static void shift_in_byte(uint8_t *output, uint16_t *output_index,
                             uint8_t *out_bit_index, uint8_t pattern,
                             uint8_t pat_len);
static void clear_buffer(uint8_t *buffer, uint16_t size);

int16_t handle_button_assoc(struct btn_assoc const *assoc, uint16_t button_num)
{
    //if assoc has an entry for a long-press
    //start a timer
    //check to see if button remains pressed for time T
    //if button is released before T seconds, execute short press
    //else, execute long press after T seconds
    //spam command as long as button is held down

    bool lp_result = false;
    //if a long-press command action exists
    if(assoc->lp_cmd.action != 0){
        lp_result = button_is_long_pressed(button_num);
    }

    if(lp_result){
        while(scan_for_pressed_button() == button_num){
            handle_cmd_container(&(assoc->lp_cmd));
        }
        reset_prev_cmd();
        return (0);
    }else if(assoc->sp_cmd.action != 0){
        return handle_cmd_container(&(assoc->sp_cmd));
    }else
        return (0);
}

static bool button_is_long_pressed(uint16_t button_num)
{
    bool button_remains_pressed = true;

    start_10ms_inc_timer(LONG_PRESS_THRESH);

    while(!timer_expired()){
        if(scan_for_pressed_button() != button_num)
            button_remains_pressed = false;
    }

    return button_remains_pressed;
}

int16_t handle_cmd_container(struct cmd_container const *container)
{
    struct cmd_seq const *cmd_seq_to_execute;
    struct command const *cmd_to_execute;
    uint8_t iteration_limit = 1;
    uint8_t i = 0;

    if(container->type == cmd_seq){
        cmd_seq_to_execute = (struct cmd_seq const *)container->action;
        iteration_limit = cmd_seq_to_execute->sequence_len;
        cmd_to_execute = cmd_seq_to_execute->sequence[0];
    }else{
        cmd_to_execute = (struct command const *)container->action;
    }

    while(i < iteration_limit){
        if(cmd_to_execute == prev_cmd)
            execute_command(cmd_to_execute, true);
        else
            execute_command(cmd_to_execute, false);

        prev_cmd = cmd_to_execute;
        i++;
        if(container->type == cmd_seq)
            cmd_to_execute = cmd_seq_to_execute->sequence[i];
    }

    return (0);
}

void reset_prev_cmd(void)
{
    prev_cmd = 0;
}

int16_t execute_command(const struct command *cmd, bool is_ditto)
{
    const struct protocol *protocol_used = cmd->device->prot_used;
    const struct stream_char *cur_char;
    const uint32_t SMCLK_freq = CS_getSMCLK();
    uint16_t extent;

    if(is_ditto){
        if(protocol_used->has_ditto == true){
            cur_char = &(protocol_used->ditto_stream);
            extent = cmd->device->prot_used->ditto_stream.extent_ms;
        }else{
            cur_char = &(protocol_used->primary_stream);
            extent = cmd->device->prot_used->primary_stream.extent_ms;
        }
    }else{
        cur_char = &(protocol_used->primary_stream);
        extent = cmd->device->prot_used->primary_stream.extent_ms;
    }

    //set up carrier freq and SPI timing
    stop_carrier_wave();
    enable_carrier_wave(SMCLK_freq, protocol_used->carrier_freq);

    disable_SPI();
    set_unit_freq(SMCLK_freq, protocol_used->unit_freq);


    int16_t result = protocol_used->fmt_func(output_buf, OUTPUT_BUF_SIZE, cur_char, cmd, is_ditto);

    if(result < 0)
        return result;

    if(extent != 0)
        start_extent_timer(extent);
    else
        set_timer_expired();

    TXData_size = result;
    TXData_index = 0;
    enable_SPI();
    enable_SPI_int();

    //enter LPM0 and wait for command to execute
    __bis_SR_register(LPM0_bits);

    clear_buffer(output_buf, TXData_size);

    if(timer_expired() == false){
        //enter LPM3 and wait for the extent time period to pass
        __bis_SR_register(LPM3_bits);
    }

    return (0);
}

int16_t format_sony20_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                              const struct stream_char *cur_char,
                              const struct command *cmd, bool is_ditto)
{
    uint16_t output_buf_index = 0;
    uint8_t output_bit_index = 8;

    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_in, cur_char->lead_in_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->function, cmd->function_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->device, cmd->device->device_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->subdevice, cmd->device->subdevice_len);
//    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_out, cur_char->lead_out_len);

    output_buf_index++;
    output_buffer[output_buf_index] = 0x00;


    return (output_buf_index + 1);
}

int16_t format_NEC1_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                           const struct stream_char *cur_char,
                           const struct command *cmd, bool is_ditto)
{
    uint16_t output_buf_index = 0;
    uint8_t output_bit_index = 8;

    append_bits(output_buffer, &output_buf_index, &output_bit_index,
                cur_char->lead_in, cur_char->lead_in_len);
    if(is_ditto == false){
        append_bits(output_buffer, &output_buf_index, &output_bit_index,
                    cmd->device->device, cmd->device->device_len);
        append_bits(output_buffer, &output_buf_index, &output_bit_index,
                    cmd->device->subdevice, cmd->device->subdevice_len);
        append_bits(output_buffer, &output_buf_index, &output_bit_index,
                    cmd->function, cmd->function_len);
    }
    append_bits(output_buffer, &output_buf_index, &output_bit_index,
                cur_char->lead_out, cur_char->lead_out_len);

    output_buf_index++;
    output_buffer[output_buf_index] = 0x00;

    return (output_buf_index + 1);
}

int16_t format_NEC2_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                           const struct stream_char *cur_char,
                           const struct command *cmd, bool is_ditto)
{
    uint16_t output_buf_index = 0;
    uint8_t output_bit_index = 8;

    append_bits(output_buffer, &output_buf_index, &output_bit_index,
                cur_char->lead_in, cur_char->lead_in_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index,
                cmd->device->device, cmd->device->device_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index,
                cmd->device->subdevice, cmd->device->subdevice_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index,
                cmd->function, cmd->function_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index,
                cur_char->lead_out, cur_char->lead_out_len);

    output_buf_index++;
    output_buffer[output_buf_index] = 0x00;

    return (output_buf_index + 1);
}

int16_t format_space_heater_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                              const struct stream_char *cur_char,
                              const struct command *cmd, bool is_ditto)
{
    uint16_t output_buf_index = 0;
    uint8_t output_bit_index = 8;

    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_in, cur_char->lead_in_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->device, cmd->device->device_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->function, cmd->function_len);

    output_buf_index++;
    output_buffer[output_buf_index] = 0x00;


    return (output_buf_index + 1);
}

static void append_bits(uint8_t *output, uint16_t *output_index,
                        uint8_t *output_bit_index, const uint8_t *input,
                        uint16_t input_bit_len)
{
    uint8_t i = 0;

    for(i = 0; i < (input_bit_len / 8); i++){

        shift_in_byte(output, output_index, output_bit_index, input[i], 8);
    }
    uint8_t remainder = input_bit_len % 8;
    if(remainder != 0)
        shift_in_byte(output, output_index, output_bit_index, input[i],
                      remainder);
}

//this function assumes that it can write to the next byte after output
static void shift_in_byte(uint8_t *output, uint16_t *output_index,
                             uint8_t *out_bit_index, uint8_t pattern,
                             uint8_t pat_len)
{
    uint8_t working_pattern = pattern;
    uint8_t pattern_len = pat_len;

next_byte:
    //if the pattern will fit entirely in the working byte
    if(*out_bit_index >= pattern_len){
        *(output + *output_index) += (working_pattern >> (8 - *out_bit_index));
        *out_bit_index = *out_bit_index - pattern_len;

        if(*out_bit_index == 0){
            *out_bit_index = 8;
            (*output_index)++;
        }
    }else{
        *(output + *output_index) += (working_pattern >> (8 - *out_bit_index));
        pattern_len = pattern_len - *out_bit_index;
        working_pattern = (working_pattern << *out_bit_index);

        *out_bit_index = 8;
        (*output_index)++;
        goto next_byte;
    }
}

static void clear_buffer(uint8_t *buffer, uint16_t size)
{
    uint16_t i = size;
    while(i > 0){
        *(buffer + i - 1) = 0;
        i--;
    }
}


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch(__even_in_range(UCA0IV, USCI_SPI_UCTXIFG))
    {
        case USCI_SPI_UCTXIFG:      // UCTXIFG

            if(TXData_index == TXData_size){
                disable_SPI();
                disable_SPI_int();
                stop_carrier_wave();
                __bic_SR_register_on_exit(LPM0_bits);
            }else{
                UCA0TXBUF = ~(output_buf[TXData_index]);
            }

            if(TXData_index < TXData_size)
                TXData_index++;

            break;
        default:
            break;
    }
}
