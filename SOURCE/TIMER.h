// TIMER.h

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Global_Define.h"
#include "RAM.h"
#include "FLAG.h"

enum timer_type {
	TIMER_0,
	TIMER_1,
	TIMER_2
};

typedef struct DataTask {
	FuncPtr myTask;
	void *param;
	uint16_t interval : 16;
	uint16_t elapsedTime : 16;
	uint8_t taskId;
	uint8_t state : 1;
} TimerTask;


extern volatile TimerTask taskList[];

#ifdef __cplusplus
extern "C" {
#endif
	extern void Timer_Init(uint8_t timerType);
	extern uint16_t MicroS();
	extern uint16_t MilliS();
	extern void Timer_AttachInterrupt(void(*func)(void));
	extern void Task_RUNNING();

#ifdef __cplusplus
} // extern "C"
#endif

#endif

