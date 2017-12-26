
#include "OS.h"
#include "RAM.h"
#include "FLAG.h"
#include "PREFERENT.h"

static void OS_runSystemTasks();


void OS_Init()
{
	OS_TimerCounter_Init();
	RegisterOSTask(&OS_runSystemTasks);
}

void OS_runSystemTasks()
{
	if (TSTFLAG(bF_TaskRunning) == 0) {
		return;
	}
	else {
		Task_1MS();

		if (TSTFLAG(bF_Task_10MS) == 1)
		{
			Task_10MS();
			CLRFLAG(bF_Task_10MS);
		}
	}
}

void OS_runApplicationTasks() {
	if (TSTFLAG(bF_TaskRunning) == 0) {
		return;
	}
	else {
		HandleAppTask_10MS();
		if (TSTFLAG(bF_Task_100MS) == 1)
		{
			Task_100MS();
			CLRFLAG(bF_Task_100MS);
		}

		if (TSTFLAG(bF_Task_1S) == 1)
		{
			Task_1S();
			CLRFLAG(bF_Task_1S);
		}
	}
}
