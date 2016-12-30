#include "Drivetrain.h"
#include "Wheel.h"
#include <stdbool.h>


volatile int8_t robotDirection;
volatile int8_t robotVelocity;


int8_t Drivetrain_GetDirection(void) {
	return robotDirection;
}

int8_t Drivetrain_GetVelocity(void) {
	return robotVelocity;
}

void Drivetrain_Initialize(void) {
	Wheel_Initialize();
	Wheel_StopLeftWheel();
	Wheel_StopRightWheel();
}

void Drivetrain_FullStop(void) {
	Wheel_StopLeftWheel();
	Wheel_StopRightWheel();
}

void Drivetrain_Move(int8_t direction, int16_t velocity) {
	robotDirection = direction;

	if (direction < -90) {
		robotDirection = -90;
	}

	if (direction > 90) {
		robotDirection = 90;
	}

	// TODO figure out algorithm for turning & moving forward/backward
	// reduce the inside wheel velocity based on the direction angle
	// LV 100  RV 100  DIR 0 == straight
	// LV 0  RV 100 DIR -90 == full left turn
	// LV 100  RV 0  DIR 90 == full right turn

	int16_t absoluteVelocity = abs(velocity);
	double percentage = (double)(90 - abs(robotDirection)) / 90;
	double calculatedVelocity = percentage * absoluteVelocity;
	bool isForward = velocity > 0;

	if (velocity == 0) {
		Wheel_StopLeftWheel();
		Wheel_StopRightWheel();
		return;
	}

	if (robotDirection < 0) {
		Wheel_TurnRightWheel(isForward, absoluteVelocity);
		Wheel_TurnLeftWheel(isForward, (int)calculatedVelocity);
	}
	else if (robotDirection > 0) {
		Wheel_TurnRightWheel(isForward, (int)calculatedVelocity);
		Wheel_TurnLeftWheel(isForward, absoluteVelocity);
	}
	else {
		Wheel_TurnRightWheel(isForward, absoluteVelocity);
		Wheel_TurnLeftWheel(isForward, absoluteVelocity);
	}
}
