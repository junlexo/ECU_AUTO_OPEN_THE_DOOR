
#include "TIMER.h"
#include <avr/interrupt.h>

#define TIMER_SETTING  0
static void myCallbackFunc0(void) {};
static void myCallbackFunc1(void) {};
static void myCallbackFunc2(void) {};


volatile TimerTask taskList[10];

const uint8_t timer_reg_addr_arr[] = {
	(uint8_t)&TCCR0A,
	(uint8_t)&TCCR1A,
	(uint8_t)&TCCR2A,
	(uint8_t)&TCCR0B,
	(uint8_t)&TCCR1B,
	(uint8_t)&TCCR2B,
	(uint8_t)&TIMSK0,
	(uint8_t)&TIMSK1,
	(uint8_t)&TIMSK2,
};
const uint16_t timer_OCRreg_addr_arr[] = {
	(uint16_t)&OCR0A,
	(uint16_t)&OCR1A,
	(uint16_t)&OCR2A
};

const uint16_t timer_mode_setup[] = {
	0,
	0,
	0,
	(1 << WGM12) | (1 << CS11) | (1 << CS10),
	0,
	0,
	(1 << OCIE1A),
	0,
#if TIMER_SETTING == 1 
	249,
#else
	24,
#endif
	3999
};

static volatile FuncPtr func_ptr_arr[3] = {
	myCallbackFunc0,
	myCallbackFunc1,
	myCallbackFunc2
};
void Timer_Init(uint8_t timerType)
{
	currentTimer = timerType;
	volatile uint8_t * reg_addr;
	cli();
	for (uint8_t i = 0; i <= 6; i += 3) {
		reg_addr = timer_reg_addr_arr[timerType + i];
		*reg_addr &= 0;
		*reg_addr |= timer_mode_setup[i];
	}
	volatile uint16_t * reg_addr1;
	reg_addr1 = timer_OCRreg_addr_arr[timerType];
	*reg_addr1 = timer_mode_setup[timerType + 7];

	sei();
}

uint16_t MicroS()
{
	us1 += (uint16_t)(TCNT1 * 4);
	return us1;
}

uint16_t MilliS()
{
	return count_1ms;
}

void Timer_AttachInterrupt(void(*func)(void))
{
	func_ptr_arr[currentTimer] = func;
}


/***********************************
*	Funtion : Interrupt Timer 1
*	Mode : CTC option 4
*	Cycle Time : 100 US 
*	Author : KhaiDH1
*************************************/
ISR(TIMER1_COMPA_vect)
{
	bFlag_100US = 1;
	t_g_ui8_100US_count++;
	if (t_g_ui8_100US_count > 10)
	{
		bFlag_1MS = 1;
		t_g_ui8_1MS_count++;
		t_g_ui8_100US_count = 0;
	}
	if (t_g_ui8_1MS_count > 10)
	{
		bFlag_10MS = 1;
		t_g_ui8_10MS_count++;
		t_g_ui8_1MS_count = 0;
	}
	if (t_g_ui8_10MS_count > 10)
	{
		bFlag_100MS = 1;
		t_g_ui8_100MS_count++;
		t_g_ui8_10MS_count = 0;
	}
	if (t_g_ui8_100MS_count > 10)
	{
		bFlag_1S = 1;
		t_g_ui8_1S_count++;
		t_g_ui8_100MS_count = 0;
	}


	if (bF_Hardware_Init == 1 && bF_Software_Init == 1)
	{
		OS_Timer_Counter();
		Task_Control();
	}
	else
	{
		bFlag_100US = 0;
		bFlag_1MS = 0;
		bFlag_10MS = 0; 
		bFlag_100MS = 0;
		bFlag_1S = 0; 
		t_g_ui8_100US_count = 0;
		t_g_ui8_1MS_count = 0;
		t_g_ui8_10MS_count = 0;
		t_g_ui8_100MS_count = 0;
		t_g_ui8_1S_count = 0;
	}

}

ISR(TIMER2_COMPA_vect)
{
	//(*func_ptr_arr[TIMER_2])();
	count_1ms++;
}


