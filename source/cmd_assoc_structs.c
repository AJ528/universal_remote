/*
 * cmd_prot_structs.c
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#include "cmd_assoc_structs.h"
#include "device_protocol_structs.h"


static const struct command SB_PWR_TOG;
static const struct command SB_VLUP;
static const struct command SB_VLDN;
static const struct command SB_MUTE;

static const struct command BR_PWR_TOG;
static const struct command BR_PWR_ON;
static const struct command BR_PWR_OFF;

static const struct command TV_PWR_TOG;
static const struct command TV_PWR_ON;
static const struct command TV_PWR_OFF;
static const struct command TV_SOURCE;
static const struct command TV_INPUT_HDMI3;
static const struct command TV_UP;
static const struct command TV_DOWN;
static const struct command TV_SELECT;

static const struct cmd_seq watch_CC;
static const struct cmd_seq MASTER_OFF;


const struct btn_assoc btn_0x04 =
{
 .action = (void *)&SB_VLUP,
 .type = command
};

const struct btn_assoc btn_0x05 =
{
 .action = (void *)&TV_UP,
 .type = command
};

const struct btn_assoc btn_0x06 =
{
 .action = (void *)&SB_MUTE,
 .type = command
};

const struct btn_assoc btn_0x0C =
{
 .action = (void *)&SB_VLDN,
 .type = command
};

const struct btn_assoc btn_0x0D =
{
 .action = (void *)&TV_DOWN,
 .type = command
};

const struct btn_assoc btn_0x0E =
{
 .action = (void *)&TV_SELECT,
 .type = command
};

const struct btn_assoc btn_0x10 =
{
 .action = (void *)&SB_PWR_TOG,
 .type = command
};

const struct btn_assoc btn_0x12 =
{
 .action = (void *)&TV_PWR_TOG,
 .type = command
};

const struct btn_assoc btn_0x17 =
{
 .action = (void *)&watch_CC,
 .type = cmd_seq
};

const struct btn_assoc btn_0x22 =
{
 .action = (void *)&TV_SOURCE,
 .type = command
};

const struct btn_assoc btn_0x27 =
{
 .action = (void *)&MASTER_OFF,
 .type = cmd_seq
};

/*
 * Command Sequences
 */

static struct command const *const watch_CC_seq[] =
{
 &TV_PWR_ON,
 &SB_PWR_TOG
};

static const struct cmd_seq watch_CC =
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

static const struct cmd_seq MASTER_OFF =
{
 .sequence = MASTER_OFF_SEQ,
 .sequence_len = (sizeof(MASTER_OFF_SEQ) / sizeof(MASTER_OFF_SEQ[0]))
};


/*
 * Blu-Ray Commands
 */

static const struct command BR_PWR_TOG =
{
 .function = {0xd6, 0xb5, 0x00},
 .function_len = 17,
 .device = &bluray
};

static const struct command BR_PWR_ON =
{
 .function = {0xb6, 0xd6, 0x80},
 .function_len = 18,
 .device = &bluray
};

static const struct command BR_PWR_OFF =
{
 .function = {0xdb, 0x6b, 0x40},
 .function_len = 19,
 .device = &bluray
};

/*
 * SoundBar Commands
 */

static const struct command SB_PWR_TOG =
{
 .function = {0xaa, 0xa8, 0xa2, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

static const struct command SB_VLUP =
{
 .function = {0x8a, 0xaa, 0x2a, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

static const struct command SB_VLDN =
{
 .function = {0x8a, 0x2a, 0x8a, 0x8a, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

static const struct command SB_MUTE =
{
 .function = {0xaa, 0x2a, 0x28, 0x88, 0xa2, 0x28},
 .function_len = 48,
 .device = &soundbar
};

/*
 * TV Commands
 */

static const struct command TV_PWR_TOG =
{
 .function = {0xa2, 0xa2, 0xa8, 0xa2, 0x28, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct command TV_PWR_ON =
{
 .function = {0xa2, 0x22, 0x22, 0x28, 0xaa, 0xa8},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct command TV_PWR_OFF =
{
 .function = {0x88, 0x88, 0x88, 0x8a, 0xaa, 0xa8},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct command TV_SOURCE =
{
 .function = {0x88, 0x88, 0xaa, 0xaa, 0x88, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct command TV_INPUT_HDMI3 =
{
 .function = {0x88, 0xaa, 0x2a, 0xa2, 0x22, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct command TV_UP =
{
 .function = {0xa2, 0xaa, 0x88, 0xa2, 0x22, 0x22},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct command TV_DOWN =
{
 .function = {0x88, 0xaa, 0xa2, 0xa2, 0x22, 0x22},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct command TV_SELECT =
{
 .function = {0x8a, 0x8a, 0xa2, 0x88, 0xa2, 0x22},
 .function_len = 48,
 .device = &toshiba_tv
};

