#include <string.h>
#include "fff.h"
#include "mock_GPIO.h"

DEFINE_FAKE_VOID_FUNC3(GPIO_DigitalWrite, GPIO_TypeDef*, uint16_t, uint16_t);
DEFINE_FAKE_VOID_FUNC3(GPIO_AnalogWrite, GPIO_TypeDef*, uint16_t, uint16_t);

void mock_GPIO_Init(void)
{
    FFF_RESET_HISTORY();
    RESET_FAKE(GPIO_DigitalWrite)
    RESET_FAKE(GPIO_AnalogWrite)
}
void mock_GPIO_Verify(void)
{
}
void mock_GPIO_Destroy(void)
{
}
