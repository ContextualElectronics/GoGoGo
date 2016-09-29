#include "cmsis_device.h"










void GPIOConfig_OutputPin(GPIO_TypeDef *port, uint16_t pin);

void GPIOConfig_InputPin(GPIO_TypeDef *port, uint16_t pin);

void GPIOConfig_SetPWMPin(GPIO_TypeDef *port, uint16_t pin);

void GPIOConfig_SetInterruptPin(GPIO_TypeDef *port, uint16_t pin);
