
#include "Wheel.h"
#include "WheelEncoder.h"


static void LeftWheel_Init(void);
static void RightWheel_Init(void);


void Wheel_Initialize(void) {
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
		WheelEncoder_SetLeftWheelCounter(WheelEncoder_GetLeftWheelCounter()+1);
	}

	if ((EXTI->PR & EXTI_PR_PR8) != (uint32_t)0) {
		EXTI->PR = EXTI_PR_PR8;
		WheelEncoder_SetRightWheelCounter(WheelEncoder_GetRightWheelCounter()+1);
	}

	if ((EXTI->PR & EXTI_PR_PR13) != (uint32_t)0) {
		EXTI->PR = EXTI_PR_PR13;
		WheelEncoder_SetIsStopped(!WheelEncoder_GetIsStopped());
	}

	NVIC_ClearPendingIRQ(EXTI4_15_IRQn);
}

void Wheel_Straight(bool forward, uint16_t velocity, uint32_t steps) {
	if (WheelEncoder_GetIsStopped())
		return;

	GPIO_AnalogWrite(GPIOB, GPIO_Pin_4, velocity); // LeftWheel Velocity
	GPIO_AnalogWrite(GPIOB, GPIO_Pin_1, velocity); // RightWheel Velocity

	GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, HIGH); // LeftWheel Enabled
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_15, HIGH); // RightWheel Enabled

	WheelEncoder_SetLeftWheelCounter(0);

	while (WheelEncoder_IsStepping(WheelEncoder_GetLeftWheelCounter(), steps)) {
		if (WheelEncoder_GetIsStopped())
			break;

		if (forward) {
			// LeftWheel
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, HIGH);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, LOW);

			// RightWheel
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, LOW);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, HIGH);
		}
		else {
			// LeftWheel
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, LOW);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, HIGH);

			// RightWheel
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, HIGH);
			GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, LOW);
		}
	}

	LeftWheel_Init();
	RightWheel_Init();
}

void Wheel_TurnLeftwheel(bool forward, uint16_t velocity, uint32_t steps) {
	if (WheelEncoder_GetIsStopped())
		return;

	GPIO_AnalogWrite(GPIOB, GPIO_Pin_4, velocity);

	WheelEncoder_SetLeftWheelCounter(0);

	while (WheelEncoder_IsStepping(WheelEncoder_GetLeftWheelCounter(), steps)) {
		if (WheelEncoder_GetIsStopped())
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

	LeftWheel_Init();
}

void Wheel_TurnRightwheel(bool forward, uint16_t velocity, uint32_t steps) {
	if (WheelEncoder_GetIsStopped())
		return;

	GPIO_AnalogWrite(GPIOB, GPIO_Pin_1, velocity);

	WheelEncoder_SetRightWheelCounter(0);

	while (WheelEncoder_IsStepping(WheelEncoder_GetRightWheelCounter(), steps)) {
		if (WheelEncoder_GetIsStopped())
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

	RightWheel_Init();
}

static void LeftWheel_Init(void) {
	GPIO_AnalogWrite(GPIOB, GPIO_Pin_4, 0);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, LOW);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, LOW);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, LOW);
}

static void RightWheel_Init(void) {
	GPIO_AnalogWrite(GPIOB, GPIO_Pin_1, 0);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, LOW);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, LOW);
	GPIO_DigitalWrite(GPIOB, GPIO_Pin_15, LOW);
}
