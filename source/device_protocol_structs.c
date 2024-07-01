/*
 * device_protocol_structs.c
 *
 *  Created on: Feb 5, 2023
 *      Author: adevries
 */

#include "device_protocol_structs.h"
#include "IR_lib.h"

//device = 0x40
//subdevice = 0xBF
const struct device toshiba_tv =
{
 .device = {0xAA, 0xA8, 0x80},
 .device_len = 18,
 .subdevice = {0x88, 0x88, 0x88, 0xa0},
 .subdevice_len = 30,
 .prot_used = &NEC1
};

const struct device samsung_tv =
{
 .device = {0x88, 0x8A, 0xA8},
 .device_len = 22,
 .subdevice = {0x88, 0x8A, 0xA8},
 .subdevice_len = 22,
 .prot_used = &NECx2
};

const struct device soundbar =
{
 .device = {0xaa, 0xaa},
 .device_len = 16,
 .subdevice = {0x88, 0x88, 0x88, 0x88},
 .subdevice_len = 32,
 .prot_used = &NEC1
};

//device = 0x1a
//subdevice = 0xe2
const struct device bluray =
{
 .device = {0xb5, 0xb0},
 .device_len = 13,
 .subdevice = {0xb5, 0x5b, 0x60},
 .subdevice_len = 20,
 .prot_used = &sony20
};

const struct device space_heater =
{
 .device = {0x8e},
 .device_len = 8,
 .subdevice = {0},
 .subdevice_len = 0,
 .prot_used = &space_heater_protocol
};

//IRP notation: {38.0k,564}<1,-1|1,-3>(16,-8,D:8,S:8,F:8,~F:8,1,^108m,(16,-4,1,^108m)*)
const struct protocol NEC1 =
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
const struct protocol NEC2 =
{
 .carrier_freq = 38000,
 .unit_freq = 1773,
 .LSB = true,
 .has_ditto = false,
 .primary_stream =
 {
  .extent_ms = 108,
//  .extent_ms = 500,
  .lead_in = {0xff, 0xff, 0x00},
  .lead_in_len = 24,
  .lead_out = {0x80},
  .lead_out_len = 1
 },
 .fmt_func = format_NEC2_command
};

//IRP notation: {38.4k,564}<1,-1|1,-3>(8,-8,D:8,S:8,F:8,~F:8,1,^108m)+
const struct protocol NECx2 =
{
 .carrier_freq = 38400,
 .unit_freq = 1773,
 .LSB = true,
 .has_ditto = false,
 .primary_stream =
 {
  .extent_ms = 108,
  .lead_in = {0xff, 0x00},
  .lead_in_len = 16,
  .lead_out = {0x80},
  .lead_out_len = 1
 },
 .fmt_func = format_NEC2_command
};

//IRP notation: {40k,600}<1,-1|2,-1>(4,-1,F:7,D:5,S:8,^45m)+
const struct protocol sony20 =
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


const struct protocol space_heater_protocol =
{
 .carrier_freq = 38000,
 .unit_freq = 2440,
 .LSB = true,
 .has_ditto = false,
 .primary_stream =
 {
  .extent_ms = 26,
  .lead_in = {0xee},
  .lead_in_len = 8,
  .lead_out = {0x00},
  .lead_out_len = 0
 },
 .fmt_func = format_space_heater_command
};

