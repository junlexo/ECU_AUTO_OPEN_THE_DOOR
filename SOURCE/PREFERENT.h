// PREFERENT.h

#ifndef _PREFERENT_h
#define _PREFERENT_h

#include <avr/io.h>
#include <stddef.h>
#include "IO.h"

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


#define Bit(bit) (1 << (bit))
#define CharToInt(c) ((uint8_t)(c)-'0')
#define IntToChar(i) ((uint8_t)(i)+'0')

#define	CLR	0U
#define	SET	1U

/***************** set/clear flag define ***************/

#define SETFLAG(flag) ((flag)=(1U))
#define CLRFLAG(flag) ((flag)=(0U))
#define TSTFLAG(flag) ((flag))

#define MIN(a,b) ((a>b)?b:a)
#define MAX(a,b) ((a>b)?a:b)
#define MIN_MAX(a,min,max)		((a>max)?max:((a<min)?min:a))

/***************** set/clear timer define ***************/

#define StartTimer(timer,time) ((timer)=(time))
#define IsTimeOut(timer) (((timer)==0U)?1:0)

/***************** set/clear timer define ***************/
#define START_TIMER(timer,time) ((timer)=(time))
#define CHECK_TIMER(timer) (((timer)==0U))
/***************** set/clear counter define ***************/

#define START_COUNTER(counter,times) 	((counter)=(times))
#define CHECK_COUNTER(counter) 			(((counter)==0U))


/******************* Typedef ******************/
typedef void(*FuncPtr)(void*);
typedef unsigned long ulong_t;
typedef long long_t;
typedef float float_t;
typedef double double_t;
typedef unsigned char uchar_t;

typedef struct Data_frame {
	uint8_t commandId;
	uchar_t breakChar;
	uchar_t endFrame;
	uint16_t dataID : 16;
	uint32_t data;
} DataFrame;




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

/*STEP MOTOR */
#define STEP_SPEED_MAX 47
#define STEP_SPEED_MIN 1
#define PIN_SPEED  9
#define PIN_DIR 8
#define PIN_HOLD 7
#define SPEED_DEFAULT 20
#define TIMEWAITTING_CLOSE_INIT 30
#define TimTIMEWAITTING_CLOSE 10
#define CLOSE HIGH
#define OPEN LOW





#endif

