
#include "GPIO.h"
#include "GPIOConfig.h"
#include "cmsis_device.h"
#include "stm32f0xx_gpio.h"


void GPIO_DigitalWrite(GPIO_TypeDef *port, uint16_t pin, uint16_t value) {
	if (value == HIGH) {
		GPIO_SetBits(port, pin);
	}

	if (value == LOW) {
		GPIO_ResetBits(port, pin);
	}
}

void GPIO_AnalogWrite(GPIO_TypeDef *port, uint16_t pin, uint16_t value) {
	volatile uint16_t PwmPeriod = (SystemCoreClock / 1000) - 1;
	volatile uint16_t ChannelPulse = (uint16_t) (((uint32_t)value * (PwmPeriod - 1)) / 100);

	if (port == GPIOB) {
		if (pin == GPIO_Pin_4) {
			TIM3->CCR1 = ChannelPulse;
		}

		if (pin == GPIO_Pin_1) {
			TIM14->CCR1 = ChannelPulse;
		}
	}
}
