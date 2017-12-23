#include "SW.h"
#include "PREFERENT.h"
#include "Timer_count.h"
#include "FLAG.h"
#include "IO.h"
#include "UART.h"
uint8_t pre_g_bF_SW1_Status = 0;
uint8_t cur_g_bF_SW1_Status = 0;
uint8_t time_g_bF_SW1_Status_on = 0;
uint8_t time_g_bF_SW1_Status_off = 0;
uint8_t pre_g_bF_SW2_Status = 0;
uint8_t cur_g_bF_SW2_Status = 0;
uint8_t time_g_bF_SW2_Status_on = 0;
uint8_t time_g_bF_SW2_Status_off = 0;
void SW_Init()
{
	g_bF_SW1_Status = 0;
	g_bF_SW2_Status = 0;
}

void SW()
{
	checkSW1();
	checkSW2();

}

void checkSW1()
{
	cur_g_bF_SW1_Status = !IOPort_Read(D_11);	
	if (cur_g_bF_SW1_Status == pre_g_bF_SW1_Status && cur_g_bF_SW1_Status == 1)
	{
		time_g_bF_SW1_Status_on += 1;		
	}
	else
	{
		time_g_bF_SW1_Status_on = 0;
	}

	if (cur_g_bF_SW1_Status == pre_g_bF_SW1_Status && cur_g_bF_SW1_Status == 0)
	{
		time_g_bF_SW1_Status_off += 1;
	}
	else
	{
		time_g_bF_SW1_Status_off = 0;
	}
/*
	if (time_g_bF_SW1_Status_on >= 19)
	{
		g_bF_SW1_Status = 2;
	}
	else */if(time_g_bF_SW1_Status_on >= 7)
	{
		g_bF_SW1_Status = 1;

	}
	else if (time_g_bF_SW1_Status_off >= 2)
	{
		g_bF_SW1_Status = 0;
	}
	else
	{

	}
	if (time_g_bF_SW1_Status_on > 255)
		time_g_bF_SW1_Status_on = 19;
	if (time_g_bF_SW1_Status_off > 255)
		time_g_bF_SW1_Status_off = 2;
	pre_g_bF_SW1_Status = cur_g_bF_SW1_Status;
}
void checkSW2()
{
	cur_g_bF_SW2_Status = !IOPort_Read(D_10);
	if (cur_g_bF_SW2_Status == pre_g_bF_SW2_Status && cur_g_bF_SW2_Status)
	{
		time_g_bF_SW2_Status_on += 1;
	}
	else
	{
		time_g_bF_SW2_Status_on = 0;
	}

	if (cur_g_bF_SW2_Status == pre_g_bF_SW2_Status && cur_g_bF_SW2_Status == 0)
	{
		time_g_bF_SW2_Status_off += 1;
	}
	else
	{
		time_g_bF_SW2_Status_off = 0;
	}

	/*if (time_g_bF_SW2_Status_on >= 19)
	{
		g_bF_SW2_Status = 2;
	}
	else */if (time_g_bF_SW2_Status_on >= 7)
	{
		g_bF_SW2_Status = 1;

	}
	else if (time_g_bF_SW2_Status_off >= 2)
	{
		g_bF_SW2_Status = 0;
	}
	else
	{

	}
	if (time_g_bF_SW2_Status_on > 255)
		time_g_bF_SW2_Status_on = 19;
	if (time_g_bF_SW2_Status_off > 255)
		time_g_bF_SW2_Status_off = 2;
	pre_g_bF_SW2_Status = cur_g_bF_SW2_Status;
}