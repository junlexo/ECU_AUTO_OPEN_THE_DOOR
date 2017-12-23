// 
// 
// 

#include "SYS.h"
#include "RAM.h"
#include "IO.h"
#include "STEP_MOTOR.h"
#include "OS_TimerCounter.h"
#include "LED.h"
#include "SW.h"
#include "ADC.h"
#include "FLAG.h"
#include "EEPROM.h"
#include "UART.h"


void CPU_Init()
{
	Hardware_Init();
	Software_Init();
	SETFLAG(bF_TaskRunning);
}
void Hardware_Init()
{
	IO_Init();
	UART_Init(9600);
	EEPROM_Init();
	LED_Init();
	SW_Init();
	ADC_init();
	OS_Init();

	//bF_Hardware_Init = 1;

}
void Software_Init()
{
	
	Init_FLAG_SYS();
	Init_RAM_SYS();
}
void Init_FLAG_SYS()
{
	bF_TaskRunning = 0;
	bF_Task_100US = 0;
	bF_Task_1MS = 0;
	bF_Task_10MS = 0;
	bF_Task_100MS = 0;
	bF_Task_1S = 0;
	/*****   STEP MOTOR       ******/
#if STEPMOTOR == ON

	g_bF_StepPWM = 0;
	g_bF_STEPMOTOR_Running = 0;
	g_bF_STEPMOTOR_Stop = 1;
	g_bF_STEPMOTOR_DIR_Close = 0;
	g_bF_STEPMOTOR_DIR_Open = 0;
	g_bF_STEPMOTOR_Dimension = 0;
	g_bF_STEP_Init = 0;
	g_bF_STEP_Start = 0;
	g_bF_STEP_Calculator = 0;
	g_bF_STEP_Cal_Range = 0;
	g_bF_READ_DEMENTION = 0;
	g_bF_STEP_ReOpen = 0;
	g_bF_STEP_TAKE_DEMENTION = 0;

#endif  // STEP MOTOR

	/*SWITCH */
	g_bF_SW1_Status = 0;
	g_bF_SW2_Status = 0;



	/*BOTTON */
	g_bF_BT1_Status = 0;
	g_bF_BT2_Status = 0;
	g_bF_BT1_Press = 0;
	g_bF_BT2_Press = 0;

	/* FIR  */
	g_bF_FIR_Status = 0;


	/* LED */
	g_bF_Led_State = 0;

	/* SYS MARCHINE LEARNING*/

	g_bF_DOOR_OPEN = 0;

	/* UART*/
	g_bF_UART_Error_Frame = 0;

	/* SYSTEM*/
	g_bF_SystemError = 0;

}
void Init_RAM_SYS()
{

}