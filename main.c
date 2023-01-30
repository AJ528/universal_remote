
#include "system.h"
#include "IR_lib.h"
#include "SPI.h"
#include "cmd_prot_structs.h"
#include "driverlib.h"
#include "GPIO.h"

#include <stdint.h>
#include <stdbool.h>


int main(void) {

    WDT_A_hold(WDT_A_BASE);

    // Determine whether we are coming out of an LPMx.5 or a regular RESET.
//    if (SYSRSTIV == SYSRSTIV_LPM5WU)        // MSP430 just woke up from LPMx.5
//    {
//        bool stop_LPM4_5_WakeUp = true; // Set Flag for SW Trap
//        while(stop_LPM4_5_WakeUp); // SW Trap if wake-up from LPM5
//    }

    init_GPIO();
    init_sys_clk();
    clear_GPIO_ints();

    //enabling infrared at this point may cause LED glitches at startup
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);
    SysCtl_setInfraredConfig(SYSCTL_INFRAREDDATASOURCE_CONFIG, SYSCTL_INFRAREDMODE_FSK, SYSCTL_INFRAREDPOLARITY_NORMAL);
    SysCtl_enableInfrared();
    __enable_interrupt();

    sys_clk_LPM_prep();
    GPIO_LPM_prep();
    system_LPM_prep();
    __bis_SR_register(LPM4_bits | GIE);


//    execute_command(&BR_PWR, false);


    while(1){

//        check_for_command();

    }


}

