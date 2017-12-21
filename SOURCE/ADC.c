#include "ADC.h"
#include "avr\interrupt.h"
#include "FLAG.h"

volatile int isr_chnl;
volatile ADC_DATA adc_info[CHANNELS];
volatile uint16_t adc_interrupt_result[CHANNELS] = {0}; /*store adc value when interrupt*/
volatile uint16_t adc_lpf_result[CHANNELS] = {0}; //low pass filter result


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
			/*Update counter for ADC_BTN*/
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
			/*Update counter for ADC_BTN*/
			if (((uint16_t)adc_info[i].ADC_VoltageValue <= (uint16_t)BTN_ON_VALUE_MV && (uint16_t)voltageConvert(adc_lpf_result[i]) <= BTN_ON_VALUE_MV) ||
				((uint16_t)adc_info[i].ADC_VoltageValue > (uint16_t)BTN_ON_VALUE_MV && (uint16_t)voltageConvert(adc_lpf_result[i]) > (uint16_t)BTN_ON_VALUE_MV && adc_info[i].ADC_Status != (uint8_t)ADC_BTN_OFF))
				adc_info[i].ADC_CountTimeMS += 10;
			else
				adc_info[i].ADC_CountTimeMS = 0;
			/*Check ADC and update system error flag for ADC_BTN*/
			if (adc_info[i].ADC_CountTimeMS >= VOLUME_ERROR_TIME_MS)
			{
				g_bF_SystemError = ERROR_VOLUME;
			}
			else
			{
				if(i == ADC_FIR)
					adc_info[i].ADC_Status = updateFIRStatus(adc_info[i]).ADC_Status;
				else
					adc_info[i].ADC_Status = updateBTNStatus(adc_info[i]).ADC_Status;
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

ADC_DATA updateBTNStatus(ADC_DATA data)
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
	if (i < 6)
		return adc_info[i].ADC_Status;
};
