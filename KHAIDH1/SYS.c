// 
// 
// 

#include "SYS.h"


void CPU_Init()
{
	Hardware_Init();
	Software_Init();

}
void Hardware_Init()
{
	IO_Init();
	Timer_Init(TIMER_1);

	bF_Hardware_Init = 1;

}
void Software_Init()
{
	Task_init();
	bF_Software_Init = 1; 
}
