// 
// 
// 

#include "SYS.h"
#include "RAM.h"
#include "IO.h"
#include "STEP_MOTOR.h"
#include "OS_TimerCounter.h"
#include "LED.h"
#include "SW.h"
#include "ADC.h"

void CPU_Init()
{
	Hardware_Init();
	Software_Init();
	SETFLAG(bF_TaskRunning);
}
void Hardware_Init()
{
	IO_Init();
	OS_TimerCounter_Init();
	LED_Init();
	SW_Init();
	
	//bF_Hardware_Init = 1;

}
void Software_Init()
{
	//Task_init();
	//bF_Software_Init = 1; 
}
