#ifndef mock_GPIOConfig_H
#define mock_GPIOConfig_H

#include "fff.h"
#include "fff_unity_helper.h"
#include "GPIOConfig.h"


DECLARE_FAKE_VOID_FUNC2(GPIOConfig_OutputPin, GPIO_TypeDef*, uint16_t);
DECLARE_FAKE_VOID_FUNC2(GPIOConfig_InputPin, GPIO_TypeDef*, uint16_t);
DECLARE_FAKE_VOID_FUNC2(GPIOConfig_SetPWMPin, GPIO_TypeDef*, uint16_t);
DECLARE_FAKE_VOID_FUNC2(GPIOConfig_SetInterruptPin, GPIO_TypeDef*, uint16_t);

void mock_GPIOConfig_Init(void);
void mock_GPIOConfig_Verify(void);
void mock_GPIOConfig_Destroy(void);

#endif // mock_GPIOConfig_H
