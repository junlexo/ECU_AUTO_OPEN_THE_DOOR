// EPPROM.h

#ifndef _EEPROM_h
#define _EEPROM_h
#include "PREFERENT.h"

#ifdef __cplusplus
extern "C" {
#endif
	void EEPROM_Init();
	uint8_t EEPROM_ReadByte(uint16_t address);
	uint8_t EEPROM_WriteByte(uint16_t address, uint8_t data);
	uint8_t EEPROM_ReadBlock(uint16_t address, uint8_t* data, uint8_t sizeBlock);
	uint8_t EEPROM_WriteBlock(uint16_t address, uint8_t* data, uint8_t sizeBlock);
	uint8_t EEPROM_Available();

#ifdef __cplusplus
} // extern "C"
#endif

#endif

