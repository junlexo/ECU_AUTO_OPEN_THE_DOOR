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
	
	if (BTN1_STATUS == ADC_BTN_PRESS && BTN2_STATUS == ADC_BTN_PRESS) {
		EEPROM_SaveAllData();
	}
}

void HandleAppTask_10MS() {
	DBG_RespondUART();
}
