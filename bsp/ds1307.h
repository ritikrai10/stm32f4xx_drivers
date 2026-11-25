/*
 * ds1307.h
 *
 *  Created on: Nov 25, 2026
 *      Author: ritikrai
 */

#ifndef DS1307_H_
#define DS1307_H_



#include "stm32f407xx.h"

/*Application configurable items */
#define DS1307_I2C  			I2C1
#define DS1307_I2C_GPIO_PORT    GPIOB
#define DS1307_I2C_SDA_PIN 		GPIO_PIN_NO_7
#define DS1307_I2C_SCL_PIN 		GPIO_PIN_NO_6
#define DS1307_I2C_SPEED 		I2C_SCL_SPEED_SM
#define DS1307_I2C_PUPD			GPIO_PIN_PU



//register addresses
#define DS1307_ADDR_SEC                    0x00
#define DS1307

#endif /* DS1307_H_ */
