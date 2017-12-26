// 
// 
// 

#include "Task_10MS.h"
#include "SW.h"
#include "PREFERENT.h"
#include "Timer_count.h"
#include "ADC.h"
#include "UARTDebugging.h"
#include "EEPROM.h"

void Task_10MS()
{
	if (IsTimeOut(SW_WaitTime) == 1) {
		SW();
	}
	ADCUpdateEvery10ms();
	
	if (TSTFLAG(g_bF_eeprom_writeData) == 1) {
		EEPROM_SaveAllData();
	}
}

void HandleAppTask_10MS() {
	DBG_RespondUART();
}
