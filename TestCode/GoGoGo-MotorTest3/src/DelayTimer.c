#include "DelayTimer.h"


void DelayTimer_Tick(void);

volatile uint32_t DelayTimer_DelayCount;


void DelayTimer_Init(void) {
	SysTick_Config(SystemCoreClock / TIMER_FREQUENCY_HZ);
}

void DelayTimer_Sleep(uint32_t ticks) {
  DelayTimer_DelayCount = ticks;

  while (DelayTimer_DelayCount != 0u)
    ;
}

void DelayTimer_Tick(void) {
  if (DelayTimer_DelayCount != 0u) {
    --DelayTimer_DelayCount;
  }
}

void SysTick_Handler(void) {
  DelayTimer_Tick();
}
