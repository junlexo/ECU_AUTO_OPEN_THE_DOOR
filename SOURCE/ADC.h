/*ADC Module*/
#ifndef _ADC_h
#define _ADC_h

#include "PREFERENT.h"

extern volatile ADC_DATA adc_info[CHANNELS];

#ifdef __cplusplus
extern "C" {
#endif
	void initADCData();
	void ADC_init();
	uint16_t lowPassFilter(uint16_t interrupt_result_value, uint16_t previous_lpf_value);
	uint16_t voltageConvert(uint16_t value);
	ADC_DATA updateBTNStatus(ADC_DATA data);
	ADC_DATA updateVolumeStatus(ADC_DATA data);
	ADC_DATA updateFIRStatus(ADC_DATA data);
#ifdef __cplusplus
} // extern "C"
#endif

#endif