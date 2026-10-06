/*
 * adc.h
 *
 *  Created on: 6 okt. 2026
 *      Author: nasra
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_
#include "main.h"
#include <stdint.h>
uint16_t read_one_adc_value(ADC_HandleTypeDef *hadc1);
float normalize_12bit(uint16_t x);
float normalize_12bit_posneg(uint16_t x);
#endif /* INC_ADC_H_ */
