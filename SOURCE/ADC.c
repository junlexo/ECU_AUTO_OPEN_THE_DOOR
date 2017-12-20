#include "ADC.h"
#include "avr\interrupt.h"
#include "FLAG.h"

volatile int isr_chnl;
volatile ADC_DATA adc_info[CHANNELS];
volatile uint16_t adc_interrupt_result[CHANNELS]; /*store adc value when interrupt*/
volatile uint16_t adc_lpf_result[CHANNELS]; //low pass filter result


void initADCData() 
{
	for (uint8_t i = 0; i < CHANNELS; i++)
	{
		adc_interrupt_result[i] = 0;

		adc_info[i].ADC_index = i;
		adc_info[i].ADC_AnalogValue = 0;
		adc_info[i].ADC_VoltageValue = 0;
		adc_info[i].ADC_Status = ADC_NORMAL;
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
	//ADCSRA |= (1 << ADSC);
};

void ADCUpdateEvery10ms()
{
	uint16_t currentValue;
	for (uint8_t i = 0; i < CHANNELS; i++)
	{
		currentValue = adc_interrupt_result[i];
		/*Update count when current digital value same before value*/
		if (adc_info[i].ADC_AnalogValue == currentValue)
			adc_info[i].ADC_CountTimeMS += 10;
		else
			adc_info[i].ADC_CountTimeMS = 0;

		/*Check ADC error*/
		if (adc_info[i].ADC_CountTimeMS >= adc_info[i].ADC_ErrorTimeMS)
		{
			adc_info[i].ADC_Status = ADC_ERROR;
			flags_list.g_bF_SystemError = ERROR_BTN;
		}
			
		adc_info[i].ADC_AnalogValue = adc_interrupt_result[i];
		adc_info[i].ADC_VoltageValue = voltageConvert(adc_interrupt_result[i]);

	}
	ADCSRA |= (1 << ADSC);
}

void lowPassFilter()
{

}