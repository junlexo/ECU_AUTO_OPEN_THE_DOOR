// 
// 
// 

#include "Task_1MS.h"
#include "UARTDebugging.h"

void Task_1MS()
{
	/*****   STEP MOTOR       ******/
#if STEPMOTOR == ON
	STEP_MANNER();
#endif
	DBG_ReadFrame();
}


