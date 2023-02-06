/*
 * timer.c
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#include "timer.h"
#include "system.h"

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>


static bool local_extent_passed = false;

void enable_carrier_wave(uint32_t SMCLK_freq, uint16_t desired_freq)
{
    uint16_t period = find_best_prescaler(SMCLK_freq, desired_freq);

    TA0CCR0 = period;      //period
    TA0CCR2 = period / 3;  //duty cycle
    TA0EX0 = TAIDEX_0;      //divide by 1
    TA0CCTL0 = 0;
    TA0CCTL2 = OUTMOD_7;    //reset/set
    TA0CTL = TASSEL__SMCLK | ID__1 | MC__UP;    //smclk source, /1, count up
}

inline void stop_carrier_wave(void)
{
    TA0CTL = MC__STOP | TACLR;
}

void start_extent_timer(uint16_t ms_delay)
{
    TA1CCR0 = ms_delay * 33;
    TA1EX0 = TAIDEX_0;      //divide by 1
    TA1CCTL0 = CCIE;        //enable interrupt
    TA1CTL = TASSEL__ACLK | ID__1 | MC__UP;    //aclk source, /1, interrupt count up
}

inline bool extent_passed(void)
{
    return local_extent_passed;
}

inline void set_extent_passed(void)
{
    local_extent_passed = true;
}

inline void reset_extent_passed(void)
{
    local_extent_passed = false;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER_A1_CCR0_ISR(void)
{
    TA1CTL = MC__STOP | TACLR;

    local_extent_passed = true;
    __bic_SR_register_on_exit(LPM3_bits);
}
