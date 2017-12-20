#include "LED.h"
#include "PREFERENT.h"
#include "RAM.h"
#include "FLAG.h"
#include "IO.h"
#include "Timer_count.h"

uint8_t l_unit8_led_normal = 0;
uint8_t l_unit8_led_error = 1;
uint8_t l_unit8_led_State = 0;
uint8_t l_uint8_led_btn1 = 0;
void LED()
{
	if (l_unit8_led_normal == 1)
	{
		if (TSTFLAG(l_unit8_led_State) == 0) {
			IOPort_Write(D_13, l_unit8_led_State);
			StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn on led 0.5s */
			SETFLAG(l_unit8_led_State);
		}
		else {
			IOPort_Write(D_13, l_unit8_led_State);
			StartTimer(LedBlinkingWaitTimeMS, 10); /* Turn off led 0.5s */
			CLRFLAG(l_unit8_led_State);
		}
	}
	else
		if (l_unit8_led_error == 1)
		{
			if (TSTFLAG(l_unit8_led_State) == 0) {
				IOPort_Write(D_13, l_unit8_led_State);
				StartTimer(LedBlinkingWaitTimeMS, 20); /* Turn off led 2s */
				SETFLAG(l_unit8_led_State);
			}
			else {
				IOPort_Write(D_13, l_unit8_led_State);
				StartTimer(LedBlinkingWaitTimeMS, 20); /* Turn on led 2s */
				CLRFLAG(l_unit8_led_State);
			}
		}
		else
			if (l_uint8_led_btn1 == 1)
			{
				IOPort_Write(D_13, HIGH);
			}
			else
			{
				IOPort_Write(D_13, LOW);
			}

	
}
void resetFlagLED()
{
	l_unit8_led_normal = 1;
	l_unit8_led_error = 0;
	l_unit8_led_State = 0;
}