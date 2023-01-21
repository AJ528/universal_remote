/*
 * timer.h
 *
 *  Created on: Jan 20, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include <stdint.h>


void enable_carrier_wave(uint32_t SMCLK_freq, uint16_t desired_freq);
inline void stop_carrier_wave(void);



#endif /* INCLUDE_TIMER_H_ */
