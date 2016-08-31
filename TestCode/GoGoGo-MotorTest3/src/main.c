

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

void setup(void);
void EXTI4_15_IRQHandler(void);
void delay(void);
void leftwheel (bool forward, uint16_t velocity, uint32_t steps);
void rightwheel(bool forward, uint16_t velocity, uint32_t steps);


uint32_t leftWheelCounter = 0;
uint32_t rightWheelCounter = 0;
bool isStopped = true;


void setup(void) {
	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_5);  // Stdby
	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_10); // In1
	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_3);  // In2
	GPIOConfig_InputPin(GPIOB, GPIO_Pin_9);  // Decoder
	GPIOConfig_SetPWMPin(GPIOB, GPIO_Pin_4);  // PWM
	GPIOConfig_SetInterruptPin(GPIOB, GPIO_Pin_9); // Decoder now an interrupt!

	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_15); // Stdby
	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_14); // In1
	GPIOConfig_OutputPin(GPIOB, GPIO_Pin_13); // In2
	GPIOConfig_InputPin(GPIOB, GPIO_Pin_8);   // Decoder
	GPIOConfig_SetPWMPin(GPIOB, GPIO_Pin_1);  // PWM
	GPIOConfig_SetInterruptPin(GPIOB, GPIO_Pin_8); // Decoder now an interrupt!

	GPIOConfig_InputPin(GPIOC, GPIO_Pin_13);  // USER Button
	GPIOConfig_SetInterruptPin(GPIOC, GPIO_Pin_13); // Button is now an interrupt!
}

void EXTI4_15_IRQHandler(void) {
	if ((EXTI->PR & EXTI_PR_PR9) != (uint32_t)0) {
		EXTI->PR = EXTI_PR_PR9;
		leftWheelCounter++;
	}

	if ((EXTI->PR & EXTI_PR_PR8) != (uint32_t)0) {
		EXTI->PR = EXTI_PR_PR8;
		rightWheelCounter++;
	}

	if ((EXTI->PR & EXTI_PR_PR13) != (uint32_t)0) {
		EXTI->PR = EXTI_PR_PR13;
		isStopped = !isStopped;
	}

	NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
}

void delay(void) {
	uint32_t i = 1234567890;

	while (i > 0) {
		i--;
	}
}

void leftwheel(bool forward, uint16_t velocity, uint32_t steps) {
	if (isStopped)
		return;

	GPIO_AnalogWrite(GPIOB, GPIO_Pin_4, velocity);

	leftWheelCounter = 0;

	while (leftWheelCounter < steps) {
		if (isStopped)
			break;

		GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, HIGH);

		if (forward) {
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, HIGH);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, LOW);
		}
		else {
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, LOW);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, HIGH);
		}
	}

	GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, HIGH);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, HIGH);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, LOW);
}

void rightwheel(bool forward, uint16_t velocity, uint32_t steps) {
	if (isStopped)
		return;

	GPIO_AnalogWrite(GPIOB, GPIO_Pin_1, velocity);

	rightWheelCounter = 0;

	while (rightWheelCounter < steps) {
		if (isStopped)
			break;

		GPIO_DigitalWrite(GPIOB, GPIO_Pin_15, HIGH);

		if (forward) {
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, LOW);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, HIGH);
		}
		else {
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, HIGH);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, LOW);
		}
	}

	GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, HIGH);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, HIGH);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_15, LOW);
}

int main(int argc, char* argv[]) {
	setup();

	while (1) {
		leftwheel(true, 50, 100);
		rightwheel(true, 50, 100);
		delay();
	}
}

#pragma GCC diagnostic pop

