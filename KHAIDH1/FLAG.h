// FLAG.h

#ifndef _FLAG_h
#define _FLAG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/****  INIT   *****/

extern boolean bF_Hardware_Init;
extern boolean bF_Software_Init;




/****  Task OS   *****/
extern boolean bF_TaskRunning;
extern boolean bF_Task_1MS ;
extern boolean bF_Task_10MS ;
extern boolean bF_Task_100MS;
extern boolean bF_Task_1S ;

/***   TIMER  *** */

extern boolean bFlag_100US;
extern boolean bFlag_1MS;
extern boolean bFlag_10MS;
extern boolean bFlag_100MS;
extern boolean bFlag_1S;
extern boolean bFlag_1MS_Over;


/*****   STEP MOTOR       ******/

extern boolean g_bF_StepPWM;


#endif

