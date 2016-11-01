/*
 * WheelEncoder.h
 *
 *  Created on: Oct 30, 2016
 *      Author: vagrant
 */

#ifndef INCLUDE_WHEELENCODER_H_
#define INCLUDE_WHEELENCODER_H_

#include <stdint.h>
#include <stdbool.h>


bool WheelEncoder_IsStepping(uint32_t encoderCount, uint32_t steps);

void WheelEncoder_SetIsStopped(bool value);
bool WheelEncoder_GetIsStopped(void);

void WheelEncoder_SetLeftWheelCounter(uint32_t value);
uint32_t WheelEncoder_GetLeftWheelCounter(void);

void WheelEncoder_SetRightWheelCounter(uint32_t value);
uint32_t WheelEncoder_GetRightWheelCounter(void);


#endif /* INCLUDE_WHEELENCODER_H_ */
