#include "WheelTest.h"
#include "Drivetrain.h"
#include "DelayTimer.h"


void WheelTest_FigureEight(void) {
	Drivetrain_Move(-90, 100);
	DelayTimer_Sleep(4000); // 4 seconds

	Drivetrain_Move(90, 100);
	DelayTimer_Sleep(4000); // 4 seconds
}

void WheelTest_SmallCircle(void) {
	Drivetrain_Move(-70, 100);
	DelayTimer_Sleep(8000); // 8 seconds
}
