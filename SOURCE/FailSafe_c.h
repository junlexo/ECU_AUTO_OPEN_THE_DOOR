// FailSafe_c.h

#ifndef _FAILSAFE_C_h
#define _FAILSAFE_C_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "RAM.h"


#endif

void FailSafe_CheckSYS();
