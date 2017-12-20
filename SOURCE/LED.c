#include "LED.h"
#include "PREFERENT.h"
#include "RAM.h"
#include "FLAG.h"
#include "IO.h"
#include "Timer_count.h"
void LED_Init()
{
	resetFlagLED();
}
void LED()
{
	if (g_bF_Led_Error == 1)
	{
		if (TSTFLAG(g_bF_Led_State) == 0) {
			IOPort_Write(D_13, g_bF_Led_State);
			StartTimer(LedBlinkingWaitTimeMS, 20); /* Turn off led 2s */
			SETFLAG(g_bF_Led_State);
		}
		else {
			IOPort_Write(D_13, g_bF_Led_State);
			StartTimer(LedBlinkingWaitTimeMS, 20); /* Turn on led 2s */
			CLRFLAG(g_bF_Led_State);
		}
	}
	else
		if (g_bF_Led_Btn1 == 1)
		{
			IOPort_Write(D_13, HIGH);
		}
		else
			if (g_bF_Led_Normal == 1)
			{
				if (TSTFLAG(g_bF_Led_State) == 0) {
					IOPort_Write(D_13, g_bF_Led_State);
					IOPort_Write(D_12, g_bF_Led_State);
					StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn on led 0.5s */
					SETFLAG(g_bF_Led_State);
				}
				else {
					IOPort_Write(D_13, g_bF_Led_State);
					IOPort_Write(D_12, g_bF_Led_State);
					StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn off led 0.5s */
					CLRFLAG(g_bF_Led_State);
				}
			}
			else
			{
				IOPort_Write(D_13, LOW);
			}

	
}
void resetFlagLED()
{
	g_bF_Led_Normal = 1;
	g_bF_Led_Error = 0;
	g_bF_Led_State = 0;
	g_bF_Led_Btn1 = 0;
}