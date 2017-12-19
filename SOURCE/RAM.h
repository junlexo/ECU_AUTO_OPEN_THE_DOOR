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



#endif

