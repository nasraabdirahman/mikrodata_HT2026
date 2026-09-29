/*
 * button.c
 *
 *  Created on: 29 sep. 2026
 *      Author: nasra
 */
#include "main.h"
#include "button.h"
#include "quad_sseg.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#define BOUNCE_DELAY_MS 4
uint16_t button_debounced_count = 0;
uint16_t button_exti_count = 0;
uint32_t last_time = 0;
enum state s_button = s_release;
void button_mode() {
	/*** init segment ***/
	/*** main loop ***/
	GPIO_PinState MY_BTN_pressed;
	while (1) {
		MY_BTN_pressed = HAL_GPIO_ReadPin(MY_BTN_GPIO_Port, MY_BTN_Pin);
		qs_put_big_num(
				MY_BTN_pressed ? button_exti_count : button_debounced_count);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	uint32_t current_time = HAL_GetTick();
	switch (s_button) {
	case s_press:
		if (GPIO_Pin == MY_BTN_Pin) {
			if (current_time - last_time >= BOUNCE_DELAY_MS) {
				last_time = current_time;
				s_button = s_release;
			}
		}
		break;
	case s_release:
		if (current_time - last_time >= BOUNCE_DELAY_MS) {
			last_time = current_time;
			button_debounced_count++;
			s_button = s_press;

		}
		break;
	}

	button_exti_count++;
}
