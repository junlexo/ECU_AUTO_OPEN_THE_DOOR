// OS.h

#ifndef _OS_h
#define _OS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <stdint.h> 
#include "RAM.h"
#include "TIMER.h"
#include "IO.h"

#ifdef __cplusplus
extern "C" {
#endif
	extern  void Task_Control();
	extern 	void PWMLED();
	extern	void Task_init();
	extern	void AddTask_Custom(uint8_t id, void(*handleTask)(void), void *paramIn, uint16_t timer);
	extern	void RemoveTask(uint8_t id);
	extern	void RemoveAllTask();
	extern	void setInterval(uint8_t taskID, uint16_t interval);
	extern	uint8_t isTaskRunning(uint8_t taskID);
	extern  void Task_RUNNING();
	extern  void AddTask_100US(uint8_t id, void(*handleTask)(void), void *paramIn);
	extern  void AddTask_1MS(uint8_t id, void(*handleTask)(void), void *paramIn);
	extern  void AddTask_10MS(uint8_t id, void(*handleTask)(void), void *paramIn);
	extern  void AddTask_100MS(uint8_t id, void(*handleTask)(void), void *paramIn);
	extern  void AddTask_1000MS(uint8_t id, void(*handleTask)(void), void *paramIn);


#ifdef __cplusplus
} // extern "C"
#endif


#endif

