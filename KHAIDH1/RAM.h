// RAM.h

#ifndef _RAM_h
#define _RAM_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PREFERENT.h"
#include "Global_Define.h"
#include "FLAG.h"
#include "TIMER.h"

/*  TIMER  */
extern  uint8_t currentTimer;
extern  volatile uint16_t us1;
extern  volatile uint16_t count_10ms;
extern  volatile uint16_t count_1ms ;
extern	volatile uint16_t count_1s;
extern  volatile uint8_t count_list;

extern volatile uint8_t  t_g_ui8_100US_count;
extern volatile uint8_t  t_g_ui8_1MS_count;
extern volatile uint8_t  t_g_ui8_10MS_count;
extern volatile uint8_t  t_g_ui8_100MS_count;
extern volatile uint8_t  t_g_ui8_1S_count;




/*  ADC  */
extern volatile uint8_t PB0_State ;
extern volatile uint8_t PB1_State ;
extern volatile uint8_t PB2_State ;
extern volatile uint8_t buttonState ;
extern volatile uint16_t voltage ;
extern volatile uint16_t angle ;
extern volatile uint16_t temperature ;

/*LED */
extern  boolean g_fblinkled;


/*****   STEP MOTOR   *******/



#endif

