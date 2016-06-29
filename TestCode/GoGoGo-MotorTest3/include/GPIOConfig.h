/*
 * GPIOConfig.h
 *
 *  Created on: Apr 18, 2016
 *      Author: vagrant
 */

#ifndef INCLUDE_GPIOCONFIG_H_
#define INCLUDE_GPIOCONFIG_H_

#include <stdint.h>
#include "cmsis_device.h"

#define LOW 0
#define HIGH 1


void GPIOConfig_OutputPin(GPIO_TypeDef *port, uint16_t pin);
void GPIOConfig_InputPin(GPIO_TypeDef *port, uint16_t pin);
void GPIOConfig_SetPWMPin(GPIO_TypeDef *port, uint16_t pin);
void GPIOConfig_SetInterruptPin(GPIO_TypeDef *port, uint16_t pin);


#endif /* INCLUDE_GPIOCONFIG_H_ */
