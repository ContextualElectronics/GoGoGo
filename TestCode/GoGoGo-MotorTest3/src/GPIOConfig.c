#include "GPIOConfig.h"
#include "cmsis_device.h"


void GPIOConfig_OutputPin(GPIO_TypeDef *port, uint16_t pin) {

	if (port == GPIOA) {
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	}
	else if (port == GPIOB) {
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	}
	else if (port == GPIOC) {
		RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	}
	else {
		// TODO?
	}

	GPIO_InitTypeDef GPIOInitStructure;

	GPIOInitStructure.GPIO_Pin = pin;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(port, &GPIOInitStructure);
}

void GPIOConfig_InputPin(GPIO_TypeDef *port, uint16_t pin) {
	GPIO_InitTypeDef GPIOInitStructure;

	GPIOInitStructure.GPIO_Pin = pin;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	if (port == GPIOC && pin == GPIO_Pin_13) {
		GPIOInitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	}

	GPIO_Init(port, &GPIOInitStructure);
}

void GPIOConfig_SetPWMPin(GPIO_TypeDef *port, uint16_t pin) {
	GPIO_InitTypeDef GPIOInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;;
	TIM_OCInitTypeDef        TIM_OCInitStructure;

	GPIOInitStructure.GPIO_Pin = pin;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIOInitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(port, &GPIOInitStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = (SystemCoreClock / 1000) - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	if (port == GPIOB) {
		if (pin == GPIO_Pin_4) {
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

			GPIO_PinAFConfig(port, GPIO_PinSource4, GPIO_AF_1);
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
			TIM_Cmd(TIM3, ENABLE);

			TIM_OC1Init(TIM3, &TIM_OCInitStructure);

			TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
			TIM_SelectOnePulseMode(TIM3, TIM_OPMode_Repetitive);
		}

		if (pin == GPIO_Pin_1) {
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

			GPIO_PinAFConfig(port, GPIO_PinSource1, GPIO_AF_0);
			TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
			TIM_Cmd(TIM14, ENABLE);

			TIM_OC1Init(TIM14, &TIM_OCInitStructure);

			TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);
			TIM_SelectOnePulseMode(TIM14, TIM_OPMode_Repetitive);
		}
	}
}

void GPIOConfig_SetInterruptPin(GPIO_TypeDef *port, uint16_t pin) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	if (port == GPIOA) {
		if (pin == GPIO_Pin_10) {
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource10);
			EXTI_InitStructure.EXTI_Line = EXTI_Line10;
		}

		if (pin == GPIO_Pin_9) {
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource9);
			EXTI_InitStructure.EXTI_Line = EXTI_Line9;
		}
	}
	else if (port == GPIOB) {
		if (pin == GPIO_Pin_8) {
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);
			EXTI_InitStructure.EXTI_Line = EXTI_Line8;
		}

		if (pin == GPIO_Pin_9) {
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource9);
			EXTI_InitStructure.EXTI_Line = EXTI_Line9;
		}
	}
	else if (port == GPIOC) {
		if (pin == GPIO_Pin_13) {
			SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);
			EXTI_InitStructure.EXTI_Line = EXTI_Line13;
		}
	}

	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
