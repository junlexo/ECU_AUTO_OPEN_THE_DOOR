// STEP_MOTOR.h

#ifndef _STEP_MOTOR_h
#define _STEP_MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RAM.h"
#include "FLAG.h"
#include "IO.h"
#include "Timer_count.h"
#include "PREFERENT.h"


static uint16_t step_Fullspeed;
static uint16_t step_Decelerating;
static uint16_t step_Accelerating;
static uint32_t step_Speed;
static uint32_t fullspeed;
static uint32_t accelerating;
static uint32_t demention_open;
static uint32_t demention_close;

#ifdef __cplusplus
extern "C" {
#endif

	extern void STEP_PWM();
	extern void STEP_Speed(uint8_t ui8_StepSpeed_SET);
	extern void STEP_Control();
	extern void STEP_InitStart();
	extern void STEP_InitDIR();
	extern void STEP_CLOSE_DEFAULT();
	extern void STEP_OPEN_DEFAULT();
	extern void STEP_STOP();
	extern void STEP_RUN();
	extern void STEP_HOLD_ON();
	extern void STEP_HOLD_OFF();
	extern void STEP_SPEED_RANGE();
	extern void STEP_READ_DEMENTION();
	extern void STEP_WAITING_CLOSE();
	extern void STEP_Control_Speed();
	extern void STEP_Running_Open();
	extern void STEP_Running_Close();
	extern void STEP_RUN_DEFAULT();
	extern void STEP_MANNER();




#ifdef __cplusplus
} // extern "C"
#endif

#endif

