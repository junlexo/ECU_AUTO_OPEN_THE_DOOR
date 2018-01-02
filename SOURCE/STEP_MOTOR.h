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
#include "UART.h"

/*****   STEP MOTOR       ******/
#if STEPMOTOR == ON
 uint32_t step_Fullspeed;
 uint32_t step_Decelerating;
 uint32_t step_Accelerating;
 uint32_t fullspeed;
 uint32_t accelerating;
 uint32_t demention_open;
 uint32_t demention_close;
 uint16_t step_loop;

#ifdef __cplusplus
extern "C" {
#endif

	extern void STEP_PWM();
	extern void STEP_MANNER();
	extern void STEPMOTOR_CheckFailSafe();
	static void STEP_Speed(uint8_t ui8_StepSpeed_SET);
	static void STEP_Control();
	static void STEPMOTOR_ResetFailsafe();
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
	static void STEP_CheckTimerClose();
	static void STEP_HOLD_ON();
	static void STEP_HOLD_OFF();
#ifdef __cplusplus
} // extern "C"
#endif
#endif  // STEP MOTOR

#endif

