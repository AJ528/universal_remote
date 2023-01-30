/*
 * GPIO.h
 *
 *  Created on: Jan 28, 2023
 *      Author: adevries
 */

#ifndef INCLUDE_GPIO_H_
#define INCLUDE_GPIO_H_

void init_GPIO(void);
void clear_GPIO_ints(void);
void enable_GPIO_ints(void);
void disable_GPIO_ints(void);
void GPIO_LPM_prep(void);

#endif /* INCLUDE_GPIO_H_ */
