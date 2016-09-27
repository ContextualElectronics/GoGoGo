

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "diag/Trace.h"

#include "Wheel.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"



void delay(void);


void delay(void) {
	uint32_t i = 1234567890;

	while (i > 0) {
		i--;
	}
}

int main(int argc, char* argv[]) {
	Wheel_Initialize();

	while (1) {
		Wheel_TurnLeftwheel(true, 50, 100);
		Wheel_TurnRightwheel(true, 50, 100);
		delay();
	}
}

#pragma GCC diagnostic pop

