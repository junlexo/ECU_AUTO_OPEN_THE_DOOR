#include "ADC.h"
#include "avr\interrupt.h"
#include "FLAG.h"
#include "Timer_count.h"

volatile int isr_chnl;
volatile ADC_DATA adc_info[CHANNELS];
volatile uint16_t adc_interrupt_result[CHANNELS] = {0}; /*store adc value when interrupt*/
volatile uint16_t adc_lpf_result[CHANNELS] = {0}; //low pass filter result
volatile uint8_t btn1_status_history[4] = {0};
volatile uint8_t btn1_check_motor_step_next_index = 0;
volatile uint8_t g_disable_btn_1 = 0;

void initADCData() 
{
	for (uint8_t i = 0; i < CHANNELS; i++)
	{
		//adc_interrupt_result[i] = 0;
		adc_info[i].ADC_index = i;
		adc_info[i].ADC_AnalogValue = 0;
		adc_info[i].ADC_VoltageValue = 0;
		adc_info[i].ADC_CountTimeMS = 0;
		adc_info[i].ADC_Status = 0;
	}
};

uint16_t voltageConvert(uint16_t value)
{
	uint16_t ret = (long)value * 5000 / 1023;
	return ret;
};

void ADC_init()
{
	/* Init data */
	initADCData();

	// Start at channel 0.
	isr_chnl = 0;
	//ADCSRA = 0;

	// Set the reference to AVCC.
	ADMUX = (1 << REFS0);

	// Enable the ADC and set the prescaler to 128.
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	// Start it up.
	sei();
	ADCSRA |= (1 << ADSC);
};

ISR(ADC_vect)
{
	// Save conversion result.
	adc_interrupt_result[isr_chnl] = ADCL | (ADCH << 8);

	// Next channel.
	if (++isr_chnl == CHANNELS)
	{
		isr_chnl = 0;
	}
	ADMUX = (ADMUX & 0xF8) | (isr_chnl & 0x07);

	// Start the next conversion.    
	ADCSRA |= (1 << ADSC);
};

void ADCUpdateEvery10ms()
{
	for (uint8_t i = 0; i < CHANNELS; i++)
	{
		
		if (adc_info[i].ADC_index == ADC_VOLUME)
		{
			/*Update counter for ADC_VOLUME*/
			if (adc_info[i].ADC_VoltageValue == voltageConvert(adc_lpf_result[i]))
				adc_info[i].ADC_CountTimeMS += 10;
			else
				adc_info[i].ADC_CountTimeMS = 0;
			/*Check ADC and update system error flag for ADC_VOLUME*/
			if (adc_info[i].ADC_CountTimeMS >= VOLUME_ERROR_TIME_MS)
			{
				g_bF_SystemError = ERROR_VOLUME;
			}
			else
			{
				
			}
		}
		else if (i == ADC_BUTTON_1 || i == ADC_BUTTON_2 || i == ADC_FIR)
		{
			/*Update counter for ADC_BTN/ADC_FIR*/
			if (((uint16_t)adc_info[i].ADC_VoltageValue <= (uint16_t)BTN_ON_VALUE_MV && (uint16_t)voltageConvert(adc_lpf_result[i]) <= BTN_ON_VALUE_MV) ||
				((uint16_t)adc_info[i].ADC_VoltageValue > (uint16_t)BTN_ON_VALUE_MV && (uint16_t)voltageConvert(adc_lpf_result[i]) > (uint16_t)BTN_ON_VALUE_MV && adc_info[i].ADC_Status != (uint8_t)ADC_BTN_OFF))
				adc_info[i].ADC_CountTimeMS += 10;
			else
				adc_info[i].ADC_CountTimeMS = 0;
			/*Check ADC and update system error flag for ADC_BTN/ADC_FIR*/
			if (adc_info[i].ADC_CountTimeMS >= BTN_ERROR_TIME_MS)
			{
				g_bF_SystemError = ERROR_BTN;
			}
			else
			{
				/*Update FIR Status*/
				if(i == ADC_FIR)
					adc_info[i].ADC_Status = updateFIRStatus(adc_info[i]).ADC_Status;
				else if (i == ADC_BUTTON_1) /*Update BTN 1 Status*/
				{
					if (g_disable_btn_1 == 1)
					{
						if (CHECK_TIMER(g_t_ui8_S_Button_ReEnable) == 1)
						{
							enableBTN1after30S();
						}
					}
					else
					{
						adc_info[i].ADC_Status = updateBTN1Status(adc_info[i]).ADC_Status;
					}
					
				}
				else /*Update BTN 2 Status*/
				{
					adc_info[i].ADC_Status = updateBTN2Status(adc_info[i]).ADC_Status;
				}
			}
		}
		/* Update ADC Value*/
		adc_lpf_result[i] = lowPassFilter(adc_interrupt_result[i], adc_lpf_result[i]);
		adc_info[i].ADC_AnalogValue = adc_lpf_result[i];
		adc_info[i].ADC_VoltageValue = voltageConvert(adc_info[i].ADC_AnalogValue);

	}
};

uint16_t lowPassFilter(uint16_t interrupt_result_value, uint16_t previous_lpf_value)
{	
	uint16_t tempValue = previous_lpf_value + (int)(ALPHA*((int)interrupt_result_value - (int)previous_lpf_value));
	return tempValue;
};

ADC_DATA updateBTN1Status(ADC_DATA data)
{
	ADC_DATA tempData = data;
	if (btn1_check_motor_step_next_index >= 4)
	{
		if (checkBTN1StatusHistory() == 0)
		{
			START_TIMER(g_t_ui8_S_Button_ReEnable,15);
			g_disable_btn_1 = 1;
			tempData.ADC_Status = ADC_BTN_OFF;
		}
		else
		{
			g_disable_btn_1 = 0;
			btn1_check_motor_step_next_index = 0;
		}
	}
	else 
	{
		if (tempData.ADC_CountTimeMS >= BTN_PRESS_TIME_MS && tempData.ADC_VoltageValue <= BTN_ON_VALUE_MV)
		{
			tempData.ADC_Status = ADC_BTN_PRESS;
			btn1_check_motor_step_next_index += 1;
			btn1_status_history[btn1_check_motor_step_next_index] = ADC_BTN_PRESS;
			START_TIMER(g_t_ui8_S_Button_WaitingInput, 15);
		}
		else if (tempData.ADC_CountTimeMS >= BTN_ON_TIME_MS && tempData.ADC_VoltageValue <= BTN_ON_VALUE_MV)
		{
			tempData.ADC_Status = ADC_BTN_ON;
			btn1_check_motor_step_next_index += 1;
			btn1_status_history[btn1_check_motor_step_next_index] = ADC_BTN_ON;
			START_TIMER(g_t_ui8_S_Button_WaitingInput, 15);
		}
		else if (tempData.ADC_CountTimeMS >= BTN_OFF_TIME_MS && tempData.ADC_VoltageValue > BTN_ON_VALUE_MV)
		{
			tempData.ADC_Status = ADC_BTN_OFF;
			if (CHECK_TIMER(g_t_ui8_S_Button_WaitingInput) == 1)
				resetBTN1StatusHistory();
		};
		
		return tempData;
	}
};

ADC_DATA updateBTN2Status(ADC_DATA data)
{
	ADC_DATA tempData = data;

	if (tempData.ADC_CountTimeMS >= BTN_PRESS_TIME_MS && tempData.ADC_VoltageValue <= BTN_ON_VALUE_MV)
	{
		tempData.ADC_Status = ADC_BTN_PRESS;
	}
	else if (tempData.ADC_CountTimeMS >= BTN_ON_TIME_MS && tempData.ADC_VoltageValue <= BTN_ON_VALUE_MV)
	{
		tempData.ADC_Status = ADC_BTN_ON;
	}
	else if (tempData.ADC_CountTimeMS >= BTN_OFF_TIME_MS && tempData.ADC_VoltageValue > BTN_ON_VALUE_MV)
	{
		tempData.ADC_Status = ADC_BTN_OFF;
	};

	return tempData;
};

ADC_DATA updateFIRStatus(ADC_DATA data)
{
	ADC_DATA tempData = data;

	if (tempData.ADC_CountTimeMS >= BTN_ON_TIME_MS && tempData.ADC_VoltageValue <= BTN_ON_VALUE_MV)
	{
		tempData.ADC_Status = ADC_BTN_ON;
	}
	else if (tempData.ADC_CountTimeMS >= BTN_OFF_TIME_MS && tempData.ADC_VoltageValue > BTN_ON_VALUE_MV)
	{
		tempData.ADC_Status = ADC_BTN_OFF;
	};

	return tempData;
};

ADC_DATA updateVolumeStatus(ADC_DATA data)
{
	ADC_DATA tempData = data;
	return tempData;
};

uint8_t getADCStatus(uint8_t index)
{
	uint8_t i = index;
	if (i < CHANNELS)
		return adc_info[i].ADC_Status;
};

uint16_t getVolumeDegree()
{
	return ((long)(adc_info[0].ADC_VoltageValue*5)/90000);
};

uint8_t getVolumeVoltage()
{
	return adc_info[0].ADC_VoltageValue;
};


uint8_t checkBTN1StatusHistory()
{
	uint8_t ret = 0;

	if (btn1_status_history[0] == ADC_BTN_ON)
		ret = 1;
	else
		return 0;

	if (btn1_status_history[1] == ADC_BTN_ON)
		ret = 1;
	else
		return 0;

	if (btn1_status_history[2] == ADC_BTN_PRESS)
		ret = 1;
	else
		return 0;

	if (btn1_status_history[3] == ADC_BTN_ON)
		ret = 1;
	else
		return 0;

	return ret;
}

void enableBTN1after30S()
{
	g_disable_btn_1 = 0;
	btn1_check_motor_step_next_index = 0;
}

void resetBTN1StatusHistory()
{
	btn1_check_motor_step_next_index = 0;
}