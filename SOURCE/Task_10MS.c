// 
// 
// 

#include "Task_10MS.h"
#include "SW.h"
#include "PREFERENT.h"
#include "Timer_count.h"

void Task_10MS()
{
	if (IsTimeOut(SW_WaitTime) == 1) {
		SW();
	}
}

