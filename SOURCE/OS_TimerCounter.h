// OS_TimerCount.h

#ifndef _OS_TIMERCOUNT_h
#define _OS_TIMERCOUNT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Timer_count.h"

#ifdef __cplusplus
extern "C" {
#endif
	extern	void OS_TimerCounter_Init();
	extern  void OS_Timer_Counter(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

