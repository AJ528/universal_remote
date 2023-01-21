/*
 * sys_clk.h
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_SYS_CLK_H_
#define INCLUDE_SYS_CLK_H_

#include <stdint.h>

uint16_t find_best_prescaler(uint32_t src_clk, uint16_t target_clk);

#endif /* INCLUDE_SYS_CLK_H_ */
