/*
 * IR_lib.h
 *
 *  Created on: Jan 12, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_IR_LIB_H_
#define INCLUDE_IR_LIB_H_

#include <stdint.h>
#include <stdbool.h>

struct command{
    uint8_t function[8];
    uint8_t function_len;
    const struct device *device;
};

typedef int16_t format_func(uint8_t *, uint16_t *, const struct command *, bool);

struct device{
    uint8_t device[4];
    uint8_t device_len;
    uint8_t subdevice[4];
    uint8_t subdevice_len;
    const struct protocol *prot_used;
};

//stream characteristics
struct stream_char{
    uint8_t extent_ms;
    int8_t lead_in[5];
    uint8_t lead_in_len;
    int8_t lead_out[5];
    uint8_t lead_out_len;
};

/*
 * limit encoding array such that SUM(abs(encoding_arr[i])) <= 16
 */

struct binary_encoding{
    int8_t zero_encoding[5];
    uint8_t zero_enc_len;
    int8_t one_encoding[5];
    uint8_t one_enc_len;
};

struct protocol{
    uint16_t carrier_freq;
    uint16_t unit_freq;
    bool LSB;
    bool has_ditto;
    struct binary_encoding bin_enc;
    struct stream_char primary_stream;
    struct stream_char ditto_stream;
    format_func *fmt_func;
};

//extern const struct protocol NEC;
extern const struct command PB_PWR;


#endif /* INCLUDE_IR_LIB_H_ */
