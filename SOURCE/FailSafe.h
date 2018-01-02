// FailSafe.h

#ifndef _FAILSAFE_h
#define _FAILSAFE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RAM.h"

void FailSafe_CheckSYS();

#endif

