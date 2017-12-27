// 
// 
// 

#include "Task_100MS.h"
#include "LED.h"
#include "PREFERENT.h"
#include "Timer_count.h"
#include "DETECT.h"
void Task_100MS()
{
	if (IsTimeOut(LedBlinkingWaitTimeMS) == 1) {
		LED();
	}
	if (IsTimeOut(DETECT_WaitTime) == 1) {
		DETECT();
	}
	//FailSafe_CheckSYS();
}
