/*
* OS_TimeCount.c
*
*  Created on: DEC 17, 2017
*   Author: KhaiDH1
*	Modified: HungTP2
*/

#include "OS_TimerCounter.h"
#include "PREFERENT.h"
#include "FLAG.h"
#include <avr/interrupt.h>
#include "Timer_count.h"

static volatile uint8_t counter_1ms = 0U;
static volatile uint8_t counter_10ms = 0U;
static volatile uint16_t counter_100ms = 0U;
static volatile uint16_t counter_1000ms = 0U;
static void	(*callbackFunc)(void);
static void OS_Timer_Counter(void);

/*********** Using Timer 1 for operation system **************/
void OS_TimerCounter_Init()
{
	cli();
	TCCR1A = 0;
	TCCR1B = 0;
	TIMSK1 = 0;
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
	OCR1A = 24;
	TIMSK1 |= (1 << OCIE1A);

	/*timer 2*/
	// Use Timer2 with 1 ms interrupts
	TCCR2A = 0;// set entire TCCR2A register to 0
	TCCR2B = 0;// same for TCCR2B
	TCNT2 = 0;//initialize counter value to 0		  
	TCCR2B |= (1 << CS22) | (1 << CS21); // Set CS21 bit for 16 prescaler
	TCCR2A |= (1 << WGM21);
	TIMSK2 |= (1 << OCIE2A);
	OCR2A = 50;
	sei();
}

void RegisterOSTask(void (*taskController)(void))
{
	callbackFunc = taskController;
}

void OS_Timer_Counter(void)
{
	uint8_t *p8;
	uint16_t *p16;
	uint32_t *p32;

	counter_1ms++;
	counter_10ms++;
	counter_100ms++;
	counter_1000ms++;

	SETFLAG(bF_Task_100US);
	/********************************   100US    *************************************************/
#if	TIMER_UINT8_100US != 0U
	/* decrement 1Byte(uint8_t) Timer Variable */
	for (p8 = (uint8_t*)&timer_uint8_100us;
		p8 < (uint8_t*)&timer_uint8_100us + sizeof(timer_uint8_100us) / sizeof(uint8_t);
		p8++)
	{
		if (*p8 != 0U)
		{
			(*p8)--;
		}
	}
#endif

#if	TIMER_UINT16_100US != 0U
	/* decrement 2Byte(uint16_t) Timer Variable */
	for (p16 = (uint16_t*)&timer_uint16_100us; p16 < (uint16_t*)&timer_uint16_100us + sizeof(timer_uint16_100us) / sizeof(uint16_t);
		p16++)
	{
		if (*p16 != 0U)
		{
			(*p16)--;
		}
	}
#endif

#if	TIMER_UINT32_100US != 0U
	/* decrement 4Byte(uint32_t) Timer Variable */
	for (p32 = (uint32_t*)&timer_uint32_100us; p32 < (uint32_t*)&timer_uint32_100us + sizeof(timer_uint32_100us) / sizeof(uint32_t);
		p32++)
	{
		if (*p32 != 0U)
		{
			(*p32)--;
		}
	}
#endif

	/********************************   1MS    *************************************************/
	if (counter_1ms >= 10)
	{
#if	TIMER_UINT8_1MS != 0U
		/* decrement 1Byte(uint8_t) Timer Variable */
		for (p8 = (uint8_t*)&timer_uint8_1ms;
			p8 < (uint8_t*)&timer_uint8_1ms + sizeof(timer_uint8_1ms) / sizeof(uint8_t);
			p8++)
		{
			if (*p8 != 0U)
			{
				(*p8)--;
			}
		}
#endif

#if	TIMER_UINT16_1MS != 0U
		/* decrement 2Byte(uint16_t) Timer Variable */
		for (p16 = (uint16_t*)&timer_uint16_1ms; p16 < (uint16_t*)&timer_uint16_1ms + sizeof(timer_uint16_1ms) / sizeof(uint16_t);
			p16++)
		{
			if (*p16 != 0U)
			{
				(*p16)--;
			}
		}
#endif

#if	TIMER_UINT32_1MS != 0U
		/* decrement 4Byte(uint32_t) Timer Variable */
		for (p32 = (uint32_t*)&timer_uint32_1ms; p32 < (uint32_t*)&timer_uint32_1ms + sizeof(timer_uint32_1ms) / sizeof(uint32_t);
			p32++)
		{
			if (*p32 != 0U)
			{
				(*p32)--;
			}
		}
#endif
		counter_1ms = 0U; /* Clear counter */
		SETFLAG(bF_Task_1MS);
	}

	/********************************   10MS    *************************************************/
	if (counter_10ms >= 100U)
	{
#if	TIMER_UINT8_10MS != 0U
		/* decrement 1Byte(uint8_t) Timer Variable */
		for (p8 = (uint8_t*)&timer_uint8_10ms;
			p8 < (uint8_t*)&timer_uint8_10ms + sizeof(timer_uint8_10ms) / sizeof(uint8_t);
			p8++)
		{
			if (*p8 != 0U)
			{
				(*p8)--;
			}
		}
#endif
#if	TIMER_UINT16_10MS != 0U
		/* decrement 2Byte(uint16_t) Timer Variable */
		for (p16 = (uint16_t*)&timer_uint16_10ms;
			p16 < (uint16_t*)&timer_uint16_10ms + sizeof(timer_uint16_10ms) / sizeof(uint16_t);
			p16++)
		{
			if (*p16 != 0U)
			{
				(*p16)--;
			}
		}
#endif
#if	TIMER_UINT32_10MS != 0U
		/* decrement 4Byte(uint32_t) Timer Variable */
		for (p32 = (uint32_t*)&timer_uint32_10ms;
			p32 < (uint32_t*)&timer_uint32_10ms + sizeof(timer_uint32_10ms) / sizeof(uint32_t);
			p32++)
		{
			if (*p32 != 0U)
			{
				(*p32)--;
			}
		}
#endif
		counter_10ms = 0U;	/* Clear counter */
		SETFLAG(bF_Task_10MS);
	}

	/********************************   100MS    *************************************************/
	if (counter_100ms >= 1000U)
	{
#if	TIMER_UINT8_100MS != 0U

		/* decrement 1Byte(uint8_t) Timer Variable */
		for (p8 = (uint8_t*)&timer_uint8_100ms;
			p8 < (uint8_t*)&timer_uint8_100ms + sizeof(timer_uint8_100ms) / sizeof(uint8_t);
			p8++)
		{
			if (*p8 != 0U)
			{
				(*p8)--;
			}
		}
#endif
#if	TIMER_UINT16_100MS != 0U
		/* decrement 2Byte(uint16_t) Timer Variable */
		for (p16 = (uint16_t*)&timer_uint16_100ms;
			p16 < (uint16_t*)&timer_uint16_100ms + sizeof(timer_uint16_100ms) / sizeof(uint16_t);
			p16++)
		{
			if (*p16 != 0U)
			{
				(*p16)--;
			}
		}
#endif
#if	TIMER_UINT32_100MS != 0U
		/* decrement 4Byte(uint32_t) Timer Variable */
		for (p32 = (uint32_t*)&timer_uint32_100ms;
			p32 < (uint32_t*)&timer_uint32_100ms + sizeof(timer_uint32_100ms) / sizeof(uint32_t);
			p32++)
		{
			if (*p32 != 0U)
			{
				(*p32)--;
			}
		}
#endif
		counter_100ms = 0U;	/* Clear Counter */
		SETFLAG(bF_Task_100MS);
	}

	/********************************   1000MS    *************************************************/
	if (counter_1000ms >= 10000U)
	{
#if	TIMER_UINT8_1000MS != 0U
		/* decrement 1Byte(uint8_t) Timer Variable */
		for (p8 = (uint8_t*)&timer_uint8_1000ms;
			p8 < (uint8_t*)&timer_uint8_1000ms + sizeof(timer_uint8_1000ms) / sizeof(uint8_t);
			p8++)
		{
			if (*p8 != 0U)
			{
				(*p8)--;
			}
		}
#endif
#if	TIMER_UINT16_1000MS != 0U
		/* decrement 2Byte(uint16_t) Timer Variable */
		for (p16 = (uint16_t*)&timer_uint16_1000ms;
			p16 < (uint16_t*)&timer_uint16_1000ms + sizeof(timer_uint16_1000ms) / sizeof(uint16_t);
			p16++)
		{
			if (*p16 != 0U)
			{
				(*p16)--;
			}
		}
#endif
#if	TIMER_UINT32_1000MS != 0U
		/* decrement 4Byte(uint32_t) Timer Variable */
		for (p32 = (uint32_t*)&timer_uint32_1000ms;
			p32 < (uint32_t*)&timer_uint32_1000ms + sizeof(timer_uint32_1000ms) / sizeof(uint32_t);
			p32++)
		{
			if (*p32 != 0U)
			{
				(*p32)--;
			}
		}
#endif
		counter_1000ms = 0U;	/* Clear Counter */
		SETFLAG(bF_Task_1S);
	}
}

/** interrupt occur every 100 uS **/
ISR(TIMER1_COMPA_vect)
{
	OS_Timer_Counter();
	callbackFunc();
}
ISR(TIMER2_COMPA_vect)
{
	STEP_PWM();
}