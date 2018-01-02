#ifndef _MOTOR_DC_h
#define _MOTOR_DC_h

#include "MOTOR_DC.h"
#include "FLAG.h"
#include "PREFERENT.h"
#include "Timer_count.h"

//#if MOTOR_DC == ON


/* dinh nghia cac duong dieu khien motor */
#define MOTOR_DDR DDRD
#define MOTOR_PORT PORTD
#define MOTOR_DIR 4
#define MOTOR_EN 5
#define Sampling_time 25 /* thoi gian lay mau (ms) */
#define inv_Sampling_time 40 /* 1/Sampling_time */
#define PWM_Period 8000 /* 8000cycle = 1ms, f=8MHz */

#ifdef __cplusplus
extern "C" {
#endif

	extern void motor_Speed(int32_t des_speed);
	extern void stop_Motor();
	extern void open_Door();
	extern void close_Door();
	extern void rotate();
	extern void MOTOR_Init();
	extern void counter();

#ifdef __cplusplus
} // extern "C"
#endif

#endif

  //#endif // MOTOR DC

