
#include "IR_lib.h"
#include "SPI.h"
#include "sys_clk.h"

#include "driverlib.h"

#include <stdint.h>
#include <stdbool.h>

#define OUTPUT_BUF_SIZE     32

uint8_t output_buf[OUTPUT_BUF_SIZE] = {0};

uint8_t TXData_index = 0;
uint16_t TXData_size;


int main(void) {

    WDT_A_hold(WDT_A_BASE);

    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    PMM_unlockLPM5();

    init_sys_clk();

    int16_t result = SB_PWR.device->prot_used->fmt_func(output_buf, OUTPUT_BUF_SIZE, &SB_PWR, false);
//    result = BR_PWR.device->prot_used->fmt_func(output_buf, OUTPUT_BUF_SIZE, &BR_PWR, false);

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

