// 
// 
// 

#include "UART.h"
#include <avr/interrupt.h>
#include "UARTDebugging.h"

static volatile uint8_t tx_ring_head;
static volatile uint8_t tx_ring_tail;
static volatile uint8_t tx_ring_data[RING_SIZE];

static volatile uint8_t rx_ring_head;
static volatile uint8_t rx_ring_tail;
static volatile uint8_t rx_ring_data[RING_SIZE];

static uint8_t tx_ring_add(uint8_t c);
static uint8_t tx_ring_remove(void);
static uint8_t rx_ring_add(uint8_t c);
static uint8_t rx_ring_remove(void);


void UART_Init(uint16_t baudRate)
{
	uint16_t ubrr = UBRR(baudRate);

	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = /*(1 << USBS0) | */(1 << UCSZ00) | (1 << UCSZ01);
	tx_ring_head = 0;
	rx_ring_head = 0;
	tx_ring_tail = 0;
	rx_ring_tail = 0;
}

void UART_Write(uint8_t data) {
	// Wait until there's room in the ring buffer
	if (UART_IsTxBufferFull())
		return;

	// Add the data to the ring buffer now that there's room
	tx_ring_add(data);

	// Ensure the data register empty interrupt is turned on
	// (it gets turned off automatically when the UART is idle)
	UCSR0B |= (1 << UDRIE0);
}

uint8_t UART_Read(void) {
	// Wait until a character is available to read
	if (UART_IsRxBufferEmpty())
		return 0;

	// Then return the character
	return rx_ring_remove();
}

void UART_WriteString(uint8_t * str)
{
	while (*str != 0x00)
	{
		UART_Write(*str);
		str++;
	}
}

void UART_WriteNumber(uint32_t num)
{
	uint8_t str[11];
	uint8_t i = 1;
	while (num) {
		str[i] = num % 10 + '0';
		i++;
		num = num / 10;
	}
	for (uint8_t j = i - 1; j >= 1; j--) {
		UART_Write(str[j]);
	}
}

uint8_t UART_IsRxBufferEmpty(void) {
	// If the head and tail are equal, the buffer is empty.
	return (rx_ring_head == rx_ring_tail) ? 1 : 0;
}

uint8_t UART_IsTxBufferEmpty(void) {
	// If the head and tail are equal, the buffer is empty.
	return (tx_ring_head == tx_ring_tail) ? 1 : 0;
}

uint8_t UART_IsRxBufferFull(void) {
	// If the head is one slot behind the tail, the buffer is full.
	return (((rx_ring_head + 1) % RING_SIZE) == rx_ring_tail) ? 1 : 0;
}

uint8_t UART_IsTxBufferFull(void) {
	// If the head is one slot behind the tail, the buffer is full.
	return (((tx_ring_head + 1) % RING_SIZE) == tx_ring_tail) ? 1 : 0;
}

static uint8_t tx_ring_add(uint8_t c) {
	uint8_t next_head = (tx_ring_head + 1) % RING_SIZE;
	if (next_head != tx_ring_tail) {
		/* there is room */
		tx_ring_data[tx_ring_head] = c;
		tx_ring_head = next_head;
		return 0;
	}
	else {
		/* no room left in the buffer */
		return -1;
	}
}

static uint8_t tx_ring_remove(void) {
	if (tx_ring_head != tx_ring_tail) {
		uint8_t c = tx_ring_data[tx_ring_tail];
		tx_ring_tail = (tx_ring_tail + 1) % RING_SIZE;
		return c;
	}
	else {
		return 0xFF;
	}
}

static uint8_t rx_ring_add(uint8_t c) {
	uint8_t next_head = (rx_ring_head + 1) % RING_SIZE;
	if (next_head != rx_ring_tail) {
		/* there is room */
		rx_ring_data[rx_ring_head] = c;
		rx_ring_head = next_head;
		return 1;
	}
	else {
		/* no room left in the buffer */
		return 0;
	}
}

static uint8_t rx_ring_remove(void) {
	if (rx_ring_head != rx_ring_tail) {
		uint8_t c = rx_ring_data[rx_ring_tail];
		rx_ring_tail = (rx_ring_tail + 1) % RING_SIZE;
		return c;
	}
	else {
		return 0xFF;
	}
}

ISR(USART_RX_vect) {
	uint8_t data = UDR0;
	rx_ring_add(data);
	DBG_checkErrorUART(data);
}

ISR(USART_UDRE_vect) {
	if (!UART_IsTxBufferEmpty()) {
		// Send the next character if we have one to send
		UDR0 = tx_ring_remove();
	}
	else {
		// Turn off the data register empty interrupt if
		// we have nothing left to send
		UCSR0B &= ~(1 << UDRIE0);
	}
}