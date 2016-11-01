#include "WheelEncoder.h"


volatile bool isStopped = true;
volatile uint32_t leftWheelCounter;
volatile uint32_t rightWheelCounter;

bool WheelEncoder_IsStepping(uint32_t encoderCount, uint32_t steps) {
	return (encoderCount < steps);
}

void WheelEncoder_SetIsStopped(bool value) {
	isStopped = value;
}

bool WheelEncoder_GetIsStopped(void) {
	return isStopped;
}

void WheelEncoder_SetLeftWheelCounter(uint32_t value) {
	leftWheelCounter = value;
}

uint32_t WheelEncoder_GetLeftWheelCounter(void) {
	return leftWheelCounter;
}

void WheelEncoder_SetRightWheelCounter(uint32_t value) {
	rightWheelCounter = value;
}

uint32_t WheelEncoder_GetRightWheelCounter(void) {
	return rightWheelCounter;
}
