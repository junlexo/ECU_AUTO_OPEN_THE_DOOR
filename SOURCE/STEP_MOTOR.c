// 
// 
// 

#include "STEP_MOTOR.h"

void STEP_MANNER()
{
#if DEBUG != ON	
	if (BTN1_STATUS == 2U)
	{
		SETFLAG(g_bF_BT1_Press);
	}
	else
	{
		CLRFLAG(g_bF_BT1_Press);
	}
	if (BTN2_STATUS == 2U)
	{
		SETFLAG(g_bF_BT2_Press);
	}
	else
	{
		CLRFLAG(g_bF_BT2_Press);
	}
	if (ADC_FIR_STATUS == 1U)
	{
		SETFLAG(g_bF_FIR_Status);
	}
	else
	{
		CLRFLAG(g_bF_FIR_Status);
	}

#else
	g_bF_DOOR_OPEN = 0;
	g_bF_BT2_Press = 0;
	g_bF_BT1_Press = 0;
	testdemention = 1;
#endif
	STEP_InitStart();
	if (TSTFLAG(g_bF_STEP_Init))
	{
		g_ui32_StepDemention = 3000;
		g_bF_STEP_TAKE_DEMENTION = 1;
		g_bF_FIR_Status = 0;

		if ((TSTFLAG(g_bF_BT2_Press)) || (TSTFLAG(g_bF_DOOR_OPEN)))
		{
			if ((g_ui32_StepDemention != 0) && (g_bF_STEP_Start == 0))
			{
				SETFLAG(g_bF_STEP_Start);
				SETFLAG(g_bF_STEPMOTOR_DIR_Open);
			}
			else
			{
				;
			}

		}
		if ((g_ui32_StepDemention == 0) || (g_bF_STEP_TAKE_DEMENTION == 0))
		{
			STEP_InitDIR();
		}
		STEP_Control();
	}

	STEPMOTOR_CheckFailSafe();
}
/*
Funtion : STEP_Control()
Dep : Control Step motor when recieve Open signal.
Author : KhaiDH1
SYS: Run 1 ms
*/
void STEP_Control()
{
	if (TSTFLAG(g_bF_STEP_Start))
	{

		if (TSTFLAG(g_bF_STEPMOTOR_DIR_Open))
		{
			if (!TSTFLAG(g_bF_SW2_Status))
			{
				STEP_Running_Open();
				STEP_CheckTimerOpen();
				g_bF_READ_DEMENTION = 0;
			}
			else
			{
				STEP_STOP();
				STEP_READ_DEMENTION();
				STEP_SPEED_RANGE();
				STEP_WAITING_CLOSE();
				CLRFLAG(g_bF_STEP_ReOpen);
			}
		}
		else if (TSTFLAG(g_bF_STEPMOTOR_DIR_Close))
		{
			if (TSTFLAG(g_bF_SW1_Status) == 1)
			{
				STEP_STOP();
				CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
				CLRFLAG(g_bF_STEP_ReOpen);
				CLRFLAG(g_bF_STEP_Start);
			}
			else if ((TSTFLAG(g_bF_FIR_Status)) || (TSTFLAG(g_bF_BT1_Press)))
			{
				if (!(TSTFLAG(g_bF_FIR_Status)))
				{
					SETFLAG(g_bF_STEP_ReOpen);
					STEP_STOP();
					STEP_READ_DEMENTION();
					STEP_SPEED_RANGE();
					SETFLAG(g_bF_STEPMOTOR_DIR_Open);
					CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
				}

			}
			else if ((TSTFLAG(g_bF_STEP_Start)))
			{
				STEP_Running_Close();
				g_bF_READ_DEMENTION = 0;
				if ((CHECK_TIMER(g_t_ui8_S_StepMotor_WattingClose)))
				{
					SETFLAG(g_bF_FS_StepMotor_TimeClose);
				}
			}
			else
			{
				;
			}



		}
		else
		{
			;

		}

	}
	else
	{


	}

}
void STEPMOTOR_CheckFailSafe()
{
	if (TSTFLAG(g_bF_FS_StepMotor_TimeClose))
	{
		// ma loi 0x06
	}
	if (TSTFLAG(g_bF_FS_StepMotor_TimeOpen))
	{
		// ma loi 0x05
	}
	if (TSTFLAG(g_bF_FS_StepMotor_TimeCloseInit))
	{
		// ma loi 0x04
	}
}

void STEP_CheckTimerOpen()
{
	if ((!(TSTFLAG(g_bF_STEP_WAITTING_OPEN))) && (CHECK_TIMER(g_t_ui8_S_StepMotor_WattingOpen)))
	{
		START_TIMER(g_t_ui8_S_StepMotor_WattingOpen, TIMEWATTING_OPEN);
		SETFLAG(g_bF_STEP_WAITTING_OPEN);
	}
	else if ((TSTFLAG(g_bF_STEP_WAITTING_OPEN)) && (CHECK_TIMER(g_t_ui8_S_StepMotor_WattingOpen)))
	{
		SETFLAG(g_bF_FS_StepMotor_TimeOpen);
		CLRFLAG(g_bF_STEP_WAITTING_OPEN);
		STEP_STOP();
		if (TSTFLAG(g_bF_STEP_Start))
		{
			CLRFLAG(g_bF_STEP_Start);
		}
	}
	else
	{
		;
	}
}
void STEP_Running_Open()
{
	if (TSTFLAG(g_bF_STEPMOTOR_DIR_Open))
	{
		STEP_RUN();
		CLRFLAG(g_bF_STEP_Cal_Range);
		SETFLAG(g_bF_STEPMOTOR_Dimension);
		IOPort_Write(PIN_DIR, OPEN);
		STEP_Control_Speed();
	}

}

void STEP_Running_Close()
{
	if (TSTFLAG(g_bF_STEPMOTOR_DIR_Close))
	{
		STEP_RUN();
		CLRFLAG(g_bF_STEP_Cal_Range);
		SETFLAG(g_bF_STEPMOTOR_Dimension);
		IOPort_Write(PIN_DIR, CLOSE);
		STEP_Control_Speed();
	}

}


void STEP_WAITING_CLOSE()
{
	if ((CHECK_TIMER(g_t_ui8_S_StepMotor_WattingClose)) || (TSTFLAG(g_bF_BT2_Press)))
	{
		SETFLAG(g_bF_STEPMOTOR_DIR_Close);
		CLRFLAG(g_bF_STEPMOTOR_DIR_Open);
		g_t_ui8_S_StepMotor_WattingClose = 0;
		START_TIMER(g_t_ui8_S_StepMotor_WattingClose, FAILSAFE_TIMEWAITTING_CLOSE);
	}
	else
	{
		;
	}
}

/*
Funtion : STEP_InitStart()
Dep :
Author : KhaiDH1
SYS: Run 1 ms
*/
void STEP_InitStart()
{
	if (TSTFLAG(g_bF_STEP_Init) == 0)
	{


		if ((g_bF_SW1_Status == 0) && (g_bF_STEPMOTOR_Stop == 1) && (g_bF_STEP_Init == 0))
		{
			SETFLAG(g_bF_STEPMOTOR_DIR_Close);
			CLRFLAG(g_bF_STEPMOTOR_DIR_Open);
			STEP_RUN_DEFAULT();
			START_TIMER(g_t_ui8_S_StepMotor_WattingClose, TIMEWAITTING_CLOSE_INIT);

		}
		else if ((g_bF_SW1_Status == 1) && (g_bF_STEP_Init == 0))
		{
			STEP_STOP();
			g_ui32_StepCount = 0;
			CLRFLAG(g_bF_STEPMOTOR_DIR_Open);
			CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
			SETFLAG(g_bF_STEP_Init);
		}
		else
		{
			;
		}
		if ((TSTFLAG(g_bF_STEPMOTOR_Running)) && (TSTFLAG(g_bF_STEPMOTOR_DIR_Close)) && (TSTFLAG(g_bF_SW1_Status) == 0))
		{

			if (CHECK_TIMER(g_t_ui8_S_StepMotor_WattingClose))
			{
				STEP_STOP();
				SETFLAG(g_bF_STEP_Init);
				g_bF_STEPMOTOR_DIR_Close = 0;
				SETFLAG(g_bF_FS_StepMotor_TimeCloseInit);
			}
			else
			{
				;
			}
		}
		else if ((TSTFLAG(g_bF_STEPMOTOR_Running)) && (TSTFLAG(g_bF_STEPMOTOR_DIR_Close)) && (TSTFLAG(g_bF_SW1_Status)))
		{
			STEP_STOP();
			g_ui32_StepCount = 0;
			CLRFLAG(g_bF_STEPMOTOR_DIR_Open);
			CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
			SETFLAG(g_bF_STEP_Init);
		}

	}
}

void STEP_InitDIR()
{

	if ((TSTFLAG(g_bF_SW1_Status)) && (g_bF_READ_DEMENTION == 0))
	{
		g_ui32_StepCount = 0;
		SETFLAG(g_bF_STEPMOTOR_DIR_Open);
		CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
		STEP_CheckTimerOpen();
		STEP_RUN_DEFAULT();
	}
	else if ((TSTFLAG(g_bF_SW2_Status)) && (TSTFLAG(g_bF_STEPMOTOR_DIR_Open)) && (g_bF_READ_DEMENTION == 0))
	{

		STEP_STOP();
		STEP_READ_DEMENTION();
		g_ui32_StepDemention = demention_open;
		SETFLAG(g_bF_STEPMOTOR_DIR_Close);
		CLRFLAG(g_bF_STEPMOTOR_DIR_Open);
		STEP_RUN_DEFAULT();

	}
	else if ((TSTFLAG(g_bF_SW1_Status)) && (TSTFLAG(g_bF_STEPMOTOR_DIR_Close)) && (g_bF_READ_DEMENTION == 1))
	{
		STEP_STOP();
		CLRFLAG(g_bF_STEPMOTOR_DIR_Open);
		CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
		SETFLAG(g_bF_STEP_TAKE_DEMENTION);
	}
	else
	{
		;
	}

}

void STEP_READ_DEMENTION()
{
	if (TSTFLAG(g_bF_READ_DEMENTION) == 0)
	{
		if ((TSTFLAG(g_bF_SW2_Status)))
		{
			demention_open = g_ui32_StepCount;
			START_TIMER(g_t_ui8_S_StepMotor_WattingClose, TIMEWAITTING_CLOSE);
			SETFLAG(g_bF_READ_DEMENTION);
		}
		else if ((TSTFLAG(g_bF_STEPMOTOR_DIR_Close)) && (TSTFLAG(g_bF_STEP_ReOpen)))
		{
			demention_close = g_ui32_StepCount;
			SETFLAG(g_bF_READ_DEMENTION);
		}
		g_ui32_StepCount = 0;
	}

}



void STEP_CLOSE_DEFAULT()
{
	if (TSTFLAG(g_bF_STEPMOTOR_DIR_Close))
	{
		STEP_Speed(SPEED_DEFAULT);
		IOPort_Write(PIN_DIR, CLOSE);
	}
}



void STEP_RUN_DEFAULT()
{
	if (TSTFLAG(g_bF_STEPMOTOR_DIR_Open))
	{
		STEP_Speed(SPEED_DEFAULT);
		IOPort_Write(PIN_DIR, OPEN);
	}

	else if (TSTFLAG(g_bF_STEPMOTOR_DIR_Close))
	{
		STEP_Speed(SPEED_DEFAULT);
		IOPort_Write(PIN_DIR, CLOSE);
	}
	STEP_RUN();

}



void STEP_OPEN_DEFAULT()
{
	if (TSTFLAG(g_bF_STEPMOTOR_DIR_Open))
	{
		STEP_Speed(SPEED_DEFAULT);
		IOPort_Write(PIN_DIR, OPEN);
	}

}



void STEP_Control_Speed()
{

	if (TSTFLAG(g_bF_STEPMOTOR_Running) && TSTFLAG(g_bF_STEP_Cal_Range))
	{
		fullspeed = step_Decelerating + step_Fullspeed;

		//accelerating = step_Decelerating + step_Fullspeed + step_Accelerating;
		if (g_ui32_StepCount < step_Decelerating)
		{
			step_Speed = step_Speed + 10;
		}
		else if ((g_ui32_StepCount > step_Decelerating) && (g_ui32_StepCount <  fullspeed))
		{
			step_Speed = 240;
		}
		else if (g_ui32_StepCount >  fullspeed)
		{
			step_Speed = step_Speed - 10;
		}
		else
		{
			;
		}
		STEP_Speed(step_Speed);
	}
	else
	{
		step_Speed = 100; // Value Default
		STEP_Speed(step_Speed);
	}
}


void STEP_STOP()
{

	CLRFLAG(g_bF_STEPMOTOR_Dimension);
	SETFLAG(g_bF_STEPMOTOR_Stop);
	CLRFLAG(g_bF_STEPMOTOR_Running);
}


void STEP_RUN()
{
	SETFLAG(g_bF_STEPMOTOR_Dimension);
	CLRFLAG(g_bF_STEPMOTOR_Stop);
	SETFLAG(g_bF_STEPMOTOR_Running);

}


void STEP_SPEED_RANGE()
{
	uint16_t u16tmp;
	uint32_t u16tmp1;
	if (TSTFLAG(g_bF_STEP_Cal_Range) == 0)

		if (g_ui32_StepDemention != 0)
		{
			if (TSTFLAG(g_bF_STEPMOTOR_DIR_Open))
			{
				u16tmp1 = g_ui32_StepDemention;
			}
			else if (TSTFLAG(g_bF_STEP_ReOpen))
			{
				u16tmp1 = demention_close;
			}
			u16tmp1 = u16tmp1 / 2;
			u16tmp = u16tmp1 - step_Fullspeed;
			step_Decelerating = u16tmp / 2;
			step_Accelerating = u16tmp - step_Decelerating;
			SETFLAG(g_bF_STEP_Cal_Range);
		}
		else
		{
			;
		}
}


void STEP_HOLD_ON()
{
	IOPort_Write(PIN_HOLD, HIGH);
}


void STEP_HOLD_OFF()
{
	IOPort_Write(PIN_HOLD, LOW);
}


/*
Funtion : STEP_PWM()
Dep : Push PWM for Step Motor
Author : KhaiDH1
SYS: Run 100us
*/
void STEP_PWM()
{

	if (TSTFLAG(g_bF_STEPMOTOR_Running))
	{
		if (TSTFLAG(g_bF_StepPWM))
		{
			IOPort_Write(PIN_SPEED, HIGH);
			CLRFLAG(g_bF_StepPWM);
			if (TSTFLAG(g_bF_STEPMOTOR_Dimension))
			{
				g_ui32_StepCount++;
			}
		}
		else
		{
			IOPort_Write(PIN_SPEED, LOW);
			SETFLAG(g_bF_StepPWM);
		}
	}
	OCR2A = g_ui8_SpeedStepValue;
}

/*
Funtion : STEP_Speed()
Dep : Control Speed PWM for step motor
Author : KhaiDH1
SYS: Run 1 ms
*/
void STEP_Speed(uint8_t ui8_StepSpeed_SET)
{
	if (ui8_StepSpeed_SET > STEP_SPEED_MAX)
	{
		ui8_StepSpeed_SET = STEP_SPEED_MAX;
	}
	if (ui8_StepSpeed_SET < STEP_SPEED_MIN)
	{
		ui8_StepSpeed_SET = STEP_SPEED_MIN;
	}
	g_ui8_SpeedStepValue = 275 - ui8_StepSpeed_SET;
}