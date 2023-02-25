/*
 * button_map.c
 *
 *  Created on: Feb 4, 2023
 *      Author: adevries
 */

#include "cmd_assoc_structs.h"

static struct btn_assoc const *const button_map[64] =
{
 &btn_0x00,     //0
 0,
 0,
 0,
 &btn_0x04,
 &btn_0x05,
 &btn_0x06,
 0,
 &btn_0x08,     //0x08
 0,
 0,
 0,
 &btn_0x0C,
 &btn_0x0D,
 &btn_0x0E,
 &btn_0x0F,
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
 &btn_0x1B,
 0,
 0,
 0,
 &btn_0x1F,
 &btn_0x20,     //0x20
 0,
 &btn_0x22,
 0,
 0,
 0,
 0,
 &btn_0x27,
 0,     //0x28
 0,
 0,
 0,
 0,
 0,
 &btn_0x2E,
 &btn_0x2F,
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
