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
	extern void STEP_MANNER();
	extern void STEPMOTOR_CheckFailSafe();
	static void STEP_Speed(uint8_t ui8_StepSpeed_SET);
	static void STEP_Control();
	static void STEP_InitStart();
	static void STEP_InitDIR();
	static void STEP_CLOSE_DEFAULT();
	static void STEP_OPEN_DEFAULT();
	static void STEP_STOP();
	static void STEP_RUN();
	static void STEP_HOLD_ON();
	static void STEP_HOLD_OFF();
	static void STEP_SPEED_RANGE();
	static void STEP_READ_DEMENTION();
	static void STEP_WAITING_CLOSE();
	static void STEP_Control_Speed();
	static void STEP_Running_Open();
	static void STEP_Running_Close();
	static void STEP_RUN_DEFAULT();
	static void STEP_CheckTimerOpen();



#ifdef __cplusplus
} // extern "C"
#endif

#endif

