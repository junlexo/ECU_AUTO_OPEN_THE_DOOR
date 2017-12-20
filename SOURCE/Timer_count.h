// Timer_count.h

#ifndef _TIMER_COUNT_h
#define _TIMER_COUNT_h
#include "RAM.h"

/************************************************************************************/
#define TIMER_UINT8_100US		1U
#define TIMER_UINT16_100US		0U
#define TIMER_UINT32_100US		0U

#define TIMER_UINT8_1MS			1U
#define TIMER_UINT16_1MS		0U
#define TIMER_UINT32_1MS		0U

#define TIMER_UINT8_10MS		1U
#define TIMER_UINT16_10MS		0U
#define TIMER_UINT32_10MS		0U

#define TIMER_UINT8_100MS		1U
#define TIMER_UINT16_100MS		0U
#define TIMER_UINT32_100MS		0U

#define TIMER_UINT8_1000MS		1U
#define TIMER_UINT16_1000MS		0U
#define TIMER_UINT32_1000MS		0U



/************************************************************************************/
#if TIMER_UINT8_100US != 0U
/* List variable timer type uint8 */
struct _timer_uint8_100us
{
	uint8_t dummy;
};
extern struct _timer_uint8_100us timer_uint8_100us;

#define	t_ui8_100us _dummy		timer_uint8_100us .dummy

#endif

#if TIMER_UINT16_100US  != 0U
/* List variable timer type uint16 */
struct _timer_uint16_100us
{
	uint16_t dummy;
};
extern struct _timer_uint16_100us  timer_uint16_100us;

#define	t_ui16_100us _dummy		timer_uint16_100us .dummy

#endif

#if TIMER_UINT32_100US != 0U
/* List variable timer type uint32 */
struct _timer_uint32_100us
{
	uint32_t dummy;
};
extern struct _timer_uint32_100us  timer_uint32_100us;

#define	t_ui32_100us _dummy		timer_uint32_100us .dummy

#endif

/************************************************************************************/
#if TIMER_UINT8_1MS != 0U
/* List variable timer type uint8 */
struct _timer_uint8_1ms
{
	uint8_t dummy;
};
extern struct _timer_uint8_1ms timer_uint8_1ms;

#define	t_ui8_1ms_dummy		timer_uint8_1ms.dummy

#endif

#if TIMER_UINT16_1MS != 0U
/* List variable timer type uint16 */
struct _timer_uint16_1ms
{
	uint16_t dummy;
};
extern struct _timer_uint16_1ms timer_uint16_1ms;

#define	t_ui16_1ms_dummy		timer_uint16_1ms.dummy

#endif

#if TIMER_UINT32_1MS != 0U
/* List variable timer type uint32 */
struct _timer_uint32_1ms
{
	uint32_t dummy;
};
extern struct _timer_uint32_1ms timer_uint32_1ms;

#define	t_ui32_1ms_dummy		timer_uint32_1ms.dummy

#endif

/************************************************************************************/
#if TIMER_UINT8_10MS != 0U
/* List variable timer type uint8 */
struct _timer_uint8_10ms
{
	uint8_t dummy;
	uint8_t SW_WaitTime;
};
extern struct _timer_uint8_10ms timer_uint8_10ms;

#define	t_ui8_10ms_dummy		timer_uint8_10ms.dummy
#define	SW_WaitTime				timer_uint8_10ms.SW_WaitTime
#endif

#if TIMER_UINT16_10MS != 0U
/* List variable timer type uint16 */
struct _timer_uint16_10ms
{
	//uint16_t LCDPrintWating;
	//uint16_t ADC_Sampleting;
	//uint16_t OBD_CMDTimming;
	uint16_t dummy;
};
extern struct _timer_uint16_10ms timer_uint16_10ms;

//#define	t_ui16LCDPrintWating		timer_uint16_10ms.LCDPrintWating
//#define t_ui16ADCSanpleting			timer_uint16_10ms.ADC_Sampleting
//#define t_ui16OBDCMDTimming 		timer_uint16_10ms.OBD_CMDTimming
#define	t_ui16_10ms_dummy		timer_uint16_10ms.dummy
#endif

#if TIMER_UINT32_10MS != 0U
/* List variable timer type uint32 */
struct _timer_uint32_10ms
{
	uint32_t dummy;
};
extern struct _timer_uint32_10ms timer_uint32_10ms;

#define	t_ui32_10ms_dummy		timer_uint32_10ms.dummy

#endif
/************************************************************************************/
#if TIMER_UINT8_100MS != 0U
/* List variable timer type uint8 */
struct _timer_uint8_100ms
{
	uint8_t LedBlinkingWaitTimeMS;
};
extern struct _timer_uint8_100ms timer_uint8_100ms;

#define	LedBlinkingWaitTimeMS		timer_uint8_100ms.LedBlinkingWaitTimeMS
#endif

#if TIMER_UINT16_100MS != 0U
/* List variable timer type uint16 */
struct _timer_uint16_100ms
{
	uint16_t dummy;
};
extern struct _timer_uint16_100ms timer_uint16_100ms;

#define	t_ui16_100ms_dummy		timer_uint16_100ms.dummy

#endif

#if TIMER_UINT32_100MS != 0U
/* List variable timer type uint32 */
struct _timer_uint32_100ms
{
	uint32_t LedBlinkingWaitTimeMS;
};
extern struct _timer_uint32_100ms timer_uint32_100ms;

#define	LedBlinkingWaitTimeMS		timer_uint32_100ms.LedBlinkingWaitTimeMS

#endif

/************************************************************************************/
#if TIMER_UINT8_1000MS != 0U
/* List variable timer type uint8 */
struct _timer_uint8_1000ms
{
	uint8_t LedBlinkingWaitTime;
};
extern struct _timer_uint8_1000ms timer_uint8_1000ms;
#endif

#if TIMER_UINT16_1000MS != 0U
/* List variable timer type uint16 */
struct _timer_uint16_1000ms
{
	uint16_t dummy;
};
extern struct _timer_uint16_1000ms timer_uint16_1000ms;

#define	t_ui16_1000ms_dummy		timer_uint16_1000ms.dummy

#endif

#if TIMER_UINT32_1000MS != 0U
/* List variable timer type uint32 */
struct _timer_uint32_1000ms
{
	uint32_t dummy;
};
extern struct _timer_uint32_1000ms timer_uint32_1000ms;

#define	t_ui32_1000ms_dummy		timer_uint32_1000ms.dummy

#endif

/******************************* Define task processing interval *********************************************/
#define LedBlinkingWaitTime timer_uint8_1000ms.LedBlinkingWaitTime

#endif

