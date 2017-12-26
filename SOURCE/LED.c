#include "LED.h"
#include "PREFERENT.h"
#include "RAM.h"
#include "FLAG.h"
#include "IO.h"
#include "Timer_count.h"
#include "UART.h"

uint8_t pre_BTN1_STATUS = 0;
void LED_Init()
{
	resetFlagLED();
}
void LED()
{
	//When have Error ERROR_VOLUME or ERROR_BTN turn off LED1 and LED2
	if (g_SystemError == ERROR_VOLUME || g_SystemError == ERROR_BTN)
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
	//When have Error turn off LED1 and LED2 blink 1s
	else if (g_SystemError == ERROR_UART)
	{
		IOPort_Write(D_12, LOW);
		uint8_t Pin[2];
		Pin[0] = D_13;
		showLED(Pin, 10, 1);
	}
	//when Button 1 put wrong LED1, LED2 blink 0.1s.
	else if (BTN1_DISABLE) {
		uint8_t Pin[2];
		Pin[0] = D_13;
		Pin[1] = D_12;
		showLED(Pin, 1, 2);
	}
	//when Button 1 put down LED1 DISPLAY AND LED2 blink 1s.
	else if (BTN1_STATUS == 1)
	{
		IOPort_Write(D_12, HIGH);
		uint8_t Pin[2];
		Pin[0] = D_13;
		showLED(Pin, 10, 1);
	}
	//when Button 1 up LED1 OFF AND LED2 blink 1s
	else if (pre_BTN1_STATUS == 1 && BTN1_STATUS == 0)
	{
		IOPort_Write(D_12, LOW);
		uint8_t Pin[2];
		Pin[0] = D_13;
		showLED(Pin, 10, 1);
	}
	//when Button 1 press LED1 blink 200ms AND LED2 blink 0.2s
	else if (BTN1_STATUS == 2)
	{
		uint8_t Pin[2];
		Pin[0] = D_13;
		Pin[1] = D_12;
		showLED(Pin, 2, 2);
	}
	//When normal LED1 and LED2 blink 1s
	else if (g_SystemError == NON_ERROR)
	{
		uint8_t Pin[2];
		Pin[0] = D_13;
		Pin[1] = D_12;
		showLED(Pin, 10, 2);
	}
	else //and more turn off both two LEDs
	{
		IOPort_Write(D_12, LOW);
		IOPort_Write(D_13, LOW);
	}

	pre_BTN1_STATUS = BTN1_STATUS;
}
void showLED(uint8_t Pin[2], uint8_t time, uint8_t nPin)
{
	if (TSTFLAG(g_bF_Led_State) == 0) {
		for (uint8_t i = 0; i < nPin; i++)
			IOPort_Write(Pin[i], g_bF_Led_State);
		StartTimer(LedBlinkingWaitTimeMS, time); /* Turn on led 1s */
		SETFLAG(g_bF_Led_State);
	}
	else {
		for (uint8_t i = 0; i < nPin; i++)
			IOPort_Write(Pin[i], g_bF_Led_State);
		StartTimer(LedBlinkingWaitTimeMS, time); /* Turn off led 1s */
		CLRFLAG(g_bF_Led_State);
	}
}
void resetFlagLED()
{
	g_SystemError = NON_ERROR;
}