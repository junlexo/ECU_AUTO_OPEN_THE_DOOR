// LED.h

#ifndef _LED_h
#define _LED_h

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


	extern void LED();
	extern void resetFlagLED();

#ifdef __cplusplus
} // extern "C"
#endif

#endif