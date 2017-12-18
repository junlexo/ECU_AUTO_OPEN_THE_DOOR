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

#ifdef __cplusplus
extern "C" {
#endif


	extern void STEP_PWM();


#ifdef __cplusplus
} // extern "C"
#endif

#endif

