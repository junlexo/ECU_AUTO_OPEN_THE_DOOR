// RAM.h

#ifndef _RAM_h
#define _RAM_h

#include <stdint.h>
#include "PREFERENT.h"
#include "FLAG.h"
/*  TIMER  */
extern uint8_t currentTimer;
extern volatile uint8_t count_list;

/**** ERROR FLAG ****/
uint8_t g_SystemError;
uint8_t g_RangeError;

/*  ADC  */

extern volatile uint8_t buttonState ;
extern volatile uint16_t ADC_voltage;
extern volatile uint32_t ADC_angle;
extern volatile uint16_t temperature ;

/*LED */
extern  uint8_t g_fblinkled;


/*****   STEP MOTOR       ******/
#if STEPMOTOR == ON

extern volatile uint8_t g_ui8_SpeedStepValue;
extern volatile uint32_t g_ui32_StepCount;
extern volatile uint32_t g_ui32_StepDemention;
extern volatile uint8_t step_Speed;
#endif
extern uint8_t getADCStatus(uint8_t);
extern uint16_t getVolumeDegree();
extern uint8_t getVolumeVoltage();
extern uint8_t isBTN1Disable();;


/* MOTOR DC */
extern uint16_t g_Kp;
extern uint16_t g_Ki;
extern uint16_t g_Kd;


/* ADC */


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
#define BTN1_DISABLE isBTN1Disable()
#define ADC_FIR_STATUS getADCStatus(3)
#define ADC_GET_VOLUME_DEGREE getVolumeDegree()
#define ADC_GET_VOLUME_VOLTAGE getVolumeVoltage() 
#endif

