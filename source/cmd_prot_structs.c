/*
 * cmd_prot_structs.c
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#include "cmd_prot_structs.h"
#include "IR_lib.h"

#include <stdint.h>

static const struct device toshiba_tv;
static const struct device soundbar;
static const struct device bluray;

static const struct protocol sony20;
static const struct protocol NEC1;
static const struct protocol NEC2;


const struct command BR_PWR =
{
 .function = {0xd6, 0xb5, 0x00},
 .function_len = 17,
 .device = &bluray
};

const struct command BR_PWR_ON =
{
 .function = {0xb6, 0xd6, 0x80},
 .function_len = 18,
 .device = &bluray
};

const struct command BR_PWR_OFF =
{
 .function = {0xdb, 0x6b, 0x40},
 .function_len = 19,
 .device = &bluray
};

const struct command SB_PWR =
{
 .function = {0xaa, 0xa8, 0xa2, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

const struct command SB_VLUP =
{
 .function = {0x8a, 0xaa, 0x2a, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

const struct command SB_VLDN =
{
 .function = {0x8a, 0x2a, 0x8a, 0x8a, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

const struct command TV_PWR =
{
 .function = {0xa2, 0xa2, 0xa8, 0xa2, 0x28, 0x88},
 .function_len = 48,
 .device = &toshiba_tv
};

const struct command TV_PWR2 =
{
 .function = {0xa2, 0x22, 0x22, 0x28, 0xaa, 0xa8},
 .function_len = 48,
 .device = &toshiba_tv
};

static const struct device toshiba_tv =
{
 .device = {0xAA, 0xA8, 0x80},
 .device_len = 18,
 .subdevice = {0x88, 0x88, 0x88, 0xa0},
 .subdevice_len = 30,
 .prot_used = &NEC2
};

static const struct device soundbar =
{
 .device = {0xaa, 0xaa},
 .device_len = 16,
 .subdevice = {0x88, 0x88, 0x88, 0x88},
 .subdevice_len = 32,
 .prot_used = &NEC1
};

static const struct device bluray =
{
 .device = {0xb5, 0xb0},
 .device_len = 13,
 .subdevice = {0xb5, 0x5b, 0x60},
 .subdevice_len = 20,
 .prot_used = &sony20
};

//IRP notation: {38.0k,564}<1,-1|1,-3>(16,-8,D:8,S:8,F:8,~F:8,1,^108m,(16,-4,1,^108m)*)
static const struct protocol NEC1 =
{
 .carrier_freq = 38000,
 .unit_freq = 1773,
 .LSB = true,
 .has_ditto = true,
 .primary_stream =
 {
  .extent_ms = 108,
  .lead_in = {0xff, 0xff, 0x00},
  .lead_in_len = 24,
  .lead_out = {0x80},
  .lead_out_len = 1
 },
 .ditto_stream =
 {
  .extent_ms = 108,
  .lead_in = {0xff, 0xff, 0x00},
  .lead_in_len = 20,
  .lead_out = {0x80},
  .lead_out_len = 1
 },
 .fmt_func = format_NEC1_command
};

//IRP notation: {38.0k,564}<1,-1|1,-3>(16,-8,D:8,S:8,F:8,~F:8,1,^108m)+
static const struct protocol NEC2 =
{
 .carrier_freq = 38000,
 .unit_freq = 1773,
 .LSB = true,
 .has_ditto = false,
 .primary_stream =
 {
  .extent_ms = 108,
  .lead_in = {0xff, 0xff, 0x00},
  .lead_in_len = 24,
  .lead_out = {0x80},
  .lead_out_len = 1
 },
 .fmt_func = format_NEC2_command
};

//IRP notation: {40k,600}<1,-1|2,-1>(4,-1,F:7,D:5,S:8,^45m)+
static const struct protocol sony20 =
{
 .carrier_freq = 40000,
 .unit_freq = 1667,
 .LSB = true,
 .has_ditto = false,
 .primary_stream =
 {
  .extent_ms = 45,
  .lead_in = {0xf0},
  .lead_in_len = 5,
  .lead_out = {0x00},
  .lead_out_len = 0
 },
 .fmt_func = format_sony20_command
};
