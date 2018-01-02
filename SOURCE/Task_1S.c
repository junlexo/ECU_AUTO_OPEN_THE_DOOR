
#include "Task_1S.h"
#include "PREFERENT.h"
#include "IO.h"
#include "Timer_count.h"
#include "FLAG.h"
#include "UARTDebugging.h"
#include "FailSafe.h"

void Task_1S()
{
		DBG_NotifyUARTError();
		FailSafe_CheckSYS();
}


