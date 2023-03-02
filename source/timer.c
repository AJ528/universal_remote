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

static inline void reset_timer_expired(void);

static bool local_timer_expired = false;

void enable_carrier_wave(uint32_t SMCLK_freq, uint16_t desired_freq)
{
    uint16_t period = find_best_prescaler(SMCLK_freq, desired_freq);

    TA0CCR0 = (period - 1);      //period
    TA0CCR2 = (period - 1) / 3;  //duty cycle
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
    reset_timer_expired();
    TA1CCR0 = ms_delay * 33;
    TA1EX0 = TAIDEX_0;      //divide by 1
    TA1CCTL0 = CCIE;        //enable interrupt
    TA1CTL = TASSEL__ACLK | ID__1 | MC__UP;    //aclk source, /1, interrupt count up
}

void start_10ms_inc_timer(uint16_t ms10_delay)
{
    reset_timer_expired();
    TA1CCR0 = ms10_delay * 33;
    TA1EX0 = TAIDEX_5;      //divide by 5
    TA1CCTL0 = CCIE;        //enable interrupt
    TA1CTL = TASSEL__ACLK | ID__2 | MC__UP;    //aclk source, /2, interrupt count up
}

bool timer_expired(void)
{
    return local_timer_expired;
}

void expire_timer(void)
{
    TA1CTL = MC__STOP | TACLR;
    local_timer_expired = true;
}

static inline void reset_timer_expired(void)
{
    local_timer_expired = false;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER_A1_CCR0_ISR(void)
{
    TA1CTL = MC__STOP | TACLR;

    local_timer_expired = true;
    __bic_SR_register_on_exit(LPM3_bits);
}
