#include "SW.h"
#include "PREFERENT.h"
#include "Timer_count.h"
#include "FLAG.h"
#include "IO.h"
void SW_Init()
{
	g_bF_SW1_Status = 0;
	g_bF_SW2_Status = 0;
}

void SW()
{
	g_bF_SW1_Status = !IOPort_Read(D_11);
	g_bF_SW2_Status = !IOPort_Read(D_10);
}