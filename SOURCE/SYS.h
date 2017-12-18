// SYS.h

#ifndef _SYS_h
#define _SYS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "RAM.h"
#include "IO.h"
#include "STEP_MOTOR.h"
#include "TIMER.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Hardware_Init();
extern void Software_Init();
extern void CPU_Init();

#ifdef __cplusplus
} // extern "C"
#endif
#endif

