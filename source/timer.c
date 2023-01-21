/*
 * timer.c
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#include "timer.h"
#include "sys_clk.h"

//#include "driverlib.h"
#include <msp430.h>
#include <stdint.h>

void enable_carrier_wave(uint32_t SMCLK_freq, uint16_t desired_freq)
{
//    uint16_t period = 26;
//    uint16_t period = (SMCLK_freq / desired_freq) - 1;

    uint16_t period = find_best_prescaler(SMCLK_freq, desired_freq);

    TA0CCR0 = period;      //period
    TA0CCR2 = period / 3;  //duty cycle
    TA0EX0 = TAIDEX_0;      //divide by 1
    TA0CCTL0 = 0;
    TA0CCTL2 = OUTMOD_7;    //reset/set
    TA0CTL = TASSEL__SMCLK | ID__1 | MC__UP;    //smclk source, /1, count up


//    Timer_A_outputPWMParam A0_pwm_param =
//    {
//     .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
//     .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1,
//     .timerPeriod = period,
//     .compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2,
//     .compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET,
//     .dutyCycle = period / 3
//    };
//
//    Timer_A_outputPWM(TIMER_A0_BASE, &A0_pwm_param);
//
//    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

inline void stop_carrier_wave(void)
{
    TA0CTL = MC__STOP | TACLR;
//    Timer_A_stop(TIMER_A0_BASE);
//    Timer_A_clear(TIMER_A0_BASE);
}
