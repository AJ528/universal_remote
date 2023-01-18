/*
 * sys_clk.c
 *
 *  Created on: Jan 17, 2023
 *      Author: adevries
 */


#include <stdint.h>
#include <stdlib.h>

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
