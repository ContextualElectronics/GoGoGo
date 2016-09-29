#ifndef mock_GPIO_H
#define mock_GPIO_H

#include "fff.h"
#include "fff_unity_helper.h"
#include "GPIO.h"


DECLARE_FAKE_VOID_FUNC3(GPIO_DigitalWrite, GPIO_TypeDef*, uint16_t, uint16_t);
DECLARE_FAKE_VOID_FUNC3(GPIO_AnalogWrite, GPIO_TypeDef*, uint16_t, uint16_t);

void mock_GPIO_Init(void);
void mock_GPIO_Verify(void);
void mock_GPIO_Destroy(void);

#endif // mock_GPIO_H
