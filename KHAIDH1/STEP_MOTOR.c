// 
// 
// 

#include "STEP_MOTOR.h"
void STEP_PWM()
{
 
	if ( g_bF_StepPWM == 1)
	{
		IOPort_Write(D_9, HIGH);
		g_bF_StepPWM = 0;
	}
	else
	{
		IOPort_Write(D_9, LOW);
		g_bF_StepPWM = 1;
	}

}


