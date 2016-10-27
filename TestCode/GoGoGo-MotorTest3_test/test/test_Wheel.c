#include "unity.h"
#include "Wheel.h"
#include <stdbool.h>

#include "mock_GPIO.h"
#include "mock_GPIOConfig.h"
#include "cmsis_device.h"


void test_whenWheelsAreInitialized_thenWeSetTheCorrectPins() {
	Wheel_Initialize();

	TEST_ASSERT_TRUE(0 < GPIOConfig_OutputPin_fake.call_count);
}

void test_whenWheelsGoForward_thenWeSetTheCorrectDirectionPinsForLeftWheel() {
    Wheel_Straight(true, 100, 6);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, HIGH);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, LOW);

    TEST_ASSERT_TRUE(GPIO_DigitalWrite_fake.call_count >= 2);
    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_10 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[2]);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[3]);
    TEST_ASSERT_TRUE(GPIO_Pin_3 == GPIO_DigitalWrite_fake.arg1_history[3]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[3]);
}

void test_whenWheelsGoForward_thenWeSetTheEnablePinForLeftWheel() {
    Wheel_Straight(true, 100, 6);

    // GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_5 == GPIO_DigitalWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[0]);
}

void test_whenWheelsGoForward_thenWeSetTheVelocityOfTheLeftWheel() {
    Wheel_Straight(true, 100, 6);

    // GPIO_AnalogWrite(GPIOB, GPIO_Pin_4, velocity);

    TEST_ASSERT_TRUE(GPIOB == GPIO_AnalogWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_4 == GPIO_AnalogWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(100 == GPIO_AnalogWrite_fake.arg2_history[0]);
}

void test_whenWheelsGoForward_thenWeSetTheCorrectDirectionPinsForRightWheel() {
    Wheel_Straight(true, 100, 6);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, LOW);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[4]);
    TEST_ASSERT_TRUE(GPIO_Pin_14 == GPIO_DigitalWrite_fake.arg1_history[4]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[4]);
    
    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[5]);
    TEST_ASSERT_TRUE(GPIO_Pin_13 == GPIO_DigitalWrite_fake.arg1_history[5]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[5]);
}

void test_whenWheelsGoForward_thenWeSetTheEnablePinForRightWheel() {
    Wheel_Straight(true, 100, 6);

    // GPIO_DigitalWrite(GPIOB, GPIO_Pin_15, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_15 == GPIO_DigitalWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[1]);
}

void test_whenWheelsGoForward_thenWeSetTheVelocityOfTheRightWheel() {
    Wheel_Straight(true, 100, 6);

    // GPIO_AnalogWrite(GPIOB, GPIO_Pin_1, velocity);

    TEST_ASSERT_TRUE(GPIOB == GPIO_AnalogWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_1 == GPIO_AnalogWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(100 == GPIO_AnalogWrite_fake.arg2_history[1]);
}

void test_whenWheelsGoBackward_thenWeSetTheCorrectDirectionPinsForLeftWheel() {
    Wheel_Straight(false, 100, 6);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, LOW);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_10 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[2]);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[3]);
    TEST_ASSERT_TRUE(GPIO_Pin_3 == GPIO_DigitalWrite_fake.arg1_history[3]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[3]);
}

void test_whenWheelsGoBackward_thenWeSetTheCorrectDirectionPinsForRightWheel() {
    Wheel_Straight(false, 100, 6);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, HIGH);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, LOW);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[4]);
    TEST_ASSERT_TRUE(GPIO_Pin_14 == GPIO_DigitalWrite_fake.arg1_history[4]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[4]);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[5]);
    TEST_ASSERT_TRUE(GPIO_Pin_13 == GPIO_DigitalWrite_fake.arg1_history[5]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[5]);
}

void test_whenWheelsGoStraight_thenWeInitializeTheWheelStepCounter() {
    
}

