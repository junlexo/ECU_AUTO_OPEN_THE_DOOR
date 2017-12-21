// FLAG.h

#ifndef _FLAG_h
#define _FLAG_h
#include <stdint.h>
#include "PREFERENT.h"

struct _flag_list {
	/****  INIT   *****/
	uint8_t bF_Hardware_Init : 1;
	uint8_t bF_Software_Init : 1;

	/****  Task OS   *****/
	uint8_t bF_TaskRunning : 1;
	uint8_t bF_Task_100US : 1;
	uint8_t bF_Task_1MS : 1;
	uint8_t bF_Task_10MS : 1;
	uint8_t bF_Task_100MS : 1;
	uint8_t bF_Task_1S : 1;

	/*****   STEP MOTOR       ******/
	uint8_t StepPWM : 1;
	uint8_t HOLDON : 1;
	uint8_t HOLD_OFF : 1;
	uint8_t STEP_RUN : 1;
	uint8_t STEP_STOP : 1;
	uint8_t DIR_CLOSE : 1;
	uint8_t DIR_OPEN : 1;
	uint8_t DIMENTION : 1;
	uint8_t STEPINIT : 1;
	uint8_t STEPSTART : 1;
	uint8_t STEPCALCULATOR : 1;
	uint8_t STEPCALRANGE : 1;
	uint8_t READ_DEMENTION : 1;
	uint8_t REOPEN : 1;
	uint8_t TAKE_DEMENTION : 1;

	/*******     SWITCH    ************/

	uint8_t SW1_STATUS : 1;
	uint8_t SW2_STATUS : 1;

	uint8_t g_bF_SW1 : 1;
	uint8_t g_bF_SW2 : 1;

	/*******     BUTTON   ************/

	uint8_t BT1_STATUS : 1;
	uint8_t BT2_STATUS : 1;
	uint8_t BT1_PRESS : 1;
	uint8_t BT2_PRESS : 1;


	/***** LED EXAMPLE ****/
	uint8_t g_bF_LedController : 1;

	/*  FIR **/
	uint8_t FIR_STATUS : 1; 


	/* SYS MARCHINE LEARNING*/
	uint8_t DOOR_OPEN : 1;
	/***** SW ****/

	/**** ERROR FLAG ****/
	uint8_t g_bF_SystemError;

	/***** LED ****/
	uint8_t g_bF_Led_Normal : 1;
	uint8_t g_bF_Led_Error : 1;
	uint8_t g_bF_Led_State : 1;
	uint8_t g_bF_Led_Btn1 : 1;
	uint8_t g_bF_UART_Error_Frame : 1;
	uint8_t g_bF_Led_Press : 1;

};

extern struct _flag_list flags_list;

/******************************** Global Flags ***********************************************/
/*OS */
#define bF_TaskRunning        			flags_list.bF_TaskRunning
#define bF_Task_100US       			flags_list.bF_Task_100US
#define bF_Task_1MS 					flags_list.bF_Task_1MS
#define bF_Task_10MS   					flags_list.bF_Task_10MS
#define bF_Task_100MS  					flags_list.bF_Task_100MS
#define bF_Task_1S  					flags_list.bF_Task_1S


/*STEP MOTOR */
#define g_bF_StepPWM  					flags_list.StepPWM
#define g_bF_HOLD_ON					flags_list.HOLD_ON
#define g_bF_HOLD_OFF					flags_list.HOLD_OFF
#define g_bF_STEPMOTOR_Running			flags_list.STEP_RUN
#define g_bF_STEPMOTOR_Stop				flags_list.STEP_STOP
#define g_bF_STEPMOTOR_DIR_Close		flags_list.DIR_CLOSE
#define g_bF_STEPMOTOR_DIR_Open			flags_list.DIR_OPEN
#define g_bF_STEPMOTOR_Dimension		flags_list.DIMENTION
#define g_bF_STEP_Init					flags_list.STEPINIT
#define g_bF_STEP_Start					flags_list.STEPSTART
#define g_bF_STEP_Calculator			flags_list.STEPCALCULATOR
#define g_bF_STEP_Cal_Range				flags_list.STEPCALRANGE
#define g_bF_READ_DEMENTION				flags_list.READ_DEMENTION	
#define g_bF_STEP_ReOpen				flags_list.REOPEN
#define g_bF_STEP_TAKE_DEMENTION		flags_list.TAKE_DEMENTION



/*SWITCH */
#define g_bF_SW1_Status					flags_list.SW1_STATUS
#define g_bF_SW2_Status					flags_list.SW2_STATUS

#define g_bF_SW1						flags_list.g_bF_SW1
#define g_bF_SW2						flags_list.g_bF_SW2



/*BOTTON */
#define g_bF_BT1_Status					flags_list.BT1_STATUS
#define g_bF_BT2_Status					flags_list.BT2_STATUS
#define g_bF_BT1_Press					flags_list.BT1_PRESS
#define g_bF_BT2_Press					flags_list.BT2_PRESS

/* FIR  */
#define g_bF_FIR_Status					flags_list.FIR_STATUS


/* LED */
#define g_bF_LedController				flags_list.g_bF_LedController
#define g_bF_Led_Normal					flags_list.g_bF_Led_Normal
#define g_bF_Led_Error					flags_list.g_bF_Led_Error
#define g_bF_Led_State					flags_list.g_bF_Led_State
#define g_bF_Led_Btn1					flags_list.g_bF_Led_Btn1
#define g_bF_Led_Press					flags_list.g_bF_Led_Press

/* SYS MARCHINE LEARNING*/

#define g_bF_DOOR_OPEN					flags_list.DOOR_OPEN

/* UART*/
#define g_bF_UART_Error_Frame			flags_list.g_bF_UART_Error_Frame

/* SYSTEM*/
#define g_bF_SystemError				flags_list.g_bF_SystemError





#endif

