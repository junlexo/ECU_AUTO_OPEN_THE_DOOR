// 
// 
// 

#include "Task_100MS.h"
#include "LED.h"
#include "PREFERENT.h"
#include "Timer_count.h"

void Task_100MS()
{
	if (IsTimeOut(LedBlinkingWaitTimeMS) == 1) {
		LED();
	}
	
}
