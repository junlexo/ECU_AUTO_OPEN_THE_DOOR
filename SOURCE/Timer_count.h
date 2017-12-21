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
	uint8_t Step_SpeedPWM;

};
extern struct _timer_uint8_1ms timer_uint8_1ms;


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
	uint8_t SW_WaitTime;
	uint8_t UARTWritingWaitTime;
};
extern struct _timer_uint8_10ms timer_uint8_10ms;



#endif

#if TIMER_UINT16_10MS != 0U
/* List variable timer type uint16 */
struct _timer_uint16_10ms
{

	uint16_t dummy;
};
extern struct _timer_uint16_10ms timer_uint16_10ms;

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
	uint8_t Led_BlinkingWaitTimeMS;
};
extern struct _timer_uint8_100ms timer_uint8_100ms;


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



#endif

/************************************************************************************/
#if TIMER_UINT8_1000MS != 0U
/* List variable timer type uint8 */
struct _timer_uint8_1000ms
{

	uint8_t Led_BlinkingWaitTime;

	uint8_t UARTDebuggingOverTime;

	uint8_t StepMotorWattingClose;
	uint8_t WaitingPutButton;
	uint8_t ReEnableButton1;

#if DEBUG == ON
	uint8_t STEP_DEBUG;
#endif

};
extern struct _timer_uint8_1000ms timer_uint8_1000ms;
/******************************* Define task processing interval *********************************************/


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

/*TIME */
#define	SW_WaitTime				timer_uint8_10ms.SW_WaitTime


/*LED */
#define LedBlinkingWaitTime				timer_uint8_1000ms.Led_BlinkingWaitTime
#define	LedBlinkingWaitTimeMS		timer_uint8_100ms.Led_BlinkingWaitTimeMS
/*STEP  MOTOR */
#define	g_u8_StepSpeed_100us			timer_uint8_1ms.Step_SpeedPWM
#define g_t_ui8_S_StepMotor_WattingClose			timer_uint8_1000ms.StepMotorWattingClose
#if DEBUG == ON
#define g_t_ui8_STEP_DEBUG							timer_uint8_1000ms.STEP_DEBUG
#endif

/*UART */
#define UARTWritingWaitTime		timer_uint8_10ms.UARTWritingWaitTime
#define UARTDebuggingOverTime						timer_uint8_1000ms.UARTDebuggingOverTime
#define g_t_ui8_S_Button_WaitingInput				timer_uint8_1000ms.WaitingPutButton
#define	g_t_ui8_S_Button_ReEnable				    timer_uint8_1000ms.ReEnableButton1
#endif

