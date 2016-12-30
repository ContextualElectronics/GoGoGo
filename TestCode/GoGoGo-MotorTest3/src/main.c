

#include <stdio.h>
#include <stdlib.h>

#include "diag/Trace.h"

#include "Drivetrain.h"
#include "WheelTest.h"
#include "DelayTimer.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


int main(int argc, char* argv[]) {
	DelayTimer_Init();
	Drivetrain_Initialize();

	while (1) {
		WheelTest_FigureEight();
		DelayTimer_Sleep(TIMER_FREQUENCY_HZ * 4); // 4 second sleep

		WheelTest_SmallCircle();
		DelayTimer_Sleep(TIMER_FREQUENCY_HZ * 4); // 4 second sleep
	}
}
