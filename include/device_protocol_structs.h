/*
 * device_protocol_structs.h
 *
 *  Created on: Feb 5, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_DEVICE_PROTOCOL_STRUCTS_H_
#define INCLUDE_DEVICE_PROTOCOL_STRUCTS_H_

#include <stdint.h>
#include <stdbool.h>

struct command; //defined in cmd

//stream characteristics
struct stream_char{
    uint16_t extent_ms;
    uint8_t lead_in[5];
    uint8_t lead_in_len;
    uint8_t lead_out[5];
    uint8_t lead_out_len;
};

typedef int16_t format_func(uint8_t *, uint16_t, const struct stream_char *, const struct command *, bool);

struct protocol{
    uint16_t carrier_freq;
    uint16_t unit_freq;
    bool LSB;
    bool has_ditto;
    struct stream_char primary_stream;
    struct stream_char ditto_stream;
    format_func *fmt_func;
};

struct device{
    uint8_t device[4];
    uint8_t device_len;
    uint8_t subdevice[4];
    uint8_t subdevice_len;
    const struct protocol *prot_used;
};

extern const struct device toshiba_tv;
extern const struct device work_samsung_tv;
extern const struct device soundbar;
extern const struct device bluray;
extern const struct device space_heater;
extern const struct protocol NEC1;
extern const struct protocol NEC2;
extern const struct protocol NECx2;
extern const struct protocol sony20;
extern const struct protocol space_heater_protocol;

#endif /* INCLUDE_DEVICE_PROTOCOL_STRUCTS_H_ */
