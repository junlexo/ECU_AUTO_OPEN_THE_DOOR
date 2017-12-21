#ifndef _MOTOR_DC_h
#define _MOTOR_DC_h

#include "MOTOR_DC.h"
#include "FLAG.h"
#include "PREFERENT.h"

#ifndef cbi
#define cbi(port, bit) (port)&=~(1<<(bit))
#endif 
#ifndef sbi
#define sbi(port, bit) (port)|=(1<<(bit))
#endif 

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

	void motor_Speed(int32_t des_speed);
	void stop_Motor();
	void open_Door();
	void close_Door();
	void rotate();

#ifdef __cplusplus
} // extern "C"
#endif


#endif

