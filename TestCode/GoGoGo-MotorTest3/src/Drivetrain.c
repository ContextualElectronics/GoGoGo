#include "Drivetrain.h"
#include "Wheel.h"


volatile int8_t robotDirection;
volatile int8_t robotVelocity;


int8_t Drivetrain_GetDirection(void) {
	return robotDirection;
}

int8_t Drivetrain_GetVelocity(void) {
	return robotVelocity;
}

void Drivetrain_Initialize(void) {
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
}
