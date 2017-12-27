#include "SW.h"
#include "PREFERENT.h"
#include "Timer_count.h"
#include "FLAG.h"
#include "IO.h"
#include "UART.h"
uint8_t pre_g_bF_DETECT_Status = 0;
uint8_t cur_g_bF_DETECT_Status = 0;
uint8_t time_g_bF_DETECT_Status_on = 0;
uint8_t time_g_bF_DETECT_Status_off = 0;
void DETECT_Init()
{
	g_bF_DOOR_OPEN = 0;
}

void DETECT()
{
	checkDETECT();

}
void checkDETECT()
{
	cur_g_bF_DETECT_Status = !IOPort_Read(A_6);
	if (cur_g_bF_DETECT_Status == pre_g_bF_DETECT_Status && cur_g_bF_DETECT_Status)
	{
		time_g_bF_DETECT_Status_on += 1;
	}
	else
	{
		time_g_bF_DETECT_Status_on = 0;
	}

	if (cur_g_bF_DETECT_Status == pre_g_bF_DETECT_Status && cur_g_bF_DETECT_Status == 0)
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
	else */if (time_g_bF_DETECT_Status_on >= 7)
	{
		g_bF_DOOR_OPEN = 1;

	}
	else if (time_g_bF_DETECT_Status_off >= 2)
	{
		g_bF_DOOR_OPEN = 0;
	}
	else
	{

	}
	if (time_g_bF_DETECT_Status_on > 255)
		time_g_bF_DETECT_Status_on = 19;
	if (time_g_bF_DETECT_Status_off > 255)
		time_g_bF_DETECT_Status_off = 2;
	pre_g_bF_DETECT_Status = cur_g_bF_DETECT_Status;
}