/*
 * adc.c
 *
 *  Created on: 6 okt. 2026
 *      Author: nasra
 */
#include "adc.h"
#include <stdint.h>
#include <stdio.h>
#define ADC_BUF_SIZE 3
#define JOY_X_IX 0
#define JOY_Y_IX 1
#define R_IX 1
extern ADC_HandleTypeDef hadc1;
volatile uint16_t adc_buffer[ADC_BUF_SIZE];
static int adc_buf_ix = 0;
volatile int ready = 0;
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
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        adc_buffer[adc_buf_ix] = HAL_ADC_GetValue(hadc);

        adc_buf_ix++;

        if (adc_buf_ix >= ADC_BUF_SIZE)
        {
            adc_buf_ix = 0;
            ready = 1;
        }
    }
}

