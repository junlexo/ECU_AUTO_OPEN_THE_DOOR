// OS_TimerCount.h

#ifndef _OS_TIMERCOUNT_h
#define _OS_TIMERCOUNT_h

#ifdef __cplusplus
extern "C" {
#endif
	extern void OS_TimerCounter_Init();
	extern void RegisterOSTask(void (*taskController)(void));

#ifdef __cplusplus
} // extern "C"
#endif

#endif

