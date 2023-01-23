
#include "IR_lib.h"
#include "SPI.h"
#include "sys_clk.h"
#include "cmd_prot_structs.h"

#include "driverlib.h"

#include <stdint.h>
#include <stdbool.h>

int main(void) {

    WDT_A_hold(WDT_A_BASE);

    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    PMM_unlockLPM5();

    init_sys_clk();

    //enabling infrared at this point may cause LED glitches at startup
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);
    SysCtl_setInfraredConfig(SYSCTL_INFRAREDDATASOURCE_CONFIG, SYSCTL_INFRAREDMODE_FSK, SYSCTL_INFRAREDPOLARITY_NORMAL);
    SysCtl_enableInfrared();
    __enable_interrupt();




    while(1){

        execute_command(&TV_PWR, false);

//        __delay_cycles(1000000);
    }


}

