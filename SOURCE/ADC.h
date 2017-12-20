/*ADC Module*/
#ifndef _ADC_h
#define _ADC_h

#include "PREFERENT.h"

enum ADC_STATUS
{
	ADC_ERROR = 0,
	ADC_NORMAL,
};

typedef struct _ADC_DATA 
{
	uint8_t ADC_index;
	uint16_t ADC_AnalogValue;
	uint8_t ADC_Pin;
	uint16_t ADC_VoltageValue;
	uint8_t ADC_Status;
	uint16_t ADC_CountTimeMS;
	uint16_t ADC_ErrorTimeMS;
}ADC_DATA;

#define CHANNELS 6

extern volatile ADC_DATA adc_info[CHANNELS];
extern volatile uint16_t adc_interrupt_result[CHANNELS];

#ifdef __cplusplus
extern "C" {
#endif
	void initADCData();
	void ADC_init();
	void lowPassFilter();
	uint16_t voltageConvert(uint16_t value);
#ifdef __cplusplus
} // extern "C"
#endif

#endif