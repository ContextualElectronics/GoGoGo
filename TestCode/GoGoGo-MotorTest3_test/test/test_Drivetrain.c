#include "unity.h"
#include "fff.h"
#include "Drivetrain.h"
#include <stdint.h>

#include "mock_Wheel.h"

#include "cmsis_device.h"

void setUp(void) {

}
 
void tearDown(void) {

}

void test_whenInitializing_thenWheelsAreStopped() {
    Drivetrain_Initialize();

    TEST_ASSERT_TRUE(1 == Wheel_StopLeftWheel_fake.call_count);
    TEST_ASSERT_TRUE(1 == Wheel_StopRightWheel_fake.call_count);
}

void test_whenFullStop_thenWheelsAreStoppedImmediately() {
    Drivetrain_FullStop();
    
    TEST_ASSERT_TRUE(1 == Wheel_StopLeftWheel_fake.call_count);
    TEST_ASSERT_TRUE(1 == Wheel_StopRightWheel_fake.call_count);
    TEST_ASSERT_TRUE(0 == Drivetrain_GetVelocity());
    TEST_ASSERT_TRUE(0 == Drivetrain_GetDirection());
}

void test_whenMovingLeft_thenMaximumTurnNoMoreThanNegative90() {
    Drivetrain_Move(-120, 100);

    TEST_ASSERT_EQUAL_INT8(-90, Drivetrain_GetDirection());
}

void test_whenMovingRight_thenMaximumTurnNoMoreThan90() {
    Drivetrain_Move(120, 100);

    TEST_ASSERT_EQUAL_INT8(90, Drivetrain_GetDirection());
}


