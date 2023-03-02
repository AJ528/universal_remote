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
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x01
  //button name: PLAY
  .sp_cmd =
  {
   .action = (void *)&BR_PLAY,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x02
  //button name: N/A
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x03
  //button name: REWIND
  .sp_cmd =
  {
   .action = (void *)&BR_PREV,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x04
  //button name: VOL+
  .sp_cmd =
  {
   .action = (void *)&SB_VLUP,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x05
  //button name: CH+
  .sp_cmd =
  {
   .action = (void *)&TV_UP,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x06
  //button name: MUTE
  .sp_cmd =
  {
   .action = (void *)&SB_MUTE,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x07
  //button name: PRE-CH
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x08
  //button name: 4
  .sp_cmd =
  {
   .action = (void *)&SB_PWR_TOG,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x09
  //button name: B
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x0a
  //button name: N/A
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x0b
  //button name: A
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x0c
  //button name: VOL-
  .sp_cmd =
  {
   .action = (void *)&SB_VLDN,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x0d
  //button name: CH-
  .sp_cmd =
  {
   .action = (void *)&TV_DOWN,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x0e
  //button name: CH LIST
  .sp_cmd =
  {
   .action = (void *)&TV_SELECT,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x0f
  //button name: 5
  .sp_cmd =
  {
   .action = (void *)&BR_PWR_TOG,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x10
  //button name: 1
  .sp_cmd =
  {
   .action = (void *)&TV_INPUT_HDMI1,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x11
  //button name: SPORTS
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x12
  //button name: POWER
  .sp_cmd =
  {
   .action = (void *)&TV_PWR_TOG,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x13
  //button name: N/A
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x14
  //button name: MENU
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x15
  //button name: GUIDE
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x16
  //button name: SMART HUB
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x17
  //button name: 2
  .sp_cmd =
  {
   .action = (void *)&TV_INPUT_HDMI2,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x18
  //button name: —
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x19
  //button name: C
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x1a
  //button name: N/A
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x1b
  //button name: D
  .sp_cmd =
  {
   .action = (void *)&BR_EJECT,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x1c
  //button name: TOOLS
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x1d
  //button name: INFO
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x1e
  //button name: UP
  .sp_cmd =
  {
   .action = (void *)&BR_UP,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x1f
  //button name: 9
  .sp_cmd =
  {
   .action = (void *)&SH_OSC,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x20
  //button name: 8
  .sp_cmd =
  {
   .action = (void *)&SH_HL_TOG,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x21
  //button name: PAUSE
  .sp_cmd =
  {
   .action = (void *)&BR_PAUSE,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x22
  //button name: SOURCE
  .sp_cmd =
  {
   .action = (void *)&TV_SOURCE,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x23
  //button name: FAST-FORWARD
  .sp_cmd =
  {
   .action = (void *)&BR_NEXT,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x24
  //button name: RETURN
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x25
  //button name: EXIT
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x26
  //button name: DOWN
  .sp_cmd =
  {
   .action = (void *)&BR_DOWN,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x27
  //button name: 3
  .sp_cmd =
  {
   .action = (void *)&TV_INPUT_HDMI3,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x28
  //button name: 0
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x29
  //button name: CLOSED-CAPTIONS
  .sp_cmd =
  {
   .action = (void *)&BR_SUBTITLE,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x2a
  //button name: N/A
  .sp_cmd =
  {
   .action = (void *)0,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x2b
  //button name: STOP
  .sp_cmd =
  {
   .action = (void *)&BR_STOP,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x2c
  //button name: LEFT
  .sp_cmd =
  {
   .action = (void *)&BR_LEFT,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x2d
  //button name: RIGHT
  .sp_cmd =
  {
   .action = (void *)&BR_RIGHT,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x2e
  //button name: SELECT
  .sp_cmd =
  {
   .action = (void *)&BR_SELECT,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 },
 {//index 0x2f
  //button name: 6
  .sp_cmd =
  {
   .action = (void *)&SH_PWR_TOG,
   .type = command
  },
  .lp_cmd =
  {
   .action = (void *)0,
   .type = command
  }
 }
};

const struct btn_assoc * get_command(uint16_t button_num)
{
    return &(button_map[button_num]);
}
