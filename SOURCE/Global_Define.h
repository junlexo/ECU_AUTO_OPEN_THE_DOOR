// Global_Define.h

#ifndef _GLOBAL_DEFINE_h
#define _GLOBAL_DEFINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once

#include <avr/io.h>
#include <stddef.h>


#define Bit(bit) (1 << (bit))
#define CharToInt(c) ((uint8_t)(c)-'0')
#define IntToChar(i) ((uint8_t)(i)+'0')

#define	CLR	0U
#define	SET	1U


/***************** set/clear bit define ***************/
#define SETBIT(BIT) ((BIT)=(1U))
#define CLRBIT(BIT) ((BIT)=(0U))

#define TSTBIT(BIT) ((BIT != 0U))

#define MIN(a,b) ((a>b)?b:a)
#define MAX(a,b) ((a>b)?a:b)
#define MIN_MAX(a,min,max)		((a>max)?max:((a<min)?min:a))

/***************** set/clear timer define ***************/
#define START_TIMER(timer,time) ((timer)=(time))
#define CHECK_TIMER(timer) (((timer)==0U))


/***************** set/clear counter define ***************/
#define START_COUNTER(counter,times) 	((counter)=(times))
#define CHECK_COUNTER(counter) 			(((counter)==0U))



typedef void(*FuncPtr)(void*);
typedef unsigned long ulong_t;
typedef long long_t;
typedef float float_t;
typedef double double_t;
typedef unsigned char uchar_t;

typedef struct Data_frame {
	uint8_t commandId;
	uchar_t breakChar;
	uchar_t endFrame;
	uint16_t dataID : 16;
	uint32_t data;
} DataFrame;

/*global*/
extern volatile uint8_t modeControlFlag;

#ifdef __cplusplus
extern "C" {
#endif
	long_t Map(long_t val, long_t in_min, long_t in_max, long_t out_min, long_t out_max);
	float_t Map_f(float_t val, float_t in_min, float_t in_max, float_t out_min, float_t out_max);
	extern uint8_t strToInt(char *s, uint8_t length);
#ifdef __cplusplus
} // extern "C"
#endif

#endif

