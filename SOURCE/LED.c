#include "LED.h"
#include "PREFERENT.h"
#include "RAM.h"
#include "FLAG.h"
#include "IO.h"
#include "Timer_count.h"

uint8_t pre_BTN1_STATUS = 0;
void LED_Init()
{
	resetFlagLED();
}
void LED()
{
	if (g_bF_SystemError == ERROR_VOLUME || g_bF_SystemError == ERROR_BTN)
	{
#ifdef OPTION2
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
#endif
		IOPort_Write(D_12, LOW);
		IOPort_Write(D_13, LOW);
	}
	else
		if (g_bF_UART_Error_Frame == 1)
		{
			IOPort_Write(D_12, LOW);
			if (TSTFLAG(g_bF_Led_State) == 0) {
				IOPort_Write(D_13, g_bF_Led_State);
				StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn on led 1s */
				SETFLAG(g_bF_Led_State);
			}
			else {
				IOPort_Write(D_13, g_bF_Led_State);
				StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn off led 1s */
				CLRFLAG(g_bF_Led_State);
			}
		}
		else
			if (BTN1_STATUS == 1)
			{
				IOPort_Write(D_12, HIGH);
				if (TSTFLAG(g_bF_Led_State) == 0) {
					IOPort_Write(D_13, g_bF_Led_State);
					StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn on led 1s */
					SETFLAG(g_bF_Led_State);
				}
				else {
					IOPort_Write(D_13, g_bF_Led_State);
					StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn off led 1s */
					CLRFLAG(g_bF_Led_State);
				}
			}
			else
				if (pre_BTN1_STATUS == 1 && BTN1_STATUS == 0)
				{
					IOPort_Write(D_12, LOW);
					if (TSTFLAG(g_bF_Led_State) == 0) {
						IOPort_Write(D_13, g_bF_Led_State);
						StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn on led 1s */
						SETFLAG(g_bF_Led_State);
					}
					else {
						IOPort_Write(D_13, g_bF_Led_State);
						StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn off led 1s */
						CLRFLAG(g_bF_Led_State);
					}
				}
				else
					if (BTN1_STATUS == 2)
					{
						if (TSTFLAG(g_bF_Led_State) == 0) {
							IOPort_Write(D_12, g_bF_Led_State);
							IOPort_Write(D_13, g_bF_Led_State);
							StartTimer(LedBlinkingWaitTimeMS, 2); /* Turn on led 200ms */
							SETFLAG(g_bF_Led_State);
						}
						else {
							IOPort_Write(D_12, g_bF_Led_State);
							IOPort_Write(D_13, g_bF_Led_State);
							StartTimer(LedBlinkingWaitTimeMS, 2); /* Turn off led 200ms */
							CLRFLAG(g_bF_Led_State);
						}
					}
					else
						if (g_bF_SystemError == NON_ERROR)
						{
							if (TSTFLAG(g_bF_Led_State) == 0) {
								IOPort_Write(D_12, g_bF_Led_State);
								IOPort_Write(D_13, g_bF_Led_State);					
								StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn on led 1s */
								SETFLAG(g_bF_Led_State);
							}
							else {
								IOPort_Write(D_12, g_bF_Led_State);
								IOPort_Write(D_13, g_bF_Led_State);					
								StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn off led 1s */
								CLRFLAG(g_bF_Led_State);
							}
						}
						else
						{
							IOPort_Write(D_12, LOW);
							IOPort_Write(D_13, LOW);
						}

	pre_BTN1_STATUS = BTN1_STATUS;
}
void resetFlagLED()
{
	g_bF_SystemError = NON_ERROR;
	g_bF_UART_Error_Frame = 0;
}