// 
// 
// 

#include "FailSafe_c.h"

void FailSafe_CheckSYS()
{
	if ( bF_TaskRunning == 0)
	{
		UART_WriteString(" SYS  INIT ERROR ");
	}
	if (g_SystemError != NON_ERROR)
	{
		if (g_RangeError == NG)
		{
			UART_WriteString(" NG ");
		}
		else if (g_RangeError == WARNING)
		{
			
			UART_WriteString(" WARNING ");
		}
		UART_WriteString("Ma loi: ");
		UART_WriteNumber((uint32_t)g_SystemError);
		UART_WriteString("\n ");
	}
}