/*
 * cmd_prot_structs.c
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#include "cmd_prot_structs.h"
#include "IR_lib.h"

#include <stdint.h>

static const struct device soundbar;
static const struct device bluray;

static const struct protocol sony20;
static const struct protocol NEC;


const struct command BR_PWR =
{
// .function = {0x01, 0xad, 0x6a},
 .function = {0xd6, 0xb5, 0x00},
 .function_len = 17,
 .device = &bluray
};

const struct command SB_PWR =
{
 .function = {0xAA, 0xA8, 0xA2, 0x22, 0x22, 0x28},
 .function_len = 48,
 .device = &soundbar
};

const struct command SB_test =
{
 .function = {0x22, 0xff, 0xa0, 0x51, 0x68, 0x99, 0x50},
 .function_len = 52,
 .device = &soundbar
};

static const struct device soundbar =
{
 .device = {0xAA, 0xAA},
 .device_len = 16,
 .subdevice = {0x88, 0x88, 0x88, 0x88},
 .subdevice_len = 32,
 .prot_used = &NEC
};

static const struct device bluray =
{
// .device = {0x16, 0xb6},
 .device = {0xb5, 0xb0},
 .device_len = 13,
 .subdevice = {0xb5, 0x5b, 0x60},
// .subdevice = {0x0b, 0x55, 0xb6},
 .subdevice_len = 20,
 .prot_used = &sony20
};

static const struct protocol NEC =
{
 .carrier_freq = 38000,
 .unit_freq = 1773,
 .LSB = true,
 .has_ditto = false,
 .primary_stream =
 {
  .extent_ms = 0,
  .lead_in = {0xff, 0xff, 0x00},
  .lead_in_len = 24,
  .lead_out = {0x80},
  .lead_out_len = 1
 },
 .fmt_func = format_NEC_command
};

static const struct protocol sony20 =
{
 .carrier_freq = 40000,
 .unit_freq = 1667,
 .LSB = true,
 .has_ditto = false,
 .primary_stream =
 {
  .extent_ms = 0,
  .lead_in = {0xf0},
  .lead_in_len = 5,
  .lead_out = {0x00},
  .lead_out_len = 0
 },
 .fmt_func = format_sony20_command
};
