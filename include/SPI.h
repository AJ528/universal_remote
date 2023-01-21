/*
 * SPI.h
 *
 *  Created on: Jan 17, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_SPI_H_
#define INCLUDE_SPI_H_

#include <stdint.h>

void set_unit_freq(uint32_t SMCLK_freq, uint16_t desired_freq);
inline void enable_SPI(void);
inline void disable_SPI(void);
inline void enable_SPI_int(void);
inline void disable_SPI_int(void);

#endif /* INCLUDE_SPI_H_ */
