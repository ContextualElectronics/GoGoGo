
#ifndef INCLUDE_WHEEL_H_
#define INCLUDE_WHEEL_H_

#include "GPIOConfig.h"
#include "GPIO.h"
#include "cmsis_device.h"

#include <stdbool.h>
#include <stdint.h>

// Arduino UNO uses Pins 0, 2, 5, 6, 8

// Left Wheel Pins
// 4 = Stdby   = PB5
// 2 = Decoder = PB9
// 5 = PWM     = PB4
// 6 = In1     = PB10
// 8 = In2     = PB3

// Right Wheel Pins
//  = Stby     = PB15
//  = Decoder  = PB8
//  = PWM      = PB1
//  = In1      = PB14
//  = In2      = PB13

// USER BUTTON = PC13

void Wheel_Initialize(void);
void Wheel_StopLeftWheel(void);
void Wheel_StopRightWheel(void);
void Wheel_Straight(bool forward, uint16_t velocity);
void Wheel_TurnLeftWheel(bool forward, uint16_t velocity);
void Wheel_TurnRightWheel(bool forward, uint16_t velocity);

void EXTI4_15_IRQHandler(void);


#endif /* INCLUDE_WHEEL_H_ */
