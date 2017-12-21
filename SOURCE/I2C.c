// 
// 
// 

#include "I2C.h"


#include "IO.h"
#include <avr/interrupt.h>

uint8_t i2c_mode_master = 1U;
uint8_t slaveAddress = 0;
static volatile uint8_t slave_rw = 0;
static volatile uint8_t i2c_state;
static volatile uint8_t i2c_error;

static uint8_t i2c_masterBuffer[I2C_BUFFER_LENGTH];
static volatile uint8_t i2c_masterBufferIndex;
static volatile uint8_t i2c_masterBufferLength;

static uint8_t i2c_txBuffer[I2C_BUFFER_LENGTH];
static volatile uint8_t i2c_txBufferIndex;
static volatile uint8_t i2c_txBufferLength;

static uint8_t i2c_rxBuffer[I2C_BUFFER_LENGTH];
static volatile uint8_t i2c_rxBufferIndex;

static void (*i2c_onSlaveReceive)(uint8_t*, uint8_t);
static void (*i2c_onSlaveTransmit)(void);

void I2C_MasterInit()
{
	i2c_state = I2C_READY;
	
	IOPort_Write(A_4, HIGH);
	IOPort_Write(A_5, HIGH);
	/*SCL CLOCK = (CPU CLOCK FREQUENCY) / (16+2*(TWBR)*4^TWPS) = 100KHz*/
	TWBR = ((F_CPU / 100000) - 16) / (2 * 1);
	TWCR = Bit(TWEN) | Bit(TWIE) | Bit(TWEA);
	TWSR = 0x00; // Prescaler: 1
}

void I2C_SlaveInit(uint8_t address)
{
	i2c_mode_master = 0U;
	slaveAddress = address;
	TWAR = slaveAddress << 1;
	I2C_MasterInit();
}

uint8_t I2C_MasterRead(uint8_t address, uint8_t* data, uint8_t length)
{
	uint8_t i;

	// ensure data will fit into buffer
	if (I2C_BUFFER_LENGTH < length) {
		return 0;
	}
	// wait until twi is ready, become master receiver
	while (I2C_READY != i2c_state) {
		continue;
	}
	i2c_state = I2C_MRX;
	// reset error state (0xFF.. no error occured)
	i2c_error = 0xFF;

	// initialize buffer iteration vars
	i2c_masterBufferIndex = 0;
	i2c_masterBufferLength = length - 1;  
	
	slave_rw = TW_READ;
	slave_rw |= address << 1;
	// send start condition
	//TWCR = TWCR_DEFAULT_ACK | Bit(TWSTA);
	TWCR = TWCR_DEFAULT_ACK | Bit(TWSTA);
	// wait for read operation to complete
	while (I2C_MRX == i2c_state) {
		continue;
	}
	if (i2c_masterBufferIndex < length)
		length = i2c_masterBufferIndex;

	// copy twi buffer to data
	for (i = 0; i < length; ++i) {
		data[i] = i2c_masterBuffer[i];
	}

	return length;
}

uint8_t I2C_MasterWrite(uint8_t address, uint8_t* data, uint8_t length)
{
	// ensure data will fit into buffer
	if (I2C_BUFFER_LENGTH < length) {
		return I2C_OVERBUFFER;
	}

	// wait until i2c is ready, become master transmitter
	while (I2C_READY != i2c_state) {
		continue;
	}
	i2c_state = I2C_MTX;
	// reset error state (0xFF.. no error occured)
	i2c_error = 0xFF;

	// initialize buffer iteration vars
	i2c_masterBufferIndex = 0;
	i2c_masterBufferLength = length;

	// copy data to i2c buffer
	for (uint8_t i = 0; i < length; ++i) {
		i2c_masterBuffer[i] = data[i];
	}

	// build sla+w, slave device address + w bit
	slave_rw = TW_WRITE;
	slave_rw |= address << 1;

	// send start condition
	TWCR = Bit(TWINT) | Bit(TWEA) | Bit(TWEN) | Bit(TWIE) | Bit(TWSTA);	// enable INTs

																		// wait for write operation to complete
	while (I2C_MTX == i2c_state) {
		continue;
	}

	switch (i2c_error)
	{
	case 0xFF:
		return I2C_SUCCESS;	// success
	case TW_MT_SLA_NACK:
		return I2C_ADDRESS_NACK;	// error: address send, nack received
	case TW_MT_DATA_NACK:
		return I2C_DATA_NACK;	// error: data send, nack received
	default:
		return I2C_OTHER_ERROR;	// other i2c error
	}
}

uint8_t i2c_SlaveTransmit(const uint8_t* data, uint8_t length)
{
	uint8_t i;

	// ensure data will fit into buffer
	if (I2C_BUFFER_LENGTH < (i2c_txBufferLength + length)) {
		return 1;
	}

	// ensure we are currently a slave transmitter
	if (I2C_STX != i2c_state) {
		return 2;
	}

	// set length and copy data into tx buffer
	for (i = 0; i < length; ++i) {
		i2c_txBuffer[i2c_txBufferLength + i] = data[i];
	}
	i2c_txBufferLength += length;

	return 0;
}

void I2C_onSlaveReceived(void (*callbackFunc)(uint8_t*,uint8_t)) {
	i2c_onSlaveReceive = callbackFunc;
}

void I2C_onSlaveRequest(void(*callbackFunc)(void)) {
	i2c_onSlaveTransmit = callbackFunc;
}

//void I2C_Start()
//{
//	TWCR = Bit(TWINT) | Bit(TWEN) | Bit(TWSTA);
//	while (!(TWCR & Bit(TWINT)));
//}
//
//void I2C_Write(uchar_t x)
//{
//	TWDR = x;
//	TWCR = Bit(TWINT) | Bit(TWEN);
//	while (!(TWCR & Bit(TWINT)));
//}
//
//uint8_t I2C_Read()
//{
//	TWCR = Bit(TWINT) | Bit(TWEN);
//	while (!(TWCR & Bit(TWINT)));
//	return TWDR;
//}

void I2C_Stop() {
	TWCR = TWCR_DEFAULT_ACK | Bit(TWSTO);
	while (TWCR & Bit(TWSTO)) {
		continue;
	}
	i2c_state = I2C_READY;
}


ISR(TWI_vect)
{
	switch (TW_STATUS) {
		// All Master
	case TW_START:     // sent start condition
	case TW_REP_START: // sent repeated start condition
					   // copy device address and r/w bit to output register and ack
		TWDR = slave_rw;
		TWCR = TWCR_DEFAULT_ACK;
		break;

		// Master Transmitter
	case TW_MT_SLA_ACK:  // slave receiver acked address
	case TW_MT_DATA_ACK: // slave receiver acked data
						 // if there is data to send, send it, otherwise stop 
		if (i2c_masterBufferIndex < i2c_masterBufferLength) {
			// copy data to output register and ack
			TWDR = i2c_masterBuffer[i2c_masterBufferIndex++];
			TWCR = TWCR_DEFAULT_ACK;
		}
		else {
			I2C_Stop();
		}
		break;
	case TW_MT_SLA_NACK:  // address sent, nack received
		i2c_error = TW_MT_SLA_NACK;
		I2C_Stop();
		break;
	case TW_MT_DATA_NACK: // data sent, nack received
		i2c_error = TW_MT_DATA_NACK;
		I2C_Stop();
		break;
	case TW_MT_ARB_LOST: // lost bus arbitration
		i2c_error = TW_MT_ARB_LOST;
		TWCR = TWCR_DEFAULT_ACK;
		i2c_state = I2C_READY;
		break;

		// Master Receiver
	case TW_MR_DATA_ACK: // data received, ack sent
						 // put byte into buffer
		i2c_masterBuffer[i2c_masterBufferIndex++] = TWDR;
	case TW_MR_SLA_ACK:  // address sent, ack received
						 // ack if more bytes are expected, otherwise nack
		if (i2c_masterBufferIndex < i2c_masterBufferLength) {
			TWCR = TWCR_DEFAULT_ACK;
		}
		else {
			TWCR = TWCR_DEFAULT_NACK;
		}
		break;
	case TW_MR_DATA_NACK: // data received, nack sent
						  // put final byte into buffer
		i2c_masterBuffer[i2c_masterBufferIndex++] = TWDR;
		I2C_Stop();
		break;
	case TW_MR_SLA_NACK: // address sent, nack received
		I2C_Stop();
		break;
		// TW_MR_ARB_LOST handled by TW_MT_ARB_LOST case

		// Slave Receiver
	case TW_SR_SLA_ACK:   // addressed, returned ack
	case TW_SR_GCALL_ACK: // addressed generally, returned ack
	case TW_SR_ARB_LOST_SLA_ACK:   // lost arbitration, returned ack
	case TW_SR_ARB_LOST_GCALL_ACK: // lost arbitration, returned ack
								   // enter slave receiver mode
		i2c_state = I2C_SRX;
		// indicate that rx buffer can be overwritten and ack
		i2c_rxBufferIndex = 0;
		TWCR = TWCR_DEFAULT_ACK;
		break;
	case TW_SR_DATA_ACK:       // data received, returned ack
	case TW_SR_GCALL_DATA_ACK: // data received generally, returned ack
							   // if there is still room in the rx buffer
		if (i2c_rxBufferIndex < I2C_BUFFER_LENGTH) {
			// put byte in buffer and ack
			i2c_rxBuffer[i2c_rxBufferIndex++] = TWDR;
			TWCR = TWCR_DEFAULT_ACK;
		}
		else {
			// otherwise nack
			TWCR = TWCR_DEFAULT_ACK;
		}
		break;
	case TW_SR_STOP: // stop or repeated start condition received
					 // ack future responses and leave slave receiver state
		TWCR = TWCR_DEFAULT_ACK;
		i2c_state = I2C_READY;
		// put a null char after data if there's room
		if (i2c_rxBufferIndex < I2C_BUFFER_LENGTH) {
			i2c_rxBuffer[i2c_rxBufferIndex] = '\0';
		}
		// callback to user defined callback
		i2c_onSlaveReceive(i2c_rxBuffer, i2c_rxBufferIndex);
		// since we submit rx buffer to "wire" library, we can reset it
		i2c_rxBufferIndex = 0;
		break;
	case TW_SR_DATA_NACK:       // data received, returned nack
	case TW_SR_GCALL_DATA_NACK: // data received generally, returned nack
								// nack back at master
		TWCR = TWCR_DEFAULT_NACK;
		break;

		// Slave Transmitter
	case TW_ST_SLA_ACK:          // addressed, returned ack
	case TW_ST_ARB_LOST_SLA_ACK: // arbitration lost, returned ack
								 // enter slave transmitter mode
		i2c_state = I2C_STX;
		// ready the tx buffer index for iteration
		i2c_txBufferIndex = 0;
		// set tx buffer length to be zero, to verify if user changes it
		i2c_txBufferLength = 0;
		// request for txBuffer to be filled and length to be set
		// note: user must call twi_transmit(bytes, length) to do this
		i2c_onSlaveTransmit();
		// if they didn't change buffer & length, initialize it
		if (0 == i2c_txBufferLength) {
			i2c_txBufferLength = 1;
			i2c_txBuffer[0] = 0x00;
		}
		// transmit first byte from buffer, fall
	case TW_ST_DATA_ACK: // byte sent, ack returned
						 // copy data to output register
		TWDR = i2c_txBuffer[i2c_txBufferIndex++];
		// if there is more to send, ack, otherwise nack
		if (i2c_txBufferIndex < i2c_txBufferLength) {
			TWCR = TWCR_DEFAULT_ACK;
		}
		else {
			TWCR = TWCR_DEFAULT_NACK;
		}
		break;
	case TW_ST_DATA_NACK: // received nack, we are done 
	case TW_ST_LAST_DATA: // received ack, but we are done already!
						  // ack future responses
		TWCR = TWCR_DEFAULT_ACK;
		// leave slave receiver state
		i2c_state = I2C_READY;
		break;

		// All
	case TW_NO_INFO:   // no state information
		break;
	case TW_BUS_ERROR: // bus error, illegal stop/start
		i2c_error = TW_BUS_ERROR;
		I2C_Stop();
		break;
	}
}