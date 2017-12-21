// RAM.h

#ifndef _RAM_h
#define _RAM_h

#include <stdint.h>
#include "PREFERENT.h"
#include "FLAG.h"
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

extern uint8_t getADCStatus(uint8_t);
/* define use ADC in here */
/*
BTN1_STATUS == 0 <=> btn 1 off
BTN1_STATUS == 1 <=> btn 1 on
BTN1_STATUS == 2 <=> btn 1 press

BTN2_STATUS == 0 <=> btn 2 off
BTN2_STATUS == 1 <=> btn 2 on
BTN2_STATUS == 2 <=> btn 2 press

ADC_FIR_STATUS == 0 <=> fir off
ADC_FIR_STATUS == 1 <=> fir on
*/
#define BTN1_STATUS getADCStatus(1)
#define BTN2_STATUS getADCStatus(2)
#define ADC_FIR_STATUS getADCStatus(3)

#endif

