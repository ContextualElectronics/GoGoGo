#include "unity.h"
#include "Wheel.h"

#include "mock_GPIO.h"
#include "mock_GPIOConfig.h"
#include "cmsis_device.h"


void test_whenWheelsAreInitialized_thenWeSetTheCorrectPins() {
	Wheel_Initialize();

	TEST_ASSERT_TRUE(0 < GPIOConfig_OutputPin_fake.call_count);
}
