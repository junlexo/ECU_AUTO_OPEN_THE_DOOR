// LED.h

#ifndef _DETECT_h
#define _DETECT_h

#ifdef __cplusplus
extern "C" {
#endif
	extern void DETECT_Init();
	extern void DETECT();
	extern uint16_t ARead_v2(uint8_t pin);
#ifdef __cplusplus
} // extern "C"
#endif

#endif#pragma once
