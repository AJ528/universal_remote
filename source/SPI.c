/*
 * SPI.c
 *
 *  Created on: Jan 17, 2023
 *      Author: adevries
 */

#include "SPI.h"
#include "sys_clk.h"

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>


void set_unit_freq(uint32_t SMCLK_freq, uint16_t desired_freq)
{
    uint16_t prescaler = find_best_prescaler(SMCLK_freq, desired_freq);

    //MSB first, master, sync, SMCLK, reset
    UCA0CTLW0 = UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCSWRST;
    UCA0BRW = prescaler;
}

inline void enable_SPI(void)
{
    UCA0CTLW0 &= ~UCSWRST;
}

inline void disable_SPI(void)
{
    UCA0CTLW0 |= UCSWRST;
}

inline bool SPI_enabled(void)
{
    if(UCA0CTLW0 & UCSWRST)
        return false;
    else
        return true;
}

inline void enable_SPI_int(void)
{
    UCA0IE = UCTXIFG;
}

inline void disable_SPI_int(void)
{
    UCA0IE = 0;
}
