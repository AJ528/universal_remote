/*
 * GPIO.c
 *
 *  Created on: Jan 28, 2023
 *      Author: adevries
 */

#include "GPIO.h"
#include "cmd_prot_structs.h"
#include "IR_lib.h"

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#define     MATRIX_NUM_ROWS     (6)
//#define     MATRIX_NUM_COLS     (8)   //not used currently

inline static int8_t get_bit_pos(uint8_t input);

void init_GPIO(void)
{
    P1DIR = 0xff;
    P2DIR = (BIT7 | BIT6);
    P3DIR = 0xff;
//    P4DIR = 0xfd;
    P4DIR = 0xff;
    P5DIR = 0xff;
    P6DIR = 0xff;
    P7DIR = 0xff;
    P8DIR = 0x0f;

    P1OUT = 0x00;

    P2REN = 0x00;
    P2IES = 0x3f;

    P3OUT = 0xff;

    PM5CTL0 &= ~LOCKLPM5;
}

// scans the array of buttons and returns the
// value of the first button pressed
// if none are pressed, returns 0
uint16_t scan_for_pressed_button(void)
{
    static const uint8_t in_mask = (0x01 << MATRIX_NUM_ROWS) - 1;
    uint8_t i = 0;
    uint8_t out_mask = BIT0;
    uint8_t input;
    int8_t bit_pos;
    uint16_t button_num = 0;

    while(out_mask != 0){
        P3OUT = ~(out_mask);
        input = (~P2IN) & in_mask;

        if(input != 0){  //a button has been pressed
            bit_pos = get_bit_pos(input);
            if(bit_pos != -1)
                button_num = (i << 3) + (bit_pos);
            return button_num;
        }
        out_mask = out_mask << 1;
        i++;
    }
    return button_num;
}

// finds least significant bit that is set in input and
// returns its position. Returns -1 if no bits are set.
inline static int8_t get_bit_pos(uint8_t input)
{
    uint8_t mask = 1;
    uint8_t i = 0;
    while(mask != 0){
        if((input & mask) != 0)
            return i;

        mask = mask << 1;
        i++;
    }
    //if no bits are found
    return (-1);
}

void clear_GPIO_ints(void)
{
    P2IFG = 0;
}

void enable_GPIO_ints(void)
{
    P2IE = 0x3f;
}

void disable_GPIO_ints(void)
{
    P2IE = 0x00;
    P2IFG = 0x00;
}

void GPIO_LPM_prep(void)
{
    PASEL0 = 0x0000;
    PBSEL0 = 0x0000;
    PCSEL0 = 0x0000;
    PDSEL0 = 0x0000;

    PAOUT = 0x0000;
    PBOUT = 0x0000;
    PCOUT = 0x0000;
    PDOUT = 0x0000;

    P2REN = 0x00;
    P2IES = 0x3f;
    P2IFG = 0x00;
    enable_GPIO_ints();
}

#pragma vector = PORT2_VECTOR
__interrupt void P2_ISR(void)
{
//    switch(__even_in_range(P2IV, P2IV_P2IFG5))
//    {
//        case P2IV_P2IFG0:
//            IR_lib_set_next_command(&SB_VLUP, false);
////            execute_command(&SB_VLUP, false);
//            break;
//        case P2IV_P2IFG1:
//            IR_lib_set_next_command(&SB_VLDN, false);
////            execute_command(&SB_VLDN, false);
//            break;
//        case P2IV_P2IFG2:
//            break;
//        case P2IV_P2IFG3:
//            break;
//        case P2IV_P2IFG4:
//            break;
//        case P2IV_P2IFG5:
//            break;
//        default:    //should never happen
////            enable_GPIO_ints();
//            break;
//    }

    disable_GPIO_ints();
    __bic_SR_register_on_exit(LPM4_bits);
}
