/*
 * sys_clk.c
 *
 *  Created on: Jan 17, 2023
 *      Author: adevries
 */

#include "system.h"

#include "driverlib.h"

#include <stdint.h>
#include <stdlib.h>

//#define CRYSTALXT1_FOR_FLLREF


#define XT1CLK_FREQ     32768
#define MCLK_FREQ_MHZ   1
#define FLL_Ref_Freq    32768
#define FLL_Softtrim_Delay_cycles    24         // delay 24 cycles of FLL reference clock
#define FLL_Softtrim_Delay  (FLL_Softtrim_Delay_cycles*1000000/FLL_Ref_Freq)*MCLK_FREQ_MHZ  // delay for FLL lock

// Statically-initialized variable for DCO tap stored when FLL locked
#pragma NOINIT(CSCTL0_cal_val)        // variable in FRAM for FLL locked DCO tap value
#pragma LOCATION(CSCTL0_cal_val, 0x1800)  // define the variable in information memory
uint16_t CSCTL0_cal_val;

#pragma NOINIT(CSCTL1_cal_val)    // variable in FRAM for FLL locked DCOFTRIM and DCORSEL value
#pragma LOCATION(CSCTL1_cal_val, 0x1802) // define the variable in information memory
uint16_t CSCTL1_cal_val;

#pragma NOINIT(calibration_valid)                  // Flag of FLL locked DCO tap, FTRIM and RSEL stored in the FRAM
#pragma LOCATION(calibration_valid, 0x1804)            // define the variable in information memory
uint8_t calibration_valid;

void init_sys_clk(void)
{
//    CSCTL7 &= ~(XT1OFFG | DCOFFG);      // Clear XT1 and DCO fault flag
//
//    __bis_SR_register(SCG0);                           // disable FLL
//    CSCTL3 = SELREF__REFOCLK;                         // Set REFO as FLL reference source
//    CSCTL0 = DCO1;                                        // clear DCO and MOD registers
//    if(calibration_valid != 0xff){
//        CSCTL0 = CSCTL0_cal_val;
//        CSCTL1 = CSCTL1_cal_val;
//    }else{
//        CSCTL1 = DCOFTRIM_3 | DCORSEL_0 | DISMOD;
//    }
//    CSCTL2 = FLLD_0 + 30;                             // DCOCLKDIV = 1 MHz
//    __delay_cycles(3);
//    __bic_SR_register(SCG0);                           // enable FLL
//    __delay_cycles(10);
//    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1));         // FLL locked
//
//    CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK;        // set default REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
//    //to avoid errata #PMM32 keep SMCLK = MCLK
//    CSCTL5 = VLOAUTOOFF | DIVM__1 | DIVS__1;          // default DCOCLKDIV as MCLK and SMCLK source



#ifdef CRYSTALXT1_FOR_FLLREF
    P4SEL0 |= BIT1 | BIT2;                  // P4.1~P4.2: crystal pins
    do
    {
        CSCTL7 &= ~(XT1OFFG | DCOFFG);      // Clear XT1 and DCO fault flag
        SFRIFG1 &= ~OFIFG;
    } while ((SFRIFG1 & OFIFG) || (CSCTL7 & XT1OFFG) || (CSCTL7 & DCOFFG));              // Test oscillator fault flag
#endif

// Start of the DCO+FLL configuration and FLL lock

    __bis_SR_register(SCG0);                // disable FLL
#ifdef CRYSTALXT1_FOR_FLLREF
    CSCTL3 = SELREF__XT1CLK;               // Set XT1CLK as FLL reference source
#else
    CSCTL3 = SELREF__REFOCLK;               // Set REFO as FLL reference source
#endif

    CSCTL0 = 0;                             // clear DCO and MOD registers

    CSCTL1 = DCOFTRIMEN | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_2;// Enable software trim, DCOFTRIM=3, DCO Range = 1MHz
    CSCTL2 = FLLD_0 + 30;                  // DCODIV = 1MHz

    if (calibration_valid != 0xff)
    {
        CSCTL0 = CSCTL0_cal_val;          // Load stored DCO Tap value
        CSCTL1 = CSCTL1_cal_val;      // Load stored DCOFTRIM and DCORSEL
    }
    __delay_cycles(3);
    __bic_SR_register(SCG0);                            // enable FLL

    #ifdef CRYSTALXT1_FOR_FLLREF
        CSCTL4 |= SELMS__XT1CLK;                        // set XT1(~32768Hz) as MCLK
    #else
        CSCTL4 |= SELMS__REFOCLK;                       // set REFO(~32768Hz) as MCLK
    #endif
        __delay_cycles(10);                             // delay 10 FLL reference clock cycles
        while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1));      // Check if FLL locked

#ifdef CRYSTALXT1_FOR_FLLREF
    CSCTL4 = SELMS__DCOCLKDIV | SELA__XT1CLK;           // set XT1(~32768Hz) as ACLK source, ACLK = 32768Hz
                                                        // default DCODIV as MCLK and SMCLK source
#else
    CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK;          // set REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
                                                        // default DCODIV as MCLK and SMCLK source
#endif

}

void system_LPM_prep(void)
{
//    RTCCTL = 0x00;
//    LCDCTL0 = 0x00;
    WDT_A_hold(WDT_A_BASE);

    __disable_interrupt();

//    PMM_turnOffRegulator();
}

uint16_t find_best_prescaler(uint32_t src_clk, uint16_t target_clk)
{
    uint16_t initial_div = src_clk / target_clk;

    int16_t diff = (src_clk / initial_div) - target_clk;


    if(diff == 0){
        return initial_div;
    }else{
        int16_t diff2 = abs((src_clk / (initial_div + 1)) - target_clk);
        if(diff > diff2)
            return (initial_div + 1);
        else
            return initial_div;
    }
}
