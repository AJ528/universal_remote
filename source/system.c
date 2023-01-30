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


#define XT1CLK_FREQ     32768

//Target frequency for MCLK in kHz
#define CS_MCLK_DESIRED_FREQUENCY_IN_KHZ 1000
//MCLK/FLLRef Ratio
#define CS_MCLK_FLLREF_RATIO 31



void init_sys_clk(void)
{
    // Configure Pins for XIN
    //Set P4.1 and P4.2 as Module Function Input.
    /*

    * Select Port 4
    * Set Pin 1, 2 to input Module Function, (XIN).
    */
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P4,
        GPIO_PIN1 + GPIO_PIN2,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    CS_setExternalClockSource(XT1CLK_FREQ);

    CS_turnOnXT1LF(CS_XT1_DRIVE_3);

    // Set DCO FLL reference = XT1CLK
    CS_initClockSignal(CS_FLLREF, CS_XT1CLK_SELECT, CS_CLOCK_DIVIDER_1);
    // Set ACLK = XT1CLK
    CS_initClockSignal(CS_ACLK, CS_XT1CLK_SELECT, CS_CLOCK_DIVIDER_1);

    // Set Ratio and Desired MCLK Frequency and initialize DCO
    CS_initFLLSettle(CS_MCLK_DESIRED_FREQUENCY_IN_KHZ, CS_MCLK_FLLREF_RATIO);

    CS_initClockSignal(CS_MCLK, CS_DCOCLKDIV_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLKDIV_SELECT, CS_CLOCK_DIVIDER_1);
}

void sys_clk_LPM_prep(void)
{
    CS_initClockSignal(CS_FLLREF, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK, CS_VLOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_turnOffXT1();
}

void system_LPM_prep(void)
{
    RTCCTL = 0x00;
    LCDCTL0 = 0x00;
    WDT_A_hold(WDT_A_BASE);

    __disable_interrupt();

    PMM_turnOffRegulator();
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
