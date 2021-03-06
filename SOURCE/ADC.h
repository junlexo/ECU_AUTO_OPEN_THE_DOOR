/*ADC Module*/
#ifndef _ADC_h
#define _ADC_h

#include "PREFERENT.h"

enum ADC_STATUS
{
	ADC_BTN_OFF = 0,
	ADC_BTN_ON,
	ADC_BTN_PRESS,
};

typedef struct _ADC_DATA 
{
	uint8_t ADC_index;
	uint8_t ADC_Status;
	uint16_t ADC_AnalogValue;
	uint16_t ADC_VoltageValue;
	uint16_t ADC_CountTimeMS;
	uint32_t ADC_AngleValue;
}ADC_DATA;

/**** ADC DEFINES ****/
#define CHANNELS 8

/**** LOW PASS FILTER DEFINES ****/

#define ALPHA 0.9
/**** BTN DEFINES ****/
#define BTN_PRESS_TIME_MS 2000
#define BTN_OFF_TIME_MS 30
#define BTN_ON_TIME_MS 80
#define BTN_ON_VALUE_MV 80
#define BTN_ERROR_TIME_MS 15000
#define BTN1_DISABLE_TIME_MS 30000U

/**** VOLUME DEFINES ****/
#define VOLUME_ERROR_TIME_MS 10000

extern volatile ADC_DATA adc_info[CHANNELS];

#ifdef __cplusplus
extern "C" {
#endif
	void initADCData();
	void ADC_init();
	uint16_t lowPassFilter(uint16_t interrupt_result_value, uint16_t previous_lpf_value);
	uint16_t voltageConvert(uint16_t value);
	ADC_DATA updateBTN1Status(ADC_DATA data);
	ADC_DATA updateBTN2Status(ADC_DATA data);
	ADC_DATA updateVolumeStatus(ADC_DATA data);
	ADC_DATA updateFIRStatus(ADC_DATA data);
	uint8_t getADCStatus(uint8_t index);
	uint8_t checkBTN1StatusHistory();
	uint16_t getVolumeDegree();
	uint8_t getVolumeVoltage();
	uint8_t isBTN1Disable();
	void setStatusIntoHistory(uint8_t status);
	void sendRequestToMotorStep();
	void ADC_HISTORY_DBG(uint8_t status); //DBG
	uint8_t isDisableReadingVolume();
	uint16_t getVoltageA6();
#ifdef __cplusplus
} // extern "C"
#endif

#endif