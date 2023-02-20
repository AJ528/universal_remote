/*
 * cmd_prot_structs.h
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_CMD_PROT_STRUCTS_H_
#define INCLUDE_CMD_PROT_STRUCTS_H_

#include "device_protocol_structs.h"

#include <stdbool.h>
#include <stdint.h>

enum action_type{
    command,
    cmd_seq
};

struct btn_assoc{
    void *action;
    enum action_type type;
};

struct cmd_seq{
    struct command const *const *sequence;
    uint8_t sequence_len;
};

struct command{
    uint8_t function[8];
    uint8_t function_len;
    const struct device *device;
};

extern const struct btn_assoc btn_0x00;
extern const struct btn_assoc btn_0x04;
extern const struct btn_assoc btn_0x05;
extern const struct btn_assoc btn_0x06;
extern const struct btn_assoc btn_0x0C;
extern const struct btn_assoc btn_0x0D;
extern const struct btn_assoc btn_0x0E;
extern const struct btn_assoc btn_0x10;
extern const struct btn_assoc btn_0x12;
extern const struct btn_assoc btn_0x17;
extern const struct btn_assoc btn_0x1F;
extern const struct btn_assoc btn_0x20;
extern const struct btn_assoc btn_0x22;
extern const struct btn_assoc btn_0x27;


#endif /* INCLUDE_CMD_PROT_STRUCTS_H_ */
