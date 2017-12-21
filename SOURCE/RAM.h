// RAM.h

#ifndef _RAM_h
#define _RAM_h

#include <stdint.h>


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

/* define use ADC in here */
/*
BTN1_STATUS == 0 <=> btn 1 off
BTN1_STATUS == 1 <=> btn 1 on
BTN1_STATUS == 2 <=> btn 1 press

BTN2_STATUS == 0 <=> btn 2 off
BTN2_STATUS == 1 <=> btn 2 on
BTN2_STATUS == 2 <=> btn 2 press
*/
#define BTN1_STATUS { return adc_info[1].ADC_Status; }
#define BTN2_STATUS { return adc_info[2].ADC_Status; }

#endif

