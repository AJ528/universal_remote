
#include "IR_lib.h"
#include "SPI.h"

#include "driverlib.h"

#include <stdint.h>
#include <stdbool.h>

#define XT1CLK_FREQ     32768

//Target frequency for MCLK in kHz
#define CS_MCLK_DESIRED_FREQUENCY_IN_KHZ 1000
//MCLK/FLLRef Ratio
#define CS_MCLK_FLLREF_RATIO 31

#define OUTPUT_BUF_SIZE     32
#define TXDATA_LEN  17

static const uint8_t TXData[TXDATA_LEN] =
{
 0xFF, 0xFF, 0x00, 0xAA, 0xAA, 0x88, 0x88, 0x88,
 0x88, 0xAA, 0xA8, 0xA2, 0x22, 0x22, 0x28, 0x80,
 0x00
};

uint8_t TXData_index = 0;
uint16_t TXData_size;

//Variable to store current Clock values
uint32_t mclockValue = 0;
uint32_t smclockValue = 0;

uint8_t output_buf[OUTPUT_BUF_SIZE] = {0};


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

//    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);
//
//    SysCtl_setInfraredConfig(SYSCTL_INFRAREDDATASOURCE_CONFIG, SYSCTL_INFRAREDMODE_FSK, SYSCTL_INFRAREDPOLARITY_NORMAL);
//
//    SysCtl_enableInfrared();


//    EUSCI_A_SPI_enable(EUSCI_A0_BASE);
//
//    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
//
//    __enable_interrupt();

    int16_t result = PB_PWR.device->prot_used->fmt_func(output_buf, OUTPUT_BUF_SIZE, &PB_PWR, false);

    if(result > 0){
        TXData_size = result;
        TXData_index = 0;
        enable_SPI();
        enable_SPI_int();

        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);
        SysCtl_setInfraredConfig(SYSCTL_INFRAREDDATASOURCE_CONFIG, SYSCTL_INFRAREDMODE_FSK, SYSCTL_INFRAREDPOLARITY_NORMAL);
        SysCtl_enableInfrared();

        __enable_interrupt();
    }


    while(1){

    }

}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
    switch(__even_in_range(UCA0IV, USCI_SPI_UCTXIFG))
    {
        case USCI_SPI_UCTXIFG:      // UCTXIFG

            if(TXData_index == TXData_size){
                disable_SPI();
                disable_SPI_int();
            }else{
                UCA0TXBUF = ~(output_buf[TXData_index]);
            }

            //Send next value
//            EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, ~(TXData[TXData_index]));

            if(TXData_index < TXData_size)
                TXData_index++;

            break;
        default:
            break;
    }
}

