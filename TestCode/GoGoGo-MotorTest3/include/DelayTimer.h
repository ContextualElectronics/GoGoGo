
#ifndef INCLUDE_DELAYTIMER_H_
#define INCLUDE_DELAYTIMER_H_

#include "cmsis_device.h"
#include <stdint.h>

#define TIMER_FREQUENCY_HZ (1000u)

volatile uint32_t DelayTimer_DelayCount;

void DelayTimer_Init(void);
void DelayTimer_Sleep(uint32_t ticks);

#endif /* INCLUDE_DELAYTIMER_H_ */
