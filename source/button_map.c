/*
 * button_map.c
 *
 *  Created on: Feb 4, 2023
 *      Author: adevries
 */

#include "cmd_prot_structs.h"
#include "IR_lib.h"



static const void *const button_map[64] =
{
 0,     //0
 0,
 0,
 0,
 &SB_VLUP,
 0,
 0,
 0,
 0,     //0x08
 0,
 0,
 0,
 &SB_VLDN,
 0,
 0,
 0,
 &SB_PWR,     //0x10
 0,
 &TV_PWR,
 0,
 0,
 0,
 0,
 0,
 0,     //0x18
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,     //0x20
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,     //0x28
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,     //0x30
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,     //0x38
 0,
 0,
 0,
 0,
 0,
 0,
 0
};

const struct command * get_command(uint16_t button_num)
{
    return button_map[button_num];
}
