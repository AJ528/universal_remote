/*
 * button_map.c
 *
 *  Created on: Feb 4, 2023
 *      Author: adevries
 */

#include "cmd_assoc_structs.h"

static const struct btn_assoc button_map[48] =
{
 {//index 0x00
  //button name: 7
  .action = (void *)0,
  .type = command
 },
 {//index 0x01
  //button name: PLAY
   .action = (void *)&BR_PLAY,
   .type = command
 },
 {//index 0x02
  //button name: N/A
   .action = (void *)0,
   .type = command
 },
 {//index 0x03
  //button name: REWIND
   .action = (void *)&BR_PREV,
   .type = command
 },
 {//index 0x04
  //button name: VOL+
   .action = (void *)&SB_VLUP,
   .type = command
 },
 {//index 0x05
  //button name: CH+
   .action = (void *)&TV_UP,
   .type = command
 },
 {//index 0x06
  //button name: MUTE
   .action = (void *)&SB_MUTE,
   .type = command
 },
 {//index 0x07
  //button name: PRE-CH
   .action = (void *)0,
   .type = command
 },
 {//index 0x08
  //button name: 4
   .action = (void *)&SB_PWR_TOG,
   .type = command
 },
 {//index 0x09
  //button name: B
   .action = (void *)0,
   .type = command
 },
 {//index 0x0a
  //button name: N/A
   .action = (void *)0,
   .type = command
 },
 {//index 0x0b
  //button name: A
   .action = (void *)0,
   .type = command
 },
 {//index 0x0c
  //button name: VOL-
   .action = (void *)&SB_VLDN,
   .type = command
 },
 {//index 0x0d
  //button name: CH-
   .action = (void *)&TV_DOWN,
   .type = command
 },
 {//index 0x0e
  //button name: CH LIST
   .action = (void *)&TV_SELECT,
   .type = command
 },
 {//index 0x0f
  //button name: 5
   .action = (void *)&BR_PWR_TOG,
   .type = command
 },
 {//index 0x10
  //button name: 1
  .action = (void *)&TV_INPUT_HDMI1,
  .type = command
 },
 {//index 0x11
  //button name: SPORTS
   .action = (void *)0,
   .type = command
 },
 {//index 0x12
  //button name: POWER
   .action = (void *)&TV_PWR_TOG,
   .type = command
 },
 {//index 0x13
  //button name: N/A
   .action = (void *)0,
   .type = command
 },
 {//index 0x14
  //button name: MENU
   .action = (void *)0,
   .type = command
 },
 {//index 0x15
  //button name: GUIDE
   .action = (void *)0,
   .type = command
 },
 {//index 0x16
  //button name: SMART HUB
   .action = (void *)0,
   .type = command
 },
 {//index 0x17
  //button name: 2
   .action = (void *)&TV_INPUT_HDMI2,
   .type = command
 },
 {//index 0x18
  //button name: —
   .action = (void *)0,
   .type = command
 },
 {//index 0x19
  //button name: C
   .action = (void *)0,
   .type = command
 },
 {//index 0x1a
  //button name: N/A
   .action = (void *)0,
   .type = command
 },
 {//index 0x1b
  //button name: D
   .action = (void *)&BR_EJECT,
   .type = command
 },
 {//index 0x1c
  //button name: TOOLS
   .action = (void *)0,
   .type = command
 },
 {//index 0x1d
  //button name: INFO
   .action = (void *)0,
   .type = command
 },
 {//index 0x1e
  //button name: UP
   .action = (void *)&BR_UP,
   .type = command
 },
 {//index 0x1f
  //button name: 9
   .action = (void *)&SH_OSC,
   .type = command
 },
 {//index 0x20
  //button name: 8
  .action = (void *)&SH_HL_TOG,
  .type = command
 },
 {//index 0x21
  //button name: PAUSE
   .action = (void *)&BR_PAUSE,
   .type = command
 },
 {//index 0x22
  //button name: SOURCE
   .action = (void *)&TV_SOURCE,
   .type = command
 },
 {//index 0x23
  //button name: FAST-FORWARD
   .action = (void *)&BR_NEXT,
   .type = command
 },
 {//index 0x24
  //button name: RETURN
   .action = (void *)0,
   .type = command
 },
 {//index 0x25
  //button name: EXIT
   .action = (void *)0,
   .type = command
 },
 {//index 0x26
  //button name: DOWN
   .action = (void *)&BR_DOWN,
   .type = command
 },
 {//index 0x27
  //button name: 3
   .action = (void *)&TV_INPUT_HDMI3,
   .type = command
 },
 {//index 0x28
  //button name: 0
   .action = (void *)0,
   .type = command
 },
 {//index 0x29
  //button name: CLOSED-CAPTIONS
   .action = (void *)&BR_SUBTITLE,
   .type = command
 },
 {//index 0x2a
  //button name: N/A
   .action = (void *)0,
   .type = command
 },
 {//index 0x2b
  //button name: STOP
   .action = (void *)&BR_STOP,
   .type = command
 },
 {//index 0x2c
  //button name: LEFT
   .action = (void *)&BR_LEFT,
   .type = command
 },
 {//index 0x2d
  //button name: RIGHT
   .action = (void *)&BR_RIGHT,
   .type = command
 },
 {//index 0x2e
  //button name: SELECT
   .action = (void *)&BR_SELECT,
   .type = command
 },
 {//index 0x2f
  //button name: 6
   .action = (void *)&SH_PWR_TOG,
   .type = command
 }
};

const struct btn_assoc * get_command(uint16_t button_num)
{
    return &(button_map[button_num]);
}
