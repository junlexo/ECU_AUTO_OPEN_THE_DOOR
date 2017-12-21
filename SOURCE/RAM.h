// RAM.h

#ifndef _RAM_h
#define _RAM_h

#include <stdint.h>
#include "PREFERENT.h"


/*  TIMER  */
extern uint8_t currentTimer;
extern volatile uint8_t count_list;

/*  ADC  */
extern volatile uint8_t PB0_State ;
extern volatile uint8_t PB1_State ;
extern volatile uint8_t PB2_State ;
extern volatile uint8_t buttonState ;
extern volatile uint16_t voltage ;
extern volatile uint16_t angle ;
extern volatile uint16_t temperature ;

/*LED */
extern  uint8_t g_fblinkled;


/*****   STEP MOTOR   *******/

extern volatile uint8_t g_ui8_SpeedStepValue;
extern volatile uint32_t g_ui32_StepCount;
extern volatile uint32_t g_ui32_StepDemention;

typedef struct _ADC_DATA
{
	uint8_t ADC_index;
	uint16_t ADC_AnalogValue;
	uint8_t ADC_Pin;
	uint16_t ADC_VoltageValue;
	uint8_t ADC_Status;
	uint16_t ADC_CountTimeMS;
}ADC_DATA;

extern uint8_t getADCStatus(uint8_t);
/* define use ADC in here */
/*
BTN1_STATUS == 0 <=> btn 1 off
BTN1_STATUS == 1 <=> btn 1 on
BTN1_STATUS == 2 <=> btn 1 press

BTN2_STATUS == 0 <=> btn 2 off
BTN2_STATUS == 1 <=> btn 2 on
BTN2_STATUS == 2 <=> btn 2 press

FIR_STATUS == 0 <=> fir off
FIR_STATUS == 1 <=> fir on
*/
#define BTN1_STATUS getADCStatus(1)
#define BTN2_STATUS getADCStatus(2)
#define ADC_FIR_STATUS getADCStatus(3)

#endif

