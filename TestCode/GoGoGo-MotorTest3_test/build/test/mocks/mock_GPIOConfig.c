#include <string.h>
#include "fff.h"
#include "mock_GPIOConfig.h"

DEFINE_FAKE_VOID_FUNC2(GPIOConfig_OutputPin, GPIO_TypeDef*, uint16_t);
DEFINE_FAKE_VOID_FUNC2(GPIOConfig_InputPin, GPIO_TypeDef*, uint16_t);
DEFINE_FAKE_VOID_FUNC2(GPIOConfig_SetPWMPin, GPIO_TypeDef*, uint16_t);
DEFINE_FAKE_VOID_FUNC2(GPIOConfig_SetInterruptPin, GPIO_TypeDef*, uint16_t);

void mock_GPIOConfig_Init(void)
{
    FFF_RESET_HISTORY();
    RESET_FAKE(GPIOConfig_OutputPin)
    RESET_FAKE(GPIOConfig_InputPin)
    RESET_FAKE(GPIOConfig_SetPWMPin)
    RESET_FAKE(GPIOConfig_SetInterruptPin)
}
void mock_GPIOConfig_Verify(void)
{
}
void mock_GPIOConfig_Destroy(void)
{
}
