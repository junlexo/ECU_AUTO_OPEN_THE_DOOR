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
	uint8_t bF_AppTask_10MS : 1;
	uint8_t bF_Task_100MS : 1;
	uint8_t bF_Task_1S : 1;


	/*****   STEP MOTOR       ******/
#if STEPMOTOR == ON
	uint8_t StepPWM : 1;
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
	uint8_t WAITTINGOPEN : 1;
	uint8_t REQUEST_BY_PASSCODE_FROM_BTN1 : 1;
#endif 

	/*******     SWITCH    ************/

	uint8_t SW1_STATUS ;
	uint8_t SW2_STATUS ; 

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

	/***** LED ****/
	uint8_t g_bF_Led_State : 1;

	/***** EEPROM  ****/
	uint8_t g_bF_eeprom_writeData : 1;

	/***** ADC  ****/
	uint8_t g_bF_disableSensor_state : 1;

	/******  FAIL SAFE *******/
	uint8_t StepMotor_TimeClose : 1;
	uint8_t StepMotor_TimeOpen : 1;
	uint8_t StepMotor_TimeCloseInit : 1;

};

extern struct _flag_list flags_list;

/******************************** Global Flags ***********************************************/
/*OS */
#define bF_TaskRunning        			flags_list.bF_TaskRunning
#define bF_Task_100US       			flags_list.bF_Task_100US
#define bF_Task_1MS 					flags_list.bF_Task_1MS
#define bF_Task_10MS   					flags_list.bF_Task_10MS
#define bF_AppTask_10MS					flags_list.bF_AppTask_10MS
#define bF_Task_100MS  					flags_list.bF_Task_100MS
#define bF_Task_1S  					flags_list.bF_Task_1S

/*STEP MOTOR */
#define g_bF_StepPWM  					flags_list.StepPWM
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
#define g_bF_STEP_WAITTING_OPEN			flags_list.WAITTINGOPEN
#define g_bF_REQUEST_BY_PASSCODE_FROM_BTN1	flags_list.REQUEST_BY_PASSCODE_FROM_BTN1

/*SWITCH */
#define g_bF_SW1_Status					flags_list.SW1_STATUS
#define g_bF_SW2_Status					flags_list.SW2_STATUS
/*BOTTON */
#define g_bF_BT1_Status					flags_list.BT1_STATUS
#define g_bF_BT2_Status					flags_list.BT2_STATUS
#define g_bF_BT1_Press					flags_list.BT1_PRESS
#define g_bF_BT2_Press					flags_list.BT2_PRESS
/* FIR  */
#define g_bF_FIR_Status					flags_list.FIR_STATUS

/* LED */
#define g_bF_Led_State					flags_list.g_bF_Led_State
/* SYS MARCHINE LEARNING*/
#define g_bF_DOOR_OPEN					flags_list.DOOR_OPEN
/* EEPROM*/
#define g_bF_eeprom_writeData			flags_list.g_bF_eeprom_writeData
/* ADC*/
#define g_bF_disableSensor_state			flags_list.g_bF_disableSensor_state
/* FailSafe*/
/* Step Motor*/
#define g_bF_FS_StepMotor_TimeClose			flags_list.StepMotor_TimeClose	
#define g_bF_FS_StepMotor_TimeOpen			flags_list.StepMotor_TimeOpen	
#define g_bF_FS_StepMotor_TimeCloseInit		flags_list.StepMotor_TimeCloseInit

#endif

