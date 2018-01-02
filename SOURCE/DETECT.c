#include "SW.h"
#include "PREFERENT.h"
#include "Timer_count.h"
#include "FLAG.h"
#include "IO.h"
#include "UART.h"
#include "ADC.h"
uint8_t pre_l_bF_DETECT_Status = 0;
uint8_t cur_l_bF_DETECT_Status = 0;
uint8_t time_l_bF_DETECT_Status_on = 0;
uint8_t time_g_bF_DETECT_Status_off = 0;
void DETECT_Init()
{
	g_bF_DOOR_OPEN = 0;
}

void DETECT()
{
	checkDETECT();
	
}


uint16_t ARead_v2(uint8_t pin)
{
	uint8_t low, high;
	ADMUX = ((1 << 6) | (pin & 0x07));
	// start the conversion
	SBI_V2(ADCSRA, ADSC);

	// ADSC is cleared when the conversion finishes
	while ((*(volatile uint8_t *)((uint16_t) &(ADCSRA))) & (1 << (ADSC)));
	low = ADCL;
	high = ADCH;

	// combine the two bytes
	return ((high << 8) | low);
}

void checkDETECT()
{
	//UART_WriteNumber((uint32_t)!IOPort_Read(D_2));
	//UART_Write('-');
	//UART_WriteNumber((uint32_t)g_bF_DOOR_OPEN);
	//UART_Write('-');
	//UART_WriteNumber((uint32_t)g_SystemError);
	//UART_Write('-');
	//UART_WriteNumber((uint32_t)BTN1_DISABLE);
	//UART_Write('\n');
	/*if (f_D2 == 1)
		cur_l_bF_DETECT_Status = 0;
	else
		cur_l_bF_DETECT_Status = 1;*/
	cur_l_bF_DETECT_Status = !IOPort_Read(D_2);
	if (cur_l_bF_DETECT_Status == pre_l_bF_DETECT_Status && cur_l_bF_DETECT_Status)
	{
		time_l_bF_DETECT_Status_on += 1;
	}
	else
	{
		time_l_bF_DETECT_Status_on = 0;
	}

	if (cur_l_bF_DETECT_Status == pre_l_bF_DETECT_Status && cur_l_bF_DETECT_Status == 0)
	{
		time_g_bF_DETECT_Status_off += 1;
	}
	else
	{
		time_g_bF_DETECT_Status_off = 0;
	}

	/*if (time_g_bF_SW2_Status_on >= 19)
	{
	g_bF_SW2_Status = 2;
	}
	else */if (time_l_bF_DETECT_Status_on >= 9)
	{
		g_bF_DOOR_OPEN = 1;

	}
	else if (time_g_bF_DETECT_Status_off >= 1)
	{
		g_bF_DOOR_OPEN = 0;
	}
	else
	{

	}
	if (time_l_bF_DETECT_Status_on > 255)
		time_l_bF_DETECT_Status_on = 9;
	if (time_g_bF_DETECT_Status_off > 255)
		time_g_bF_DETECT_Status_off = 1;
	pre_l_bF_DETECT_Status = cur_l_bF_DETECT_Status;
}
