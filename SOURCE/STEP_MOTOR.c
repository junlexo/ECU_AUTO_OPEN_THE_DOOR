
#include "STEP_MOTOR.h"
/*****   STEP MOTOR       ******/

#if STEPMOTOR == ON

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
		if (g_ui32_StepDemention != 0)
		{
			if ((TSTFLAG(g_bF_BT2_Press)) || (TSTFLAG(g_bF_DOOR_OPEN)) || (TSTFLAG(g_bF_REQUEST_BY_PASSCODE_FROM_BTN1)))
			{
				if ((g_ui32_StepDemention != 0) && (g_bF_STEP_Start == 0))
				{
					SETFLAG(g_bF_STEP_Start);
					SETFLAG(g_bF_STEPMOTOR_DIR_Open);
					g_ui32_StepCount = 0;
					CLRFLAG(g_bF_STEP_Cal_Range);
					if (TSTFLAG(g_bF_REQUEST_BY_PASSCODE_FROM_BTN1))
					{
						CLRFLAG(g_bF_REQUEST_BY_PASSCODE_FROM_BTN1);
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
			;
		}
		if ((g_ui32_StepDemention ==0) || ( !TSTFLAG(g_bF_STEP_TAKE_DEMENTION)))
		{
			STEP_InitDIR();
		}
		else
		{
			;
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
				STEP_SPEED_RANGE();
				STEP_Running_Open();
				STEP_CheckTimerOpen();
				CLRFLAG(g_bF_READ_DEMENTION);
			}
			else
			{
				STEP_STOP();
				STEP_READ_DEMENTION();
				STEP_WAITING_CLOSE();
				STEPMOTOR_ResetFailsafe();
				
			}
		}
		else if (TSTFLAG(g_bF_STEPMOTOR_DIR_Close))
		{

			if ((TSTFLAG(g_bF_FIR_Status)) || (TSTFLAG(g_bF_BT1_Press)))
			{
					SETFLAG(g_bF_STEP_ReOpen);
					SETFLAG(g_bF_STEPMOTOR_DIR_Open);
					CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
					STEP_STOP();
					STEP_READ_DEMENTION();
					STEP_SPEED_RANGE();
					step_Speed = STEP_SPEED_MIN;
					CLRFLAG(g_bF_STEP_ReOpen);
					CLRFLAG(g_bF_STEP_WAITTING_CLOSE);
					STEPMOTOR_ResetFailsafe();
					
			}
			else if ((!TSTFLAG(g_bF_SW1_Status)))
			{
				STEP_SPEED_RANGE();
				STEP_Running_Close();
				STEP_CheckTimerClose();
				CLRFLAG(g_bF_READ_DEMENTION);
			}
			else if (TSTFLAG(g_bF_SW1_Status))
			{
				STEP_STOP();
				CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
				CLRFLAG(g_bF_STEP_Start);
				STEPMOTOR_ResetFailsafe();
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
		;
	}

}
void STEPMOTOR_ResetFailsafe()
{
	CLRFLAG(g_bF_STEP_WAITTING_OPEN);
	CLRFLAG(g_bF_STEP_WAITTING_CLOSE);
	g_t_ui8_S_StepMotor_WattingOpen = 0;
	g_t_ui8_S_StepMotor_WattingClose = 0;
}
void STEPMOTOR_CheckFailSafe()
{
	if (TSTFLAG(g_bF_FS_StepMotor_TimeClose))
	{
		g_SystemError = ERROR_STEPMOTOR_CLOSE_running;
		g_RangeError = NG;
		STEP_HOLD_ON();

	}
	else if (TSTFLAG(g_bF_FS_StepMotor_TimeOpen))
	{
		g_SystemError = ERROR_STEPMOTOR_OPEN_running;
		g_RangeError = NG;
		STEP_HOLD_ON();
	}
	else if (TSTFLAG(g_bF_FS_StepMotor_TimeCloseInit))
	{
		g_SystemError = ERROR_STEPMOTOR_CLOSE_init;
		g_RangeError = NG;
		STEP_HOLD_ON();
	}
	else
	{
		STEP_HOLD_OFF();
	}
}

void STEP_CheckTimerOpen()
{
	if (!(TSTFLAG(g_bF_STEP_WAITTING_OPEN)))
	{
		START_TIMER(g_t_ui8_S_StepMotor_WattingOpen, FAILSAFE_TIMEWAITTING_OPEN);
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
void STEP_CheckTimerClose()
{
	if (!(TSTFLAG(g_bF_STEP_WAITTING_CLOSE)))
	{
		START_TIMER(g_t_ui8_S_StepMotor_WattingOpen, FAILSAFE_TIMEWAITTING_CLOSE);
		SETFLAG(g_bF_STEP_WAITTING_CLOSE);
	}
	else if ((TSTFLAG(g_bF_STEP_WAITTING_CLOSE)) && (CHECK_TIMER(g_t_ui8_S_StepMotor_WattingOpen)))
	{
		SETFLAG(g_bF_FS_StepMotor_TimeClose);
		CLRFLAG(g_bF_STEP_WAITTING_CLOSE);
		STEP_STOP();
		if (TSTFLAG(g_bF_STEP_Start))
		{
			CLRFLAG(g_bF_STEP_Start);
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

void STEP_Running_Open()
{
	if (TSTFLAG(g_bF_STEPMOTOR_DIR_Open))
	{
		STEP_RUN();
		IOPort_Write(PIN_DIR, OPEN);
		STEP_Control_Speed();
	}
}

void STEP_Running_Close()
{
	if (TSTFLAG(g_bF_STEPMOTOR_DIR_Close))
	{
		STEP_RUN();
		IOPort_Write(PIN_DIR, CLOSE);
		STEP_Control_Speed();
	}
}


void STEP_WAITING_CLOSE()
{
	if (!TSTFLAG(g_bF_STEP_STANDING_CLOSE))
	{
		START_TIMER(g_t_ui8_S_StepMotor_Standing, TIMEWAITTING_STANDING);
		SETFLAG(g_bF_STEP_STANDING_CLOSE);
	}
	else if ((CHECK_TIMER(g_t_ui8_S_StepMotor_Standing)) || (TSTFLAG(g_bF_BT2_Press)))
	{
		CLRFLAG(g_bF_STEP_STANDING_CLOSE);
		SETFLAG(g_bF_STEPMOTOR_DIR_Close);
		CLRFLAG(g_bF_STEPMOTOR_DIR_Open);
		CLRFLAG(g_bF_STEP_Cal_Range);
		step_Speed = STEP_SPEED_MIN;
		g_ui32_StepCount = 0;
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
				g_ui32_StepCount = 0;
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
		CLRFLAG(g_bF_STEPMOTOR_DIR_Close);
		SETFLAG(g_bF_STEPMOTOR_DIR_Open);
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
			SETFLAG(g_bF_READ_DEMENTION);
			CLRFLAG(g_bF_STEP_Cal_Range);
			g_ui32_StepCount = 0;
		}
		else if (TSTFLAG(g_bF_STEP_ReOpen))
		{
			demention_close = g_ui32_StepCount;
			SETFLAG(g_bF_READ_DEMENTION);
			CLRFLAG(g_bF_STEP_Cal_Range);
			g_ui32_StepCount = 0;
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

	if (TSTFLAG(g_bF_STEPMOTOR_Running))
	{

		fullspeed = step_Decelerating + step_Fullspeed;

		//accelerating = step_Decelerating + step_Fullspeed + step_Accelerating;
		if (g_ui32_StepCount < step_Decelerating)
		{
			if (CHECK_TIMER(g_u8_StepSpeed_10MS))
			{
				step_Speed++;
				START_TIMER(g_u8_StepSpeed_10MS, StepCountPWM_OPEN);
			}
			if (step_Speed >= STEP_SPEED_MAX)
			{
				step_Speed = STEP_SPEED_MAX;
			}
		}
		else if (((g_ui32_StepCount > step_Decelerating)) && (g_ui32_StepCount <  fullspeed))
		{
			step_Speed = STEP_SPEED_MAX;
			
		}
		else if (g_ui32_StepCount >  fullspeed )
		{
			if (CHECK_TIMER(g_u8_StepSpeed_10MS))
			{
				step_Speed -- ;
				START_TIMER(g_u8_StepSpeed_10MS, StepCountPWM_CLOSE);
				
			}
			if (step_Speed <= STEP_SPEED_MIN)
			{
				step_Speed = STEP_SPEED_MIN; 
			}

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
	uint32_t u32tmp;
	uint32_t u32tmp1;
	uint32_t u32tmp2;
	uint32_t u32tmp3;
	if (TSTFLAG(g_bF_STEP_Cal_Range) == 0)

		if (g_ui32_StepDemention != 0)
		{
			 if (TSTFLAG(g_bF_STEP_ReOpen))
			{
				u32tmp1 = demention_close;
			}

			else
			{
				u32tmp1 = g_ui32_StepDemention;
			}
			step_Fullspeed = u32tmp1 / 2;
			u32tmp = u32tmp1 - step_Fullspeed;
			u32tmp2 = u32tmp / 2;
			step_Decelerating = u32tmp2;
			u32tmp3 = u32tmp1 - (u32tmp + step_Fullspeed);
			step_Accelerating = u32tmp3;
			SETFLAG(g_bF_STEP_Cal_Range);
		}
		else
		{
			;
		}
	else
	{
		;
	}
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
		step_loop++;
		if (step_loop > g_ui8_SpeedStepValue)
		{
			step_loop = 0;
			if (TSTFLAG(g_bF_StepPWM))
			{
				IOPort_Write(PIN_SPEED, HIGH);
				CLRFLAG(g_bF_StepPWM);
				if (TSTFLAG(g_bF_STEPMOTOR_Dimension))
				{
					g_ui32_StepCount++;
				}
				else
				{
					;
				}
			}
			else
			{
				IOPort_Write(PIN_SPEED, LOW);
				SETFLAG(g_bF_StepPWM);
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
	g_ui8_SpeedStepValue = 256 - ui8_StepSpeed_SET;
}

void STEP_HOLD_ON()
{
	IOPort_Write(PIN_HOLD,HIGH);
}
void STEP_HOLD_OFF()
{
	IOPort_Write(PIN_HOLD,LOW);
}

#endif // STEP MOTOR 