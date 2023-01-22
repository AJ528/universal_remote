/*
 * IR_lib.c
 *
 *  Created on: Jan 12, 2023
 *      Author: adevries
 */

#include "IR_lib.h"
#include "timer.h"
#include "SPI.h"

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//#include <string.h>

static void append_bits(uint8_t *output, uint16_t *output_index,
                        uint8_t *output_bit_index, const uint8_t *input,
                        uint16_t input_bit_len);

static void shift_in_byte(uint8_t *output, uint16_t *output_index,
                             uint8_t *out_bit_index, uint8_t pattern,
                             uint8_t pat_len);

int16_t format_sony20_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                           const struct command *cmd, bool is_ditto)
{
    const struct protocol *protocol_used = cmd->device->prot_used;
    const struct stream_char *cur_char;
    const uint32_t SMCLK_freq = CS_getSMCLK();

    if(is_ditto)
        cur_char = &(protocol_used->ditto_stream);
    else
        cur_char = &(protocol_used->primary_stream);

    //set up carrier freq and SPI timing
    stop_carrier_wave();
    enable_carrier_wave(SMCLK_freq, protocol_used->carrier_freq);

    disable_SPI();
    set_unit_freq(SMCLK_freq, protocol_used->unit_freq);

    uint16_t output_buf_index = 0;
    uint8_t output_bit_index = 8;

    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_in, cur_char->lead_in_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->function, cmd->function_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->device, cmd->device->device_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->subdevice, cmd->device->subdevice_len);
//    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_out, cur_char->lead_out_len);

//    uint8_t buffer[] = {0xf6, 0xb5, 0xaa, 0xd6, 0xd6, 0xab, 0x6c}; //left-most 55 bits

//    memcpy(output_buffer, buffer, sizeof(buffer));
//    output_buf_index = sizeof(buffer);

//    lead-in   0x1e            5 bits
//    func      0x01 0xad 0x6a  17 bits
//    dev       0x16 0xb6       13 bits
//    subdev    0x0b 0x55 0xb6  20 bits



    output_buf_index++;
    output_buffer[output_buf_index] = 0x00;


    return (output_buf_index + 1);
}

int16_t format_NEC_command(uint8_t *output_buffer, uint16_t output_buffer_size,
                           const struct command *cmd, bool is_ditto)
{
    const struct protocol *protocol_used = cmd->device->prot_used;
    const struct stream_char *cur_char;
    const uint32_t SMCLK_freq = CS_getSMCLK();

    if(is_ditto)
        cur_char = &(protocol_used->ditto_stream);
    else
        cur_char = &(protocol_used->primary_stream);

    //set up carrier freq and SPI timing
    stop_carrier_wave();
    enable_carrier_wave(SMCLK_freq, protocol_used->carrier_freq);

    disable_SPI();
    set_unit_freq(SMCLK_freq, protocol_used->unit_freq);

    uint16_t output_buf_index = 0;
    uint8_t output_bit_index = 8;

    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_in, cur_char->lead_in_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->device, cmd->device->device_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->subdevice, cmd->device->subdevice_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->function, cmd->function_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_out, cur_char->lead_out_len);

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

