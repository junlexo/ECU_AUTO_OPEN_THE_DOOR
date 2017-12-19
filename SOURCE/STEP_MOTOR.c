// 
// 
// 

#include "STEP_MOTOR.h"
void STEP_PWM()
{
 
	if (TSTFLAG(g_bF_StepPWM) == 1)
	{
		IOPort_Write(D_13, HIGH);
		CLRFLAG(g_bF_StepPWM);
	}
	else
	{
		IOPort_Write(D_13, LOW);
		SETFLAG(g_bF_StepPWM);
	}

}


