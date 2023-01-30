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


void init_GPIO(void)
{
    P1DIR = 0xff;
    P2DIR = (BIT7 | BIT6);
    P3DIR = 0xff;
    P4DIR = 0xfd;
    P5DIR = 0xff;
    P6DIR = 0xff;
    P7DIR = 0xff;
    P8DIR = 0x0f;

    P1OUT = 0x00;

    P2REN = 0x00;
    P2IES = 0x3f;

    P3OUT = 0xff;

//    P3OUT &= ~BIT4;

    PM5CTL0 &= ~LOCKLPM5;
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

    switch(__even_in_range(P2IV, P2IV_P2IFG5))
    {
        case P2IV_P2IFG0:
            IR_lib_set_next_command(&SB_VLUP, false);
//            execute_command(&SB_VLUP, false);
            break;
        case P2IV_P2IFG1:
            IR_lib_set_next_command(&SB_VLDN, false);
//            execute_command(&SB_VLDN, false);
            break;
        case P2IV_P2IFG2:
            break;
        case P2IV_P2IFG3:
            break;
        case P2IV_P2IFG4:
            break;
        case P2IV_P2IFG5:
            break;
        default:    //should never happen
//            enable_GPIO_ints();
            break;
    }

    disable_GPIO_ints();
}
