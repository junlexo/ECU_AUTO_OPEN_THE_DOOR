// 
// 
// 

#include "Task_1S.h"
#include "PREFERENT.h"
#include "IO.h"
#include "Timer_count.h"

void Task_1S()
{
	if (IsTimeOut(LedBlinkingWaitTime) == 1) {
		blinkLED();
	}
}

/*Example*/

void blinkLED(){
	static uint8_t f_ledState = 0;
	if (TSTFLAG(f_ledState) == 0) {
		IOPort_Write(D_13, f_ledState);
		StartTimer(LedBlinkingWaitTime, 1); /* Turn on led 1s */
		SETFLAG(f_ledState);
	}
	else {
		IOPort_Write(D_13, f_ledState);
		StartTimer(LedBlinkingWaitTime, 2); /* Turn off led 2s */
		CLRFLAG(f_ledState);
	}
}

