/*
 * button.c
 *
 *  Created on: 5 okt. 2026
 *      Author: nasra
 */

#include "main.h"
#include "button.h"
#include <stdlib.h>
#include <stdbool.h>
void wait_for_button_press() {

	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
	{

	}
	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET)
	{

	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

}

