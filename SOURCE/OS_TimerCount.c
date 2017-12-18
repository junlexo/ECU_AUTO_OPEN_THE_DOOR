/*
* OS_TimeCount.c
*
*  Created on: DEC 17, 2017
*      Author: KhaiDH1
*/

#include "OS_TimerCount.h"


void OS_Timer_Counter(void)
{
	uint8_t *p8;
	uint16_t *p16;
	uint32_t *p32;
	static uint8_t counter_1ms = 0U, counter_10ms = 0U;
	static uint16_t  counter_100ms = 0U;
	static uint32_t  counter_1000ms = 0U;
	static uint32_t s_ui16IO_counter = 0U;

	counter_1ms++;
	counter_10ms++;
	counter_100ms++;
	counter_1000ms++;

	s_ui16IO_counter++;

	if (s_ui16IO_counter >= 5000U)
	{
		IOPort_Write(LED_BUILTIN, HIGH); // turn the LED13  on (HIGH is the voltage level)
		if (s_ui16IO_counter >= 10000U)
		{
			s_ui16IO_counter = 0U;
		}
	}
	else
	{
		IOPort_Write(LED_BUILTIN, LOW); 	// turn the LED13 off (HIGH is the voltage level)
	}

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
	if (counter_1ms > 10)
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
	}
}

