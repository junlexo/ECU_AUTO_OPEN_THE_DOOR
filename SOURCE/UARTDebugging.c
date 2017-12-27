// 
// 
// 

#include "UARTDebugging.h"
#include "FLAG.h"
#include "Timer_count.h"

#define MAX_SIZE_FRAME 20
#define RESPONSEOFFSET 128
#define ANGLEOFFSET 4500

enum POSITION_FRAME {
	START_FRAME,
	MIDDLE_FRAME,
	END_FRAME
};

enum MODE_UART_DEBUGGING {
	CONNECT_MODE,
	DISCONNECT_MODE,
	READ_DATA_MODE,
	WRITE_DATA_MODE,
	NONE
};

static uint8_t previous_position = END_FRAME;
static uint8_t uart_dbg_mode = NONE;
static volatile uint8_t uart_dbg_notifyError = 0;
static volatile uint8_t frame_buffer[MAX_SIZE_FRAME];
static volatile uint8_t bufferCount = 0;
static volatile uint8_t isControlEnabled = 0;
static volatile uint8_t waitForHandling = 0;
const uint8_t connectStr[] = "CONNECT/";
const uint8_t disconnectStr[] = "DISCONNECT/";

static void processReadingMode();
static void processWrittingMode();
uint32_t pow(uint16_t num, uint8_t n);
static void setConnectionState();
static void BDG_RespondData(uint8_t id);
static void BDG_saveData(uint8_t id);

static volatile uint8_t uart_commandID = 0;
static volatile uint8_t uart_dataID = 0xFF;
static volatile  uint32_t uart_data = 0U;

void DBG_checkErrorUART(uint8_t c)
{
	if (waitForHandling == 1 || g_SystemError == ERROR_UART) {
		UART_WriteString("stop");
		return;
	}

	frame_buffer[bufferCount] = c;
	bufferCount++;

	if (previous_position == END_FRAME) {
		if (c == 'C') {
			uart_dbg_mode = CONNECT_MODE;
		}
		else if (c == 'D') {
			uart_dbg_mode = DISCONNECT_MODE;
		}
		else if (c == '1') {
			uart_dbg_mode = READ_DATA_MODE;
		}
		else if (c == '8') {
			uart_dbg_mode = WRITE_DATA_MODE;
		}
		else {
			// error
			bufferCount = 0;
			g_SystemError = ERROR_UART;
			uart_dbg_mode = NONE;
			return;
		}
		uart_dbg_notifyError = 1;
		StartTimer(UARTDebuggingOverTime, 5);
		previous_position = START_FRAME;
	}
	else if (previous_position == START_FRAME) {
		previous_position = MIDDLE_FRAME;
	}
	else {
		if (c == '/') {
			uart_dbg_notifyError = 0;
			previous_position = END_FRAME;
			waitForHandling = 1;
			setConnectionState();
		}
	}
}

void DBG_NotifyUARTError()
{
	if (IsTimeOut(UARTDebuggingOverTime) == 1) {
		if (uart_dbg_notifyError == 1) {
			//error
			bufferCount = 0;
			g_SystemError = ERROR_UART;
			uart_dbg_mode = NONE;
		}
	}
}

void DBG_ReadFrame()
{
	if (waitForHandling == 1
		&& g_SystemError != ERROR_UART
		&& uart_dbg_mode != NONE)
	{
		if (isControlEnabled) {
			CLRFLAG(g_bF_disableSensor_state);
			if (uart_dbg_mode == READ_DATA_MODE)
			{
				processReadingMode();
			}
			else if (uart_dbg_mode == WRITE_DATA_MODE)
			{
				SETFLAG(g_bF_disableSensor_state);
				processWrittingMode();
			}
			else {}
			//uart_dbg_mode = NONE;
		}
		bufferCount = 0;
		waitForHandling = 0;
	}
}

void DBG_RespondUART()
{
	if (IsTimeOut(UARTWritingWaitTime) == 1) {
		if (uart_commandID != 0 && isControlEnabled == 1) {
			if (uart_dbg_mode == READ_DATA_MODE || uart_dbg_mode == WRITE_DATA_MODE) {
				uint16_t responseId = uart_commandID + RESPONSEOFFSET;
				UART_Write((responseId / 100) + '0');
				UART_Write((responseId / 10 % 10) + '0');
				UART_Write(responseId % 10 + '0');
				UART_Write(',');
				UART_Write(uart_dataID + '0');
				UART_Write(',');
				BDG_RespondData(uart_dataID);
				UART_Write('/');
				UART_Write('\n');
			}
		}
		StartTimer(UARTWritingWaitTime,25);
	}
}

static void processReadingMode() {
	uart_commandID = 1;
	uart_dataID = 0;
	uint8_t n = 0;
	uint8_t i = bufferCount - 3;
	while (i >= 0) {
		if (frame_buffer[i] == ',') {
			i--;
			n = 0;
			break;
		}
		uart_dataID += (frame_buffer[i] - '0') * (uint16_t)pow((uint16_t)10, n);
		n++;
		i--;
	}
}

static void processWrittingMode() {
	//uart_commandID = 8;
	//uart_dataID = 0;
	uart_data = 0;
	uint8_t n = 0;
	uint8_t i = bufferCount - 2;
	while (i >= 0) {
		if (frame_buffer[i] == ',') {
			i--;
			n = 0;
			break;
		}
		uart_data += (frame_buffer[i] - '0') * pow((uint16_t)10, n);
		n++;
		i--;
	}
	while (i >= 0) {
		if (frame_buffer[i] == ',') {
			break;
		}
		uart_dataID += (frame_buffer[i] - '0') * (uint16_t)pow((uint16_t)10, n);
		i--;
		n++;
	}
	BDG_saveData(uart_dataID);
}

uint32_t pow(uint16_t num, uint8_t n)
{
	uint32_t val = 1;
	for (uint8_t i = 0; i < n; i++)
	{
		val = val*(uint32_t)num;
	}
	return val;
}

static void setConnectionState() {
	if (uart_dbg_mode == CONNECT_MODE && isControlEnabled == 0) {
		bufferCount--;
		while (bufferCount) {
			if (frame_buffer[bufferCount] != connectStr[bufferCount]) {
				return;
			}
			bufferCount--;
		}
		isControlEnabled = 1;
	}
	else if (uart_dbg_mode == DISCONNECT_MODE && isControlEnabled == 1) {
		bufferCount--;
		while (bufferCount) {
			if (frame_buffer[bufferCount] != disconnectStr[bufferCount]) {
				return;
			}
			bufferCount--;
		}
		isControlEnabled = 0;
		CLRFLAG(g_bF_disableSensor_state);
	}
	else {}
}

static void BDG_RespondData(uint8_t id) {
	switch (id)
	{
	case READING_VOLTAGE_ID:
	{
		UART_WriteNumber(ADC_voltage);
		break;
	}
	case READING_Angle_ID:
	{
		UART_WriteNumber(ADC_angle);
		break;
	}
	case READING_SPEED_ID:
	{
		UART_Write('0');
		UART_Write('0');
		break;
	}
	case READING_SYSTEM_ERROR_ID:
	{
		UART_Write('0');
		UART_Write('0');
		break;
	}
	case READING_DISTANCE_ID:
	{
		UART_Write('0');
		UART_Write('0');
		break;
	}
	default:
		break;
	}
}

static void BDG_saveData(uint8_t id) {
	switch (id)
	{
	case WRITTING_VOLTAGE_ID:
	{
		ADC_voltage = (uint16_t)uart_data;
		break;
	}
	case WRITTING_Angle_ID:
	{
		ADC_angle = uart_data;
		break;
	}
	case WRITTING_SPEED_ID:
	{
		break;
	}
	case WRITTING_SYSTEM_ERROR_ID:
	{
		break;
	}
	case WRITTING_REQUESTMOTOR_ID:
	{
		break;
	}
	default:
		break;
	}
}