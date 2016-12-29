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

void test_WhenMoving90DegreesRight_thenInnerWheelDoesNotTurn() {
    Drivetrain_Move(90, 100);

    TEST_ASSERT_TRUE(Wheel_TurnRightWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL_INT(0, Wheel_TurnRightWheel_fake.arg1_val);

    TEST_ASSERT_TRUE(Wheel_TurnLeftWheel_fake.arg0_val);
    TEST_ASSERT_TRUE(100 == Wheel_TurnLeftWheel_fake.arg1_val);
}

void test_WhenMoving45DegreesRight_thenInnerWheelTurnsAtHalfSpeed() {
    Drivetrain_Move(45, 100);
    
    TEST_ASSERT_TRUE(Wheel_TurnRightWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(50, Wheel_TurnRightWheel_fake.arg1_val);

    TEST_ASSERT_TRUE(Wheel_TurnLeftWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(100, Wheel_TurnLeftWheel_fake.arg1_val);
}

void test_WhenMoving45DegreesLeft_thenInnerWheelTurnsAtHalfSpeed() {
    Drivetrain_Move(-45, 100);
    
    TEST_ASSERT_TRUE(Wheel_TurnRightWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(100, Wheel_TurnRightWheel_fake.arg1_val);

    TEST_ASSERT_TRUE(Wheel_TurnLeftWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(50, Wheel_TurnLeftWheel_fake.arg1_val);
}

void test_WhenMovingStraightAhead_thenVelocityIsSameOnBothWheels() {
    Drivetrain_Move(0, 100);
    
    TEST_ASSERT_TRUE(Wheel_TurnRightWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(100, Wheel_TurnRightWheel_fake.arg1_val);

    TEST_ASSERT_TRUE(Wheel_TurnLeftWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(100, Wheel_TurnLeftWheel_fake.arg1_val);
}

void test_WhenMovingStraightBack_thenVelocityIsSameOnBothWheels() {
    Drivetrain_Move(0, -100);
    
    TEST_ASSERT_FALSE(Wheel_TurnRightWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(100, Wheel_TurnRightWheel_fake.arg1_val);

    TEST_ASSERT_FALSE(Wheel_TurnLeftWheel_fake.arg0_val);
    TEST_ASSERT_EQUAL(100, Wheel_TurnLeftWheel_fake.arg1_val);

}

void test_WhenVelocityIs0_thenWheelsAreStopped() {
    Drivetrain_Move(0, 0);

    TEST_ASSERT_TRUE(Wheel_StopLeftWheel_fake.call_count == 1);
    TEST_ASSERT_TRUE(Wheel_StopRightWheel_fake.call_count == 1);
}
