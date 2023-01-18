
#include "IR_lib.h"

#include "driverlib.h"

#include <stdint.h>
#include <stdbool.h>

#define XT1CLK_FREQ     32768

//Target frequency for MCLK in kHz
#define CS_MCLK_DESIRED_FREQUENCY_IN_KHZ 1000
//MCLK/FLLRef Ratio
#define CS_MCLK_FLLREF_RATIO 31

#define TXDATA_LEN  17

static const uint8_t TXData[TXDATA_LEN] =
{
 0xFF, 0xFF, 0x00, 0xAA, 0xAA, 0x88, 0x88, 0x88,
 0x88, 0xAA, 0xA8, 0xA2, 0x22, 0x22, 0x28, 0x80,
 0x00
};

uint8_t TXData_Index = 0;

//Variable to store current Clock values
uint32_t mclockValue = 0;
uint32_t smclockValue = 0;



int main(void) {

    WDT_A_hold(WDT_A_BASE);

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

    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    PMM_unlockLPM5();

    // Set DCO FLL reference = XT1CLK
    CS_initClockSignal(CS_FLLREF, CS_XT1CLK_SELECT, CS_CLOCK_DIVIDER_1);
    // Set ACLK = XT1CLK
    CS_initClockSignal(CS_ACLK, CS_XT1CLK_SELECT, CS_CLOCK_DIVIDER_1);

    // Set Ratio and Desired MCLK Frequency and initialize DCO
    CS_initFLLSettle(CS_MCLK_DESIRED_FREQUENCY_IN_KHZ, CS_MCLK_FLLREF_RATIO);

    CS_initClockSignal(CS_MCLK, CS_DCOCLKDIV_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLKDIV_SELECT, CS_CLOCK_DIVIDER_1);


    //Verify if the Clock settings are as expected
    mclockValue = CS_getMCLK();
    smclockValue = CS_getSMCLK();


    Timer_A_outputPWMParam A0_pwm_param =
    {
     .clockSource = TIMER_A_CLOCKSOURCE_SMCLK,
     .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1,
     .timerPeriod = 26,         //for 27 counts
     .compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2,
     .compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET,
     .dutyCycle = 7
    };

    Timer_A_outputPWM(TIMER_A0_BASE, &A0_pwm_param);

    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

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
//    EUSCI_A_SPI_initMaster(EUSCI_A0_BASE, &spi_param);

    UCA0CTLW0 = 0x2981;
    UCA0BRW = 569;

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);

    SysCtl_setInfraredConfig(SYSCTL_INFRAREDDATASOURCE_CONFIG, SYSCTL_INFRAREDMODE_FSK, SYSCTL_INFRAREDPOLARITY_NORMAL);

    SysCtl_enableInfrared();


//    EUSCI_A_SPI_enable(EUSCI_A0_BASE);
//
//    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
//
//    __enable_interrupt();


    uint8_t output_buf[32] = {0};
    uint16_t output_buf_size = 32;

    PB_PWR.device->prot_used->fmt_func(output_buf, &output_buf_size, &PB_PWR, false);


    while(1){
        if(TXData_Index == TXDATA_LEN){
            EUSCI_A_SPI_disable(EUSCI_A0_BASE);
        }
    }

}


#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch(__even_in_range(UCA0IV, USCI_SPI_UCTXIFG))
    {
        case USCI_SPI_UCTXIFG:      // UCTXIFG

            //Send next value
            EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, ~(TXData[TXData_Index]));

            if(TXData_Index < TXDATA_LEN - 1)
                TXData_Index++;
            break;
        default:
            break;
    }
}

