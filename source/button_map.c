/*
 * button_map.c
 *
 *  Created on: Feb 4, 2023
 *      Author: adevries
 */

#include "cmd_assoc_structs.h"
//#include "IR_lib.h"



static struct btn_assoc const *const button_map[64] =
{
 0,     //0
 0,
 0,
 0,
 &btn_0x04,
 0,
 0,
 0,
 0,     //0x08
 0,
 0,
 0,
 &btn_0x0C,
 0,
 0,
 0,
 &btn_0x10,     //0x10
 0,
 &btn_0x12,
 0,
 0,
 0,
 0,
 &btn_0x17,
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

const struct btn_assoc * get_command(uint16_t button_num)
{
    return button_map[button_num];
}
