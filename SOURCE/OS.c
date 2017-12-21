
#include "OS.h"
#include "RAM.h"
#include "FLAG.h"
#include "PREFERENT.h"

static void OS_ControlTask();

void OS_Init()
{
	OS_TimerCounter_Init();
	RegisterOSTask(&OS_ControlTask);
}

void OS_ControlTask()
{
	if (TSTFLAG(bF_TaskRunning) == 0) {
		return;
	}
	else {
		if (TSTFLAG(bF_Task_100US) == 1)
		{
			Task_100US();
			CLRFLAG(bF_Task_100US);
		}

		if (TSTFLAG(bF_Task_1MS) == 1)
		{
			Task_1MS();
			CLRFLAG(bF_Task_1MS);
		}

		if (TSTFLAG(bF_Task_10MS) == 1)
		{
			Task_10MS();
			CLRFLAG(bF_Task_10MS);
		}

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
