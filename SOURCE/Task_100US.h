// Task_100US.h

#ifndef _TASK_100US_h
#define _TASK_100US_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

	extern  void Task_100US();

#ifdef __cplusplus
} // extern "C"
#endif



#endif

