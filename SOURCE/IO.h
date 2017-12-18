// IO.h

#ifndef _IO_h
#define _IO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RAM.h"
#include "PREFERENT.h"

enum port_available {
	D_0,
	D_1,
	D_2,
	D_3,
	D_4,
	D_5,
	D_6,
	D_7,
	D_8,
	D_9,
	D_10,
	D_11,
	D_12,
	D_13,
	A_0 = 16,
	A_1,
	A_2,
	A_3,
	A_4,
	A_5,
};





extern const uint8_t port_arr[];
//const uint8_t analog_port_arr[6] = { PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5 };

extern const uint8_t port_reg_addr_arr[];



#ifdef __cplusplus
extern "C" {
#endif
	extern void ClearRegisters();

	extern void SetPin(uint8_t pinNum, uint8_t pinMode);

	extern void IOPort_Write(uint8_t pinNum, uint8_t val);

	extern int IOPort_Read(uint8_t pinNum);

	extern void IO_Init();



#ifdef __cplusplus
} // extern "C"
#endif

#endif

