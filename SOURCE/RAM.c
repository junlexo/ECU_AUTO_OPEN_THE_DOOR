// 
// 
// 

#include "RAM.h"


/*  TIMER  */		
			   uint8_t currentTimer = 0 ;
	  volatile uint16_t us1 = 0;
	  volatile uint16_t count_10ms = 0;
	  volatile uint16_t count_1ms = 0 ;
	  volatile uint16_t count_1s = 0;
	  volatile uint8_t count_list = 0;


	 volatile uint8_t  t_g_ui8_100US_count =0 ;
	 volatile uint8_t  t_g_ui8_1MS_count = 0;
	 volatile uint8_t  t_g_ui8_10MS_count =0 ;
	 volatile uint8_t  t_g_ui8_100MS_count =0 ;
	 volatile uint8_t  t_g_ui8_1S_count =0 ;

  /* ADC   */
	  volatile uint8_t PB0_State = LOW;
	  volatile uint8_t PB1_State = LOW;
	  volatile uint8_t PB2_State = LOW;
	  volatile uint8_t buttonState = 0;
	  volatile uint16_t voltage = 0;
	  volatile uint16_t angle = 0;
	  volatile uint16_t temperature = 0;

  /*LED */
	  boolean g_fblinkled = 0;

 /*****   STEP MOTOR   *******/

