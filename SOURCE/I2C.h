// I2C.h

#ifndef _I2C_h
#define _I2C_h

#include "PREFERENT.h"


/*@{*/
/* Master */
/** \ingroup util_twi
\def TW_START
start condition transmitted */
#define TW_START		0x08

/** \ingroup util_twi
\def TW_REP_START
repeated start condition transmitted */
#define TW_REP_START		0x10

/******************************************************** Master Transmitter *********************************************************/
/** \ingroup util_twi
\def TW_MT_SLA_ACK
SLA+W transmitted, ACK received */
#define TW_MT_SLA_ACK		0x18

/** \ingroup util_twi
\def TW_MT_SLA_NACK
SLA+W transmitted, NACK received */
#define TW_MT_SLA_NACK		0x20

/** \ingroup util_twi
\def TW_MT_DATA_ACK
data transmitted, ACK received */
#define TW_MT_DATA_ACK		0x28

/** \ingroup util_twi
\def TW_MT_DATA_NACK
data transmitted, NACK received */
#define TW_MT_DATA_NACK		0x30

/** \ingroup util_twi
\def TW_MT_ARB_LOST
arbitration lost in SLA+W or data */
#define TW_MT_ARB_LOST		0x38

/********************************************************** Master Receiver ********************************************************/
/** \ingroup util_twi
\def TW_MR_ARB_LOST
arbitration lost in SLA+R or NACK */
#define TW_MR_ARB_LOST		0x38

/** \ingroup util_twi
\def TW_MR_SLA_ACK
SLA+R transmitted, ACK received */
#define TW_MR_SLA_ACK		0x40

/** \ingroup util_twi
\def TW_MR_SLA_NACK
SLA+R transmitted, NACK received */
#define TW_MR_SLA_NACK		0x48

/** \ingroup util_twi
\def TW_MR_DATA_ACK
data received, ACK returned */
#define TW_MR_DATA_ACK		0x50

/** \ingroup util_twi
\def TW_MR_DATA_NACK
data received, NACK returned */
#define TW_MR_DATA_NACK		0x58

/******************************************************* Slave Transmitter *******************************************************/
/** \ingroup util_twi
\def TW_ST_SLA_ACK
SLA+R received, ACK returned */
#define TW_ST_SLA_ACK		0xA8

/** \ingroup util_twi
\def TW_ST_ARB_LOST_SLA_ACK
arbitration lost in SLA+RW, SLA+R received, ACK returned */
#define TW_ST_ARB_LOST_SLA_ACK	0xB0

/** \ingroup util_twi
\def TW_ST_DATA_ACK
data transmitted, ACK received */
#define TW_ST_DATA_ACK		0xB8

/** \ingroup util_twi
\def TW_ST_DATA_NACK
data transmitted, NACK received */
#define TW_ST_DATA_NACK		0xC0

/** \ingroup util_twi
\def TW_ST_LAST_DATA
last data byte transmitted, ACK received */
#define TW_ST_LAST_DATA		0xC8

/**************************************************************** Slave Receiver **************************************************************/
/** \ingroup util_twi
\def TW_SR_SLA_ACK
SLA+W received, ACK returned */
#define TW_SR_SLA_ACK		0x60

/** \ingroup util_twi
\def TW_SR_ARB_LOST_SLA_ACK
arbitration lost in SLA+RW, SLA+W received, ACK returned */
#define TW_SR_ARB_LOST_SLA_ACK	0x68

/** \ingroup util_twi
\def TW_SR_GCALL_ACK
general call received, ACK returned */
#define TW_SR_GCALL_ACK		0x70

/** \ingroup util_twi
\def TW_SR_ARB_LOST_GCALL_ACK
arbitration lost in SLA+RW, general call received, ACK returned */
#define TW_SR_ARB_LOST_GCALL_ACK 0x78

/** \ingroup util_twi
\def TW_SR_DATA_ACK
data received, ACK returned */
#define TW_SR_DATA_ACK		0x80

/** \ingroup util_twi
\def TW_SR_DATA_NACK
data received, NACK returned */
#define TW_SR_DATA_NACK		0x88

/** \ingroup util_twi
\def TW_SR_GCALL_DATA_ACK
general call data received, ACK returned */
#define TW_SR_GCALL_DATA_ACK	0x90

/** \ingroup util_twi
\def TW_SR_GCALL_DATA_NACK
general call data received, NACK returned */
#define TW_SR_GCALL_DATA_NACK	0x98

/** \ingroup util_twi
\def TW_SR_STOP
stop or repeated start condition received while selected */
#define TW_SR_STOP		0xA0

/* Misc */
/** \ingroup util_twi
\def TW_NO_INFO
no state information available */
#define TW_NO_INFO		0xF8

/** \ingroup util_twi
\def TW_BUS_ERROR
illegal start or stop condition */
#define TW_BUS_ERROR		0x00


/**
* \ingroup util_twi
* \def TW_STATUS_MASK
* The lower 3 bits of TWSR are reserved on the ATmega163.
* The 2 LSB carry the prescaler bits on the newer ATmegas.
*/
#define TW_STATUS_MASK		(Bit(TWS7)|Bit(TWS6)|Bit(TWS5)|Bit(TWS4)|\
							Bit(TWS3))
/**
* \ingroup util_twi
* \def TW_STATUS
*
* TWSR, masked by TW_STATUS_MASK
*/
#define TW_STATUS		(TWSR & TW_STATUS_MASK)
/*@}*/

/**
* \name R/~W bit in SLA+R/W address field.
*/

/*@{*/
/** \ingroup util_twi
\def TW_READ
SLA+R address */
#define TW_READ		1U

/** \ingroup util_twi
\def TW_WRITE
SLA+W address */
#define TW_WRITE	0U
/*@}*/

#define I2C_BUFFER_LENGTH 32U
#define TWCR_DEFAULT_ACK (Bit(TWEN) | Bit(TWIE) | Bit(TWINT) | Bit(TWEA))
#define TWCR_DEFAULT_NACK (Bit(TWEN) | Bit(TWIE) | Bit(TWINT))

enum i2c_state {
	I2C_READY,
	I2C_MRX,
	I2C_MTX,
	I2C_SRX,
	I2C_STX
};

enum i2c_error
{
	I2C_SUCCESS,
	I2C_OVERBUFFER,
	I2C_ADDRESS_NACK,
	I2C_DATA_NACK,
	I2C_OTHER_ERROR
};

#ifdef __cplusplus
extern "C" {
#endif

	void I2C_MasterInit();
	void I2C_SlaveInit(uint8_t address);
	uint8_t I2C_MasterRead(uint8_t address, uint8_t * data, uint8_t length);
	uint8_t I2C_MasterWrite(uint8_t address, uint8_t * data, uint8_t length);
	uint8_t i2c_SlaveTransmit(const uint8_t * data, uint8_t length);
	void I2C_onSlaveReceived(void (*callbackFunc)(uint8_t *, uint8_t));
	void I2C_onSlaveRequest(void (*callbackFunc)(void));

	//void I2C_Start();
	//void I2C_Write(uchar_t x);
	//uint8_t I2C_Read();

#ifdef __cplusplus
} // extern "C"
#endif

#endif

