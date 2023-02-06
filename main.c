
#include "system.h"
#include "IR_lib.h"
#include "SPI.h"
#include "cmd_assoc_structs.h"
#include "driverlib.h"
#include "GPIO.h"

#include <stdint.h>
#include <stdbool.h>

int main(void) {

    WDT_A_hold(WDT_A_BASE);

    init_GPIO();
    init_sys_clk();
    clear_GPIO_ints();

    //enabling infrared at this point may cause LED glitches at startup
    P1SEL0 |= BIT0;     //set P1.0 for primary module function
    SYSCFG1 = IRMSEL | IREN;    //configure IR modulation to source data from UCA0, FSK mode, normal polarity, and enabled
    __enable_interrupt();

    const struct btn_assoc * action;

    while(1){

        uint16_t button_num = scan_for_pressed_button();
        if(button_num != 0){
            action = get_command(button_num);
            if(action != 0){
                handle_btn_assoc(action);
            }
        }else{
            reset_prev_cmd();
            GPIO_LPM_prep();
            system_LPM_prep();
            __bis_SR_register(LPM4_bits | GIE);
        }
        __no_operation();

    }


}

