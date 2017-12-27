// 
// 
// 

#include "EEPROM.h"
#include "RAM.h"
#include <avr/interrupt.h>
#include "UART.h"

static volatile uint8_t ee_isAvailable = 1;
static volatile uint16_t ee_address = 0;

const uint8_t ee_angle_id = 0x00;
const uint8_t ee_turnOnTime_id = 0x04;
const uint8_t ee_turnOffTime_id = 0x06;
const uint8_t ee_kp_id = 0x08;
const uint8_t ee_kd_id = 0x0A;
const uint8_t ee_ki_id = 0x0C;
const uint8_t ee_distance_id = 0x0E;
const uint8_t ee_voltage_id = 0x20;

struct DataPacket {
	uint8_t _address;
	uint8_t _data[20];
	volatile uint8_t _dataCount;
};

struct DataPacket ee_stackData[10];
static volatile uint8_t ee_stackCount = 0;

void EEPROM_Init()
{
	EEPROM_GetAllData();
}

uint8_t EEPROM_ReadByte(uint16_t address)
{
	EEAR = address;
	EECR = Bit(EERE);
	return EEDR;
}

uint8_t EEPROM_WriteByte(uint16_t address, uint8_t data)
{
	ee_isAvailable = 0;
	ee_stackData[ee_stackCount]._address = address;
	ee_stackData[ee_stackCount]._dataCount = 0;
	ee_stackData[ee_stackCount]._data[ee_stackData[ee_stackCount]._dataCount] = data;
	ee_stackData[ee_stackCount]._dataCount++;
	ee_stackCount++;
	EECR |= Bit(EEMPE);
	EECR |= Bit(EEPE);
	EECR |= Bit(EERIE);
	return 1;
}

uint8_t EEPROM_ReadBlock(uint16_t address, uchar_t * data, uint8_t sizeBlock)
{
	uint8_t length = 0;
	while (length < sizeBlock)
	{
		*data = EEPROM_ReadByte(address);
		//UART_Transmit(*data);
		data++;
		address++;
		length++;
	}

	return length;
}

uint8_t EEPROM_WriteBlock(uint16_t address, uint8_t * data, uint8_t sizeBlock)
{
	ee_isAvailable = 0;
	ee_address = address;
	ee_stackData[ee_stackCount]._address = address;
	ee_stackData[ee_stackCount]._dataCount = 0;
	while (ee_stackData[ee_stackCount]._dataCount < sizeBlock) {
		//	EEPROM_WriteByte(*address, *str);
		ee_stackData[ee_stackCount]._data[ee_stackData[ee_stackCount]._dataCount] = *data;
		ee_stackData[ee_stackCount]._dataCount++;
		data++;
	}
	ee_stackCount++;
	EECR |= Bit(EEMPE);
	EECR |= Bit(EEPE);
	EECR |= Bit(EERIE);
	return ee_stackData[ee_stackCount-1]._dataCount;
}

uint8_t EEPROM_Available() {
	return ee_isAvailable;
}

void EEPROM_GetAllData()
{
	if (ee_isAvailable == 1) {
		uint8_t dataArr[4];
		EEPROM_ReadBlock(ee_angle_id, dataArr, 4);
		ADC_angle = (dataArr[0] << 24) | (dataArr[1] << 16) | (dataArr[2] << 8) | dataArr[3];
		EEPROM_ReadBlock(ee_voltage_id, dataArr, 2);
		ADC_voltage = (dataArr[0] << 8) | dataArr[1];
	}
}

void EEPROM_SaveAllData()
{
	if (ee_isAvailable == 1) {
		uint8_t angle4byte[] = { ADC_angle >> 24, ADC_angle >> 16, ADC_angle >> 8, ADC_angle };
		uint8_t voltage2byte[] = { ADC_voltage >> 8, ADC_voltage };
		EEPROM_WriteBlock(ee_angle_id, angle4byte, 4);
		EEPROM_WriteBlock(ee_voltage_id, voltage2byte, 2);
	}
}

ISR(EE_READY_vect) {
	static uint8_t _tempStackcount = 0;
	static uint8_t _tempdataCount = 0;
	if (_tempStackcount < ee_stackCount) {
		if (_tempdataCount < ee_stackData[_tempStackcount]._dataCount) {
			EEAR = ee_stackData[_tempStackcount]._address++;
			EEDR = ee_stackData[_tempStackcount]._data[_tempdataCount];
			EECR |= Bit(EEMPE);
			EECR |= Bit(EEPE);
			_tempdataCount++;
		}
		else {
			_tempStackcount++;
			_tempdataCount = 0;
		}
	}
	else {
		ee_stackCount = 0;
		_tempStackcount = 0;
		_tempdataCount = 0;
		ee_isAvailable = 1;
		EECR &= ~Bit(EERIE);
	}
}
