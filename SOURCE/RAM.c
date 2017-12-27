// 
// 
// 

#include "RAM.h"

/*  TIMER  */
uint8_t currentTimer = 0;


/* ADC   */
volatile uint8_t buttonState = 0;
volatile uint16_t ADC_voltage = 0;
volatile uint32_t ADC_angle = 0;

/*LED */
uint8_t g_fblinkled = 0;

/*****   STEP MOTOR   ******/
#if STEPMOTOR == ON
volatile uint8_t g_ui8_SpeedStepValue = 0;
volatile uint32_t g_ui32_StepCount = 0;
volatile uint32_t g_ui32_StepDemention = 0;
volatile uint8_t step_Speed = STEP_SPEED_MIN;
#endif // STEP MOTOR

/* MOTOR DC*/
uint16_t g_Kp = 8;
uint16_t g_Ki = 1;
uint16_t g_Kd = 10;

