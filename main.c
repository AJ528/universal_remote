
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

    init_GPIO();

    __bis_SR_register(LPM4_bits | GIE);

    // Determine whether we are coming out of an LPMx.5 or a regular RESET.
//    if (SYSRSTIV == SYSRSTIV_LPM5WU)        // MSP430 just woke up from LPMx.5
//    {
//        bool stop_LPM4_5_WakeUp = true; // Set Flag for SW Trap
//        while(stop_LPM4_5_WakeUp); // SW Trap if wake-up from LPM5
//    }

    init_sys_clk();
    clear_GPIO_ints();

    //enabling infrared at this point may cause LED glitches at startup
//    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);
    P1SEL0 |= BIT0;     //set P1.0 for primary module function
//    SysCtl_setInfraredConfig(SYSCTL_INFRAREDDATASOURCE_CONFIG, SYSCTL_INFRAREDMODE_FSK, SYSCTL_INFRAREDPOLARITY_NORMAL);
//    SysCtl_enableInfrared();
//    SYSCFG1 = IRMSEL | IREN;    //configure IR modulation to source data from UCA0, FSK mode, normal polarity, and enabled
    SYSCFG1 = IRMSEL;
    __enable_interrupt();

    CSCTL8 = 0;

    GPIO_LPM_prep();
    system_LPM_prep();
    __bis_SR_register(LPM4_bits | GIE);

    uint16_t button_num = scan_for_pressed_button();

//    execute_command(&BR_PWR, false);


    while(1){

        __no_operation();

//        check_for_command();

    }


}

