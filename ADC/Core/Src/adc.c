/*
 * adc.c
 *
 *  Created on: 6 okt. 2026
 *      Author: nasra
 */
#include "adc.h"
#include <stdint.h>
#include <stdio.h>
extern ADC_HandleTypeDef hadc1;
uint16_t read_one_adc_value(ADC_HandleTypeDef *hadc) {
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, 100);
	uint32_t reading = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
	return (uint16_t) reading;
}

float normalize_12bit(uint16_t x) // right
{
	float value = (float)x/4095;
	return value;
}
float normalize_12bit_posneg(uint16_t x) //left
{
	float value = 0.0;
	uint16_t temp = 0;
	if(x > 2047)
	{
		temp = x - 2047;
		value = (float)temp/2048;
	}
	else
	{
		temp = 2047 - x;
		value = -(float)temp/2047;
	}
	return value;
}

