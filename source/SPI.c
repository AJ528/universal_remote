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


void set_unit_freq(uint32_t SMCLK_freq, uint16_t desired_freq)
{

    //    EUSCI_A_SPI_initMasterParam spi_param =
    //    {
    //     .selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK,
    //     .clockSourceFrequency = clockValue,
    //     .desiredSpiClock = 1786,
    //     .msbFirst = EUSCI_A_SPI_MSB_FIRST,
    //     .clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
    //     .clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
    //     .spiMode = EUSCI_A_SPI_3PIN
    //    };
    //
//        EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &spi_param);

    uint16_t prescaler = find_best_prescaler(SMCLK_freq, desired_freq);

    //MSB first, master, sync, SMCLK, reset
    UCA0CTLW0 = UCMSB | UCMST | UCSYNC | UCSSEL__SMCLK | UCSWRST;
    UCA0BRW = prescaler;

//    UCA0CTLW0 &= ~UCSWRST;

//    UCA0CTLW0 = 0x2981;
//    UCA0BRW = 569;
}

inline void enable_SPI(void)
{
    UCA0CTLW0 &= ~UCSWRST;
}

inline void disable_SPI(void)
{
    UCA0CTLW0 |= UCSWRST;
}

inline void enable_SPI_int(void)
{
    UCA0IE = UCTXIFG;
}

inline void disable_SPI_int(void)
{
    UCA0IE = 0;
}
