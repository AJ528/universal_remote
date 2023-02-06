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

static const struct command BR_PWR;
static const struct command BR_PWR_ON;
static const struct command BR_PWR_OFF;

static const struct command TV_PWR_TOG;
static const struct command TV_PWR_ON;

static const struct cmd_seq watch_CC;


const struct btn_assoc btn_0x04 =
{
 .action = (void *)&SB_VLUP,
 .type = command
};

const struct btn_assoc btn_0x0C =
{
 .action = (void *)&SB_VLDN,
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

static const struct command BR_PWR =
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


