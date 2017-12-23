// 
// 
// 

#include "RAM.h"

/*  TIMER  */		
 uint8_t currentTimer = 0;


  /* ADC   */
	  volatile uint8_t PB0_State = LOW;
	  volatile uint8_t PB1_State = LOW;
	  volatile uint8_t PB2_State = LOW;
	  volatile uint8_t buttonState = 0;
	  volatile uint16_t voltage = 0;
	  volatile uint16_t angle = 0;
	  volatile uint16_t temperature = 0;

  /*LED */
	  uint8_t g_fblinkled = 0;

	  /*****   STEP MOTOR       ******/
#if STEPMOTOR == ON
	  volatile uint8_t g_ui8_SpeedStepValue = 0;
	  volatile uint32_t g_ui32_StepCount=0 ;
	  volatile uint32_t g_ui32_StepDemention= 0;
#endif // STEP MOTOR

	  /* MOTOR DC*/
	  uint16_t g_Kp = 8;
	  uint16_t g_Ki = 1;
	  uint16_t g_Kd = 10;

