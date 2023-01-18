/*
 * IR_lib.c
 *
 *  Created on: Jan 12, 2023
 *      Author: adevries
 */

#include "IR_lib.h"

#include "driverlib.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

static int16_t format_NEC_command(uint8_t *output_buffer, uint16_t *output_buffer_size,
                           const struct command *cmd, bool is_ditto);

const struct protocol NEC =
{
 .carrier_freq = 38000,
 .unit_freq = 1773,
 .LSB = true,
 .has_ditto = false,
 .bin_enc =
 {
  .zero_encoding = {1, -1},
  .zero_enc_len = 2,
  .one_encoding = {1, -3},
  .one_enc_len = 2
 },
 .primary_stream =
 {
  .extent_ms = 0,
  .lead_in = {0xff, 0xff, 0x00},
  .lead_in_len = 24,
  .lead_out = {0x01},
  .lead_out_len = 1
 },
 .fmt_func = format_NEC_command
};

const struct device soundbar =
{
 .device = {0xAA, 0xAA},
 .device_len = 16,
 .subdevice = {0x88, 0x88, 0x88, 0x88},
 .subdevice_len = 32,
 .prot_used = &NEC
};

const struct command PB_PWR =
{
 .function = {0xAA, 0xA8, 0xA2, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

static void append_bits(uint8_t *output, uint16_t *output_index,
                        uint8_t *output_bit_index, const uint8_t *input,
                        uint16_t input_bit_len);

static void shift_in_byte(uint8_t *output, uint16_t *output_index,
                             uint8_t *out_bit_index, uint8_t pattern,
                             uint8_t pat_len);

static int16_t format_NEC_command(uint8_t *output_buffer, uint16_t *output_buffer_size,
                           const struct command *cmd, bool is_ditto)
{
    const struct protocol *protocol_used = cmd->device->prot_used;
    const struct stream_char *cur_char;
    const uint16_t max_buffer_size = *output_buffer_size;

    if(is_ditto)
        cur_char = &(protocol_used->ditto_stream);
    else
        cur_char = &(protocol_used->primary_stream);


    //set up carrier freq and SPI timing

    uint16_t output_buf_index = 0;
    uint8_t output_bit_index = 8;

    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_in, cur_char->lead_in_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->device, cmd->device->device_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->device->subdevice, cmd->device->subdevice_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cmd->function, cmd->function_len);
    append_bits(output_buffer, &output_buf_index, &output_bit_index, cur_char->lead_out, cur_char->lead_out_len);


    *output_buffer_size = output_buf_index + 1;

    return (0);

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
        *out_bit_index = *out_bit_index - pattern_len;
        *(output + *output_index) += (working_pattern << *out_bit_index);

        if(*out_bit_index == 0){
            *out_bit_index = 8;
            (*output_index)++;
        }
    }else{
        pattern_len = pattern_len - *out_bit_index;
        *(output + *output_index) += (working_pattern >> pattern_len);
        working_pattern = (working_pattern & ((0x01 << pattern_len) - 1));

        *out_bit_index = 8;
        (*output_index)++;
        goto next_byte;
    }
}


static int16_t convert_to_SPI_envelope(uint8_t *output_buffer,
                                       uint16_t output_buffer_size,
                                       uint16_t *output_buffer_index,
                                       uint8_t *output_bit_index,
                                       const uint8_t *input_data,
                                       uint16_t input_data_len,
                                       const struct binary_encoding *encoding);


static void create_pattern(uint16_t *pattern, uint8_t *pattern_len,
                           const int8_t *encoding, uint8_t enc_len);

static void create_pattern(uint16_t *pattern, uint8_t *pattern_len,
                           const int8_t *encoding, uint8_t enc_len)
{
    *pattern = 0;
    *pattern_len = 0;

    uint16_t local_pattern = 0;
    uint8_t local_pattern_len = 0;

    if(enc_len == 0)
        return;

    uint8_t i = 0;

    while(i < enc_len){

        if(encoding[i] != 0){
            bool is_positive = (encoding[i] > 0);
            uint8_t j = abs(encoding[i]);

            local_pattern = local_pattern << j;
            local_pattern_len += j;
            if(is_positive)
                local_pattern += (0x01 << j) - 1;
        }
        i++;
    }

    *pattern_len = local_pattern_len;
    *pattern = local_pattern;
}


static int16_t convert_to_SPI_envelope(uint8_t *output_buffer,
                                       uint16_t output_buffer_size,
                                       uint16_t *output_buffer_index,
                                       uint8_t *output_bit_index,
                                       const uint8_t *input_data,
                                       uint16_t input_data_len,
                                       const struct binary_encoding *encoding)
{
    uint16_t input_data_index = 0;

    uint16_t zero_pattern = 0;
    uint8_t zero_pat_len = 0;

    create_pattern(&zero_pattern, &zero_pat_len, encoding->zero_encoding,
                   encoding->zero_enc_len);

    uint16_t one_pattern = 0;
    uint8_t one_pat_len = 0;

    create_pattern(&one_pattern, &one_pat_len, encoding->one_encoding,
                   encoding->one_enc_len);

    while(input_data_index < input_data_len){
        uint8_t in_bit_index = 0;
        uint8_t working_number = input_data[input_data_index];

        while(in_bit_index < 8){

            if(*output_buffer_index > output_buffer_size - 2)
                return (-1);

            if(*output_bit_index == 0){
                *output_bit_index = 8;
                (*output_buffer_index)++;
            }

            if(working_number & 0x80){
                //shift one pattern in
                shift_in_byte(output_buffer, output_buffer_index,
                                 output_bit_index, one_pattern, one_pat_len);
            }else{
                //shift zero pattern in
                shift_in_byte(output_buffer, output_buffer_index,
                                 output_bit_index, zero_pattern, zero_pat_len);
            }
            working_number = working_number << 1;
            in_bit_index++;
        }
        input_data_index++;
    }
    return (0);
}
