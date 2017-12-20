// FLAG.h

#ifndef _FLAG_h
#define _FLAG_h
#include <stdint.h>

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
	uint8_t g_bF_StepPWM : 1;

	/***** LED ****/
	uint8_t g_bF_Led_Normal : 1;
	uint8_t g_bF_Led_Error : 1;
	uint8_t g_bF_Led_State : 1;
	uint8_t g_bF_Led_Btn1 : 1;
	
};

extern struct _flag_list flags_list;

/******************************** Global Flags ***********************************************/

#define bF_TaskRunning        			flags_list.bF_TaskRunning
#define bF_Task_100US       			flags_list.bF_Task_100US
#define bF_Task_1MS 					flags_list.bF_Task_1MS
#define bF_Task_10MS   					flags_list.bF_Task_10MS
#define bF_Task_100MS  					flags_list.bF_Task_100MS
#define bF_Task_1S  					flags_list.bF_Task_1S
#define g_bF_StepPWM  					flags_list.g_bF_StepPWM
#define g_bF_Led_Normal					flags_list.g_bF_Led_Normal
#define g_bF_Led_Error					flags_list.g_bF_Led_Error
#define g_bF_Led_State					flags_list.g_bF_Led_State
#define g_bF_Led_Btn1					flags_list.g_bF_Led_Btn1

#endif

