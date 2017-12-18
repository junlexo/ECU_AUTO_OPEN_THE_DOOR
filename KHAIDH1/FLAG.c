// 
// 
// 

#include "FLAG.h"

/****  INIT   *****/
boolean bF_Hardware_Init = 0; 
boolean bF_Software_Init = 0;

/****  Task OS   *****/
boolean  bF_TaskRunning = 0;
boolean bF_Task_1MS = 0;
boolean bF_Task_10MS = 0;
boolean bF_Task_100MS = 0;
boolean bF_Task_1S = 0;

/***   TIMER  *** */
boolean bFlag_100US = 0 ;
boolean bFlag_1MS =0 ;
boolean bFlag_10MS =0 ;
boolean bFlag_100MS =0 ;
boolean bFlag_1S =0 ;
boolean bFlag_1MS_Over = 0;


/*****   STEP MOTOR       ******/

boolean g_bF_StepPWM = 1;
