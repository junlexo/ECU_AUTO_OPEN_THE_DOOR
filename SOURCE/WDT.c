// 
// 
// 

#include "WDT.h"
#include "PREFERENT.h"
#include <avr/wdt.h>
#include <avr/interrupt.h>
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

ISR(WDT_vect)
{
	
	WDTCSR = (1 << WDIE) | (1 << WDE);
}