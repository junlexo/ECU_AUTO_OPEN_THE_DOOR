// UARTDebugging.h

#ifndef _UARTDEBUGGING_h
#define _UARTDEBUGGING_h
#include "PREFERENT.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void DBG_checkErrorUART(uint8_t c);
extern void DBG_NotifyUARTError();
extern void DBG_ReadFrame();
extern void DBG_RespondUART();
#ifdef __cplusplus
} // extern "C"
#endif

#endif

