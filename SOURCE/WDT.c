// 
// 
// 

#include "WDT.h"
#include "PREFERENT.h"
#include <avr/wdt.h>
#include <avr/interrupt.h>

static void(*callbackFunc)(void);

void WDT_Init()
{
	cli();
	wdt_reset();
	WDTCSR = Bit(WDCE) | Bit(WDE);
	WDTCSR = Bit(WDIE) | Bit(WDE);
	sei();
}

void WDT_Reset()
{
	wdt_reset();
}

void WDT_RegisterFunc(void (*FuncPtr)(void))
{
	callbackFunc = FuncPtr;
}

ISR(WDT_vect)
{
	callbackFunc();
	WDTCSR = (1 << WDIE) | (1 << WDE);
}