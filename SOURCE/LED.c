#include "LED.h"
static uint8_t l_uint8_led_blink_off = 500;
static uint8_t l_uint8_led_blink_on = 500;
static uint8_t l_uint8_led_blink_normal = 1000;
uint8_t l_unit8_led_normal = 0;
uint8_t l_unit8_led_error = 1;
uint8_t l_unit8_led_status = 0;
static uint8_t l_uint8_led_error_time = 5000;
void LED()
{
	if (l_unit8_led_normal == 1)
	{
		if (l_uint8_led_blink_normal > 0)
		{
			IOPort_Write(D_13, HIGH);
			l_uint8_led_blink_normal -= 10;
		}
		else
		{
			l_uint8_led_blink_normal = 1000;
		}
		return;
	}
	else
	{
		IOPort_Write(D_13, LOW);
		return;
	}

	if (l_unit8_led_status == 1)
	{
		IOPort_Write(D_13, HIGH);
		return;
	}
	else
	{
		IOPort_Write(D_13, LOW);
		return;
	}
	if (l_unit8_led_error == 1)
	{
		//blink led
		if(l_uint8_led_blink_on > 0)
		{
			IOPort_Write(D_13, HIGH);		
			l_uint8_led_blink_on -= 10;
		}
		else
			if (l_uint8_led_blink_off > 0)
			{
				IOPort_Write(D_13, LOW);
				l_uint8_led_blink_off -= 10;
			}
			else
			{
				l_uint8_led_blink_off = 500;
				l_uint8_led_blink_on = 500;
			}

		if (l_uint8_led_error_time == 0)
		{
			l_unit8_led_error = 0;
			l_uint8_led_error_time = 5000;
		}
		l_uint8_led_error_time -= 10;
		return;
	}
}
void resetFlagLED()
{
	l_unit8_led_normal = 1;
	l_unit8_led_error = 0;
	l_unit8_led_status = 0;
}