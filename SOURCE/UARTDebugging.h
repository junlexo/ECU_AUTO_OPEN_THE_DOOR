// UARTDebugging.h

#ifndef _UARTDEBUGGING_h
#define _UARTDEBUGGING_h
#include "PREFERENT.h"

//#define DBG_VOLTAGE_ID	0x0000
//#define DBG_Angle_ID		0x0001
//#define DBG_SPEED_ID		0x0002
//#define DBG_VOLTAGE_ID	0x00
//#define DBG_VOLTAGE_ID	0x00
//#define DBG_VOLTAGE_ID	0x00
//#define DBG_VOLTAGE_ID	0x00
enum DBG_READING_ID {
	READING_VOLTAGE_ID,
	READING_Angle_ID,
	READING_SPEED_ID,
	READING_SYSTEM_ERROR_ID,
	READING_DISTANCE_ID
};

enum DBG_WRITTING_ID {
	WRITTING_VOLTAGE_ID,
	WRITTING_Angle_ID,
	WRITTING_SPEED_ID,
	WRITTING_SYSTEM_ERROR_ID,
	WRITTING_REQUESTMOTOR_ID
};
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

