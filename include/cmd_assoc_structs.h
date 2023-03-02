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

struct cmd_container{
    void *action;
    enum action_type type;
};

//sp_cmd = short-press command
//lp_cmd = long-press command
struct btn_assoc{
    struct cmd_container sp_cmd;
    struct cmd_container lp_cmd;
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

extern const struct command SB_PWR_TOG;
extern const struct command SB_VLUP;
extern const struct command SB_VLDN;
extern const struct command SB_MUTE;
extern const struct command SB_SOURCE;


extern const struct command BR_PWR_TOG;
extern const struct command BR_PWR_ON;
extern const struct command BR_PWR_OFF;
extern const struct command BR_PLAY;
extern const struct command BR_PAUSE;
extern const struct command BR_STOP;
extern const struct command BR_NEXT;
extern const struct command BR_PREV;
extern const struct command BR_UP;
extern const struct command BR_DOWN;
extern const struct command BR_LEFT;
extern const struct command BR_RIGHT;
extern const struct command BR_SELECT;
extern const struct command BR_SUBTITLE;
extern const struct command BR_EJECT;

extern const struct command SH_PWR_TOG;
extern const struct command SH_HL_TOG;
extern const struct command SH_OSC;

extern const struct command TV_PWR_TOG;
extern const struct command TV_PWR_ON;
extern const struct command TV_PWR_OFF;
extern const struct command TV_SOURCE;
extern const struct command TV_INPUT_HDMI1;
extern const struct command TV_INPUT_HDMI2;
extern const struct command TV_INPUT_HDMI3;
extern const struct command TV_UP;
extern const struct command TV_DOWN;
extern const struct command TV_SELECT;

extern const struct command SAM_TV_PWR_TOG;

extern const struct cmd_seq watch_CC;
extern const struct cmd_seq MASTER_OFF;

#endif /* INCLUDE_CMD_PROT_STRUCTS_H_ */
