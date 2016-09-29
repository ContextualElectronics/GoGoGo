#include "cmsis_device.h"
#include "mock_GPIOConfig.h"
#include "mock_GPIO.h"
#include "Wheel.h"
#include "unity.h"








void test_whenWheelsAreInitialized_thenWeSetTheCorrectPins() {

 Wheel_Initialize();



 if ((0 < GPIOConfig_OutputPin_fake.call_count)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (_U_UINT)((_U_UINT)(12)));};

}
