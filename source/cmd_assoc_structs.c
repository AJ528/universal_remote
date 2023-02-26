/*
 * cmd_prot_structs.c
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#include "cmd_assoc_structs.h"
#include "device_protocol_structs.h"

/*
 * Command Sequences
 */

static struct command const *const watch_CC_seq[] =
{
 &TV_PWR_ON,
 &SB_PWR_TOG
};

const struct cmd_seq watch_CC =
{
 .sequence = watch_CC_seq,
 .sequence_len = (sizeof(watch_CC_seq) / sizeof(watch_CC_seq[0]))
};

static struct command const *const MASTER_OFF_SEQ[] =
{
 &TV_PWR_OFF,
 &SB_PWR_TOG,
 &BR_PWR_OFF
};

const struct cmd_seq MASTER_OFF =
{
 .sequence = MASTER_OFF_SEQ,
 .sequence_len = (sizeof(MASTER_OFF_SEQ) / sizeof(MASTER_OFF_SEQ[0]))
};


/*
 * Blu-Ray Commands
 */

//function = 0x15
const struct command BR_PWR_TOG =
{
 .function = {0xd6, 0xb5, 0x00},
 .function_len = 17,
 .device = &bluray
};

//function = 0x2e
const struct command BR_PWR_ON =
{
 .function = {0xb6, 0xd6, 0x80},
 .function_len = 18,
 .device = &bluray
};

//function = 0x2f
const struct command BR_PWR_OFF =
{
 .function = {0xdb, 0x6b, 0x40},
 .function_len = 19,
 .device = &bluray
};

//function = 0x1a
const struct command BR_PLAY =
{
 .function = {0xb5, 0xb5, 0x00},
 .function_len = 17,
 .device = &bluray
};

//function = 0x19
const struct command BR_PAUSE =
{
 .function = {0xd5, 0xb5, 0x00},
 .function_len = 17,
 .device = &bluray
};

//function = 0x18
const struct command BR_STOP =
{
 .function = {0xab, 0x6a},
 .function_len = 16,
 .device = &bluray
};

//function = 0x56
const struct command BR_NEXT =
{
 .function = {0xb6, 0xb5, 0x80},
 .function_len = 18,
 .device = &bluray
};

//function = 0x57
const struct command BR_PREV =
{
 .function = {0xdb, 0x5a, 0xc0},
 .function_len = 19,
 .device = &bluray
};

//function = 0x39
const struct command BR_UP =
{
 .function = {0xd5, 0xb6, 0x80},
 .function_len = 18,
 .device = &bluray
};

//function = 0x3a
const struct command BR_DOWN =
{
 .function = {0xb5, 0xb6, 0x80},
 .function_len = 18,
 .device = &bluray
};

//function = 0x3b
const struct command BR_LEFT =
{
 .function = {0xda, 0xdb, 0x40},
 .function_len = 19,
 .device = &bluray
};

//function = 0x3c
const struct command BR_RIGHT =
{
 .function = {0xad, 0xb6, 0x80},
 .function_len = 18,
 .device = &bluray
};

//function = 0x3d
const struct command BR_SELECT =
{
 .function = {0xd6, 0xdb, 0x40},
 .function_len = 19,
 .device = &bluray
};

//function = 0x63
const struct command BR_SUBTITLE =
{
 .function = {0xda, 0xad, 0x80},
 .function_len = 18,
 .device = &bluray
};

//function = 0x16
const struct command BR_EJECT =
{
 .function = {0xb6, 0xb5, 0x00},
 .function_len = 17,
 .device = &bluray
};

/*
 * SoundBar Commands
 */

//function = 0x40
const struct command SB_PWR_TOG =
{
 .function = {0xaa, 0xa8, 0xa2, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

//function = 0x41
const struct command SB_VLUP =
{
 .function = {0x8a, 0xaa, 0x2a, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

//function = 0x45
const struct command SB_VLDN =
{
 .function = {0x8a, 0x2a, 0x8a, 0x8a, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

//function = 0x48
const struct command SB_MUTE =
{
 .function = {0xaa, 0x2a, 0x28, 0x88, 0xa2, 0x28},
 .function_len = 48,
 .device = &soundbar
};

//function = 0x44
const struct command SB_SOURCE =
{
 .function = {0xa8, 0xaa, 0x28, 0x8a, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

/*
 * Space Heater Commands
 */

const struct command SH_PWR_TOG =
{
 .function = {0xe8, 0x88, 0x88, 0x8e},
 .function_len = 32,
 .device = &space_heater
};

const struct command SH_HL_TOG =
{
 .function = {0xe8, 0x88, 0x8e, 0x88},
 .function_len = 32,
 .device = &space_heater
};

const struct command SH_OSC =
{
 .function = {0xe8, 0x88, 0xe8, 0x88},
 .function_len = 32,
 .device = &space_heater
};

/*
 * TV Commands
 */

const struct command TV_PWR_TOG =
{
 .function = {0xa2, 0xa2, 0xa8, 0xa2, 0x28, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_PWR_ON =
{
 .function = {0xa2, 0x22, 0x22, 0x28, 0xaa, 0xa8},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_PWR_OFF =
{
 .function = {0x88, 0x88, 0x88, 0x8a, 0xaa, 0xa8},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_SOURCE =
{
 .function = {0x88, 0x88, 0xaa, 0xaa, 0x88, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_INPUT_HDMI1 =
{
 .function = {0x8a, 0xa8, 0xaa, 0x22, 0x22, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_INPUT_HDMI2 =
{
 .function = {0xa2, 0xa8, 0xa8, 0xa2, 0x22, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_INPUT_HDMI3 =
{
 .function = {0x88, 0xaa, 0x2a, 0xa2, 0x22, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_UP =
{
 .function = {0xa2, 0xaa, 0x88, 0xa2, 0x22, 0x22},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_DOWN =
{
 .function = {0x88, 0xaa, 0xa2, 0xa2, 0x22, 0x22},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_SELECT =
{
 .function = {0x8a, 0x8a, 0xa2, 0x88, 0xa2, 0x22},
 .function_len = 48,
 .device = &toshiba_tv
};


/*
 * Work Samsung TV Commands
 */

const struct command SAM_TV_PWR_TOG =
{
 .function = {0xa2, 0xaa, 0xa2, 0x88, 0x88, 0x88},
 .function_len = 48,
 .device = &work_samsung_tv
};
