// UART.h

#ifndef _UART_h
#define _UART_h
#include "PREFERENT.h"

#define BAUD 9600
#define UBRR(BR) F_CPU/16/BR-1
#define RING_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif
	void UART_Init(uint16_t baudRate);
	void UART_Write(uint8_t data);
	uint8_t UART_Read(void);
	void UART_WriteString(uint8_t* str);
	void UART_WriteNumber(uint32_t num);
	uint8_t UART_IsRxBufferEmpty(void);
	uint8_t UART_IsTxBufferEmpty(void);
	uint8_t UART_IsRxBufferFull(void);
	uint8_t UART_IsTxBufferFull(void);
#ifdef __cplusplus
} // extern "C"
#endif

#endif
