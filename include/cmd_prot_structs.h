/*
 * cmd_prot_structs.h
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_CMD_PROT_STRUCTS_H_
#define INCLUDE_CMD_PROT_STRUCTS_H_

#include <stdbool.h>
#include <stdint.h>

struct command{
    uint8_t function[8];
    uint8_t function_len;
    const struct device *device;
};

typedef int16_t format_func(uint8_t *, uint16_t, const struct command *, bool);

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
    uint8_t lead_in[5];
    uint8_t lead_in_len;
    uint8_t lead_out[5];
    uint8_t lead_out_len;
};

struct protocol{
    uint16_t carrier_freq;
    uint16_t unit_freq;
    bool LSB;
    bool has_ditto;
    struct stream_char primary_stream;
    struct stream_char ditto_stream;
    format_func *fmt_func;
};

extern const struct command SB_PWR;
extern const struct command SB_test;

extern const struct command BR_PWR;

#endif /* INCLUDE_CMD_PROT_STRUCTS_H_ */
