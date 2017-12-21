// 
// 
// 

#include "Task_10MS.h"
#include "SW.h"
#include "PREFERENT.h"
#include "Timer_count.h"
#include "ADC.h"
#include "UARTDebugging.h"

void Task_10MS()
{
	if (IsTimeOut(SW_WaitTime) == 1) {
		SW();
	}
	ADCUpdateEvery10ms();
	DBG_RespondUART();
}

