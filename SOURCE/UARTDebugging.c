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
static void BDG_writeData(uint8_t id);
static void BDG_saveData(uint8_t id);


static volatile uint8_t commandID = 0;
static volatile uint8_t dataID = 0xFF;
static volatile  uint16_t data = 0U;

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
			if (uart_dbg_mode == READ_DATA_MODE)
			{
				processReadingMode();
			}
			else if (uart_dbg_mode == WRITE_DATA_MODE)
			{
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
	if (commandID != 0 && isControlEnabled == 1) {
		if (uart_dbg_mode == READ_DATA_MODE || uart_dbg_mode == WRITE_DATA_MODE) {
			uint16_t responseId = commandID + RESPONSEOFFSET;
			UART_Write((responseId / 100) + '0');
			UART_Write((responseId / 10 % 10) + '0');
			UART_Write(responseId % 10 + '0');
			UART_Write(',');
			UART_Write(dataID + '0');
			UART_Write(',');

			UART_WriteString("1234");
			UART_Write('/');
			UART_Write('\n');
		}
	}
}

static void processReadingMode() {
	commandID = 1;
	dataID = 0;
	uint8_t n = 0;
	uint8_t i = bufferCount - 3;
	while (i >= 0) {
		if (frame_buffer[i] == ',') {
			i--;
			n = 0;
			break;
		}
		dataID += (frame_buffer[i] - '0') * (uint16_t)pow((uint16_t)10, n);
		n++;
		i--;
	}
}

static void processWrittingMode() {
	commandID = 8;
	dataID = 0;
	data = 0;
	uint8_t n = 0;
	uint8_t i = bufferCount - 2;
	while (i >= 0) {
		if (frame_buffer[i] == ',') {
			i--;
			n = 0;
			break;
		}
		data += (frame_buffer[i] - '0') * (uint16_t)pow((uint16_t)10, n);
		n++;
		i--;
	}
	while (i >= 0) {
		if (frame_buffer[i] == ',') {
			break;
		}
		dataID += (frame_buffer[i] - '0') * (uint16_t)pow((uint16_t)10, n);
		i--;
		n++;
	}
	BDG_saveData(dataID);
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
	}
	else {}
}

static void BDG_writeData(uint8_t id) {
	switch (id)
	{
	case 0x00:
	{
		break;
	}
	case 0x01:
	{
		break;
	}
	case 0x02:
	{
		break;
	}
	case 0x03:
	{
		break;
	}
	case 0x04:
	{
		break;
	}
	default:
		break;
	}
}

static void BDG_saveData(uint8_t id) {
	switch (id)
	{
	case 0x00:
	{
		break;
	}
	case 0x01:
	{
		break;
	}
	case 0x02:
	{
		break;
	}
	case 0x03:
	{
		break;
	}
	case 0x04:
	{
		break;
	}
	default:
		break;
	}
}