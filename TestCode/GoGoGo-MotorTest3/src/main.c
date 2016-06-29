

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "diag/Trace.h"

#include "GPIOConfig.h"
#include "GPIO.h"
#include "cmsis_device.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// Arduino UNO uses Pins 0, 2, 5, 6, 8
// 4 = Stdby   = PB5
// 2 = Decoder = PA10
// 5 = PWM     = PB4
// 6 = In1     = PB10
// 8 = In2     = PA9

void setup(void);
void EXTI4_15_IRQHandler(void);
void delay(void);
void leftwheel (bool forward, uint16_t velocity, uint32_t steps);

uint32_t counter = 0;

void setup(void) {
	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_5);  // Stdby
	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_10); // In1
	GPIOConfig_OutputPin(GPIOA, GPIO_Pin_9);  // In2
	GPIOConfig_InputPin(GPIOA, GPIO_Pin_10);  // Decoder
	GPIOConfig_SetPWMPin(GPIOB, GPIO_Pin_4);  // PWM
	GPIOConfig_SetInterruptPin(GPIOA, GPIO_Pin_10); // Decoder now an interrupt!
}

void EXTI4_15_IRQHandler(void) {
	if ((EXTI->PR & EXTI_PR_PR10) != (uint32_t)0) {
		EXTI->PR = EXTI_PR_PR10;
		counter++;
		NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
	}
}

void delay(void) {
	uint32_t i = 12345678;

	while (i > 0) {
		i--;
	}
}
void leftwheel (bool forward, uint16_t velocity, uint32_t steps) {
	GPIO_AnalogWrite(GPIOB, GPIO_Pin_4, velocity);

	counter = 0;

	while (counter < steps) {
		GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, HIGH);

		if (forward) {
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, HIGH);
			GPIO_DigitalWrite(GPIOA, GPIO_Pin_9, LOW);
		}
		else {
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, LOW);
			GPIO_DigitalWrite(GPIOA, GPIO_Pin_9, HIGH);
		}
	}

	GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, HIGH);
	GPIO_DigitalWrite(GPIOA, GPIO_Pin_9, HIGH);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, LOW);
}

int main(int argc, char* argv[]) {
	setup();

	while (1) {
		leftwheel(true, 50, 100);
		delay();
		leftwheel(false, 100, 20);
		delay();
	}
}

#pragma GCC diagnostic pop

