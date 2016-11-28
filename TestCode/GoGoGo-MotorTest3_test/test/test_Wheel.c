#include "unity.h"
#include "fff.h"
#include "Wheel.h"
#include <stdbool.h>
#include <stdint.h>

#include "mock_GPIO.h"
#include "mock_GPIOConfig.h"
#include "mock_WheelEncoder.h"

#include "cmsis_device.h"


void setUp(void) {

    RESET_FAKE(WheelEncoder_IsStepping);
    RESET_FAKE(WheelEncoder_GetIsStopped);
    RESET_FAKE(WheelEncoder_SetIsStopped);
}
 
void tearDown(void) {

}

void test_whenWheelsAreInitialized_thenWeSetTheCorrectPins() {
    Wheel_Initialize();

    TEST_ASSERT_TRUE(0 < GPIOConfig_OutputPin_fake.call_count);
}

void test_whenLeftWheelGoesForward_thenWeSetTheCorrectDirectionPins() {
    Wheel_TurnLeftWheel(true, 100);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, HIGH);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, LOW);

    TEST_ASSERT_TRUE(GPIO_DigitalWrite_fake.call_count >= 2);
    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_10 == GPIO_DigitalWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[1]);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_3 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[2]);
}

void test_whenLeftWheelGoesForward_thenWeSetTheEnablePin() {
    Wheel_TurnLeftWheel(true, 100);

    // GPIO_DigitalWrite(GPIOB, GPIO_Pin_5, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_5 == GPIO_DigitalWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[0]);
}

void test_whenLeftWheelGoesForward_thenWeSetTheVelocity() {
    Wheel_TurnLeftWheel(true, 100);

    // GPIO_AnalogWrite(GPIOB, GPIO_Pin_4, velocity);

    TEST_ASSERT_TRUE(GPIOB == GPIO_AnalogWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_4 == GPIO_AnalogWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(100 == GPIO_AnalogWrite_fake.arg2_history[0]);
}

void test_whenRightWheelGoesForward_thenWeSetTheCorrectDirectionPins() {
    Wheel_TurnRightWheel(true, 100);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, LOW);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_14 == GPIO_DigitalWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[1]);
    
    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_13 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[2]);
}

void test_whenRightWheelGoesForward_thenWeSetTheEnablePin() {
    Wheel_TurnRightWheel(true, 100);

    // GPIO_DigitalWrite(GPIOB, GPIO_Pin_15, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_15 == GPIO_DigitalWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[0]);
}

void test_whenRightWheelGoesForward_thenWeSetTheVelocity() {
    Wheel_TurnRightWheel(true, 100);

    // GPIO_AnalogWrite(GPIOB, GPIO_Pin_1, velocity);

    TEST_ASSERT_TRUE(GPIOB == GPIO_AnalogWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_1 == GPIO_AnalogWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(100 == GPIO_AnalogWrite_fake.arg2_history[0]);
}

void test_whenLeftWheelGoesBackward_thenWeSetTheCorrectDirectionPins() {
    Wheel_TurnLeftWheel(false, 100);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_10, LOW);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_3, HIGH);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_10 == GPIO_DigitalWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[1]);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_3 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[2]);
}

void test_whenRightWheelGoesBackward_thenWeSetTheCorrectDirectionPins() {
    Wheel_TurnRightWheel(false, 100);

    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_14, HIGH);
    //GPIO_DigitalWrite(GPIOB, GPIO_Pin_13, LOW);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_14 == GPIO_DigitalWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(HIGH == GPIO_DigitalWrite_fake.arg2_history[1]);

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_13 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[2]);
}

void test_WhenWheelsGoStraight_thenWeExitIfIsStopped() {
    WheelEncoder_GetIsStopped_fake.return_val = true;    

    Wheel_Straight(true, 100);

    // Explicitly stop the wheels

    TEST_ASSERT_TRUE(2 == GPIO_AnalogWrite_fake.call_count); 
}

void test_WhenLeftWheelStops_thenWeSetVelocityToZero() {
    Wheel_StopLeftWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_AnalogWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_4 == GPIO_AnalogWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(0 == GPIO_AnalogWrite_fake.arg2_history[0]);
}

void test_WhenLeftWheelStops_thenWeSetPinIn1ToLow() {
    Wheel_StopLeftWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_10 == GPIO_DigitalWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[0]);
}

void test_whenLeftWheelStops_thenWeSetPinIn2ToLow() {
    Wheel_StopLeftWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_3 == GPIO_DigitalWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[1]);
}

void test_whenLeftWheelStops_thenWeSetPinStandbyToLow() {
    Wheel_StopLeftWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_5 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[2]);
}

void test_WhenRightWheelStops_thenWeSetVelocityToZero() {
    Wheel_StopRightWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_AnalogWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_1 == GPIO_AnalogWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(0 == GPIO_AnalogWrite_fake.arg2_history[0]);
}

void test_WhenRightWheelStops_thenWeSetPinIn1ToLow() {
    Wheel_StopRightWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[0]);
    TEST_ASSERT_TRUE(GPIO_Pin_14 == GPIO_DigitalWrite_fake.arg1_history[0]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[0]);
}

void test_whenRightWheelStops_thenWeSetPinIn2ToLow() {
    Wheel_StopRightWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[1]);
    TEST_ASSERT_TRUE(GPIO_Pin_13 == GPIO_DigitalWrite_fake.arg1_history[1]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[1]);
}

void test_whenRightWheelStops_thenWeSetPinStandbyToLow() {
    Wheel_StopRightWheel();

    TEST_ASSERT_TRUE(GPIOB == GPIO_DigitalWrite_fake.arg0_history[2]);
    TEST_ASSERT_TRUE(GPIO_Pin_15 == GPIO_DigitalWrite_fake.arg1_history[2]);
    TEST_ASSERT_TRUE(LOW == GPIO_DigitalWrite_fake.arg2_history[2]);
}
