// 
// 
// 

#include "IO.h"
void IO_Init()
{
/*****     SW    *****/
	SetPin(D_10, INPUT_PULLUP); // SW2 in number_port 10
	SetPin(D_11, INPUT_PULLUP); // SW1 in number_port 11
/*****     LED    *****/
	SetPin(D_12, OUTPUT); // Blink LED1 in number_port 12
	SetPin(D_13, OUTPUT); // Blink LED0 in number_port 13
/*****   STEP MOTOR       ******/
#if STEPMOTOR == ON
	SetPin(D_8, OUTPUT);
	SetPin(D_9, OUTPUT);
	SetPin(D_7, OUTPUT);

	SetPin(D_3, INPUT_PULLUP);
#endif // STEP MOTOR
}

const uint8_t port_arr[MAX_PORT_NUM] = {
	PORTD0, PORTD1, PORTD2, PORTD3, PORTD4, PORTD5, PORTD6, PORTD7,
	PORTB0, PORTB1, PORTB2, PORTB3, PORTB4, PORTB5, PORTB6, PORTB7,
	PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, PORTC5,
};

const uint8_t port_reg_addr_arr[9] = {
	(uint8_t)&DDRD,
	(uint8_t)&DDRB,
	(uint8_t)&DDRC,
	(uint8_t)&PORTD,
	(uint8_t)&PORTB,
	(uint8_t)&PORTC,
	(uint8_t)&PIND,
	(uint8_t)&PINB,
	(uint8_t)&PINC,
};


void ClearRegisters()
{
	DDRD = 0x00;
	DDRB = 0x00;
	DDRC = 0x00;
	PORTD = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
}

void SetPin(uint8_t pinNum, uint8_t pinMode)
{
	if (pinMode == INPUT_PULLUP) {
		pinMode = INPUT;
		IOPort_Write(pinNum, HIGH);
	}

	if (pinNum < MAX_PORT_NUM) {
		volatile uint8_t * dddr_reg = port_reg_addr_arr[(1 << (pinNum >> 4)) & (pinNum >> 3)];
		*dddr_reg |= (pinMode << port_arr[pinNum]);
	}
}

void IOPort_Write(uint8_t pinNum, uint8_t val)
{
	if (pinNum < MAX_PORT_NUM) {
		volatile uint8_t * port_reg = port_reg_addr_arr[((1 << (pinNum >> 4)) & (pinNum >> 3)) + 3];
		if (val >= 1)
			*port_reg |= (1 << port_arr[pinNum]);
		else
			*port_reg &= ~(1 << port_arr[pinNum]);
	}
}

uint8_t IOPort_Read(uint8_t pinNum)
{
	if (pinNum < MAX_PORT_NUM) {
		volatile uint8_t * pin_reg = port_reg_addr_arr[((1 << (pinNum >> 4)) & (pinNum >> 3)) + 6];
		if (*pin_reg & (1 << port_arr[pinNum]))
			return HIGH;
		else
			return LOW;
	}
	else {
		return LOW;
	}
}

