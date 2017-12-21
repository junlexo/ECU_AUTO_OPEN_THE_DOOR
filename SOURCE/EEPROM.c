// 
// 
// 

#include "EEPROM.h"
#include <avr/interrupt.h>

static volatile uint8_t ee_isAvailable = 1;
static volatile uint16_t ee_address = 0;

struct DataPacket {
	uint8_t _address;
	uint8_t _data[20];
	volatile uint8_t _dataCount;
};

struct DataPacket ee_stackData[10];
static volatile uint8_t ee_stackCount = 0;

void EEPROM_Init()
{
	if (EEPROM_Available()) {
		uint8_t dataArr[4];
		EEPROM_ReadBlock(ANGLE_ADDRESS, dataArr, 4);
		//angle = (dataArr[2] << 8) | dataArr[3];
		EEPROM_ReadBlock(TEMPERATURE_ADDRESS, dataArr, 2);
		//temperature = (dataArr[0] << 8) | dataArr[1];
		EEPROM_ReadBlock(VOLTAGE_ADDRESS, dataArr, 2);
		//voltage = (dataArr[0] << 8) | dataArr[1];
	}
}

uint8_t EEPROM_ReadByte(uint16_t address)
{
	/*if(ee_isAvailable == 0)
	{*/
	//UART_SendString("O \n");
	//while ((EECR & Bit(EEPE)) == 1);
	EEAR = address;
	EECR = Bit(EERE);
	return EEDR;
	//}
	//else {
	//	//UART_SendString("K \n");
	//	return 0xFF;
	//}
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