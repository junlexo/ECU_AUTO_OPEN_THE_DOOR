// PREFERENT.h

#ifndef _PREFERENT_h
#define _PREFERENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define HIGH 1
#define LOW 0
#define OUTPUT 1 
#define INPUT 0
#define INPUT_PULLUP 2


#define VOL10DEG 30389
#define VOL_10DEG 20426
#define SEND_ADCVAL_ID 0x0000		
#define SEND_ANGLEVAL_ID 0x0001
#define MAPPING_COL 19
#define MAPPING_ROW 2

#define OFF 0
#define	ON 1
#define	PRESS 2
#define	ERROR 3


/*LED */
#define BLINK250MS 250
#define BLINK500MS 500
#define BLINK1S 1000

/*ADC */
#define ANGLE_ADDRESS 0x00
#define TEMPERATURE_ADDRESS 0x04
#define VOLTAGE_ADDRESS 0x20

/*IO */
#define	MAX_PORT_NUM 22



#endif

