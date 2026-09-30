/*
 * clock.c
 *
 *  Created on: 29 sep. 2026
 *      Author: nasra
 */

#include "main.h"
#include "quad_sseg.h"
#include "clock.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

enum state_clock s_clock = s_start;

extern TIM_HandleTypeDef htim1;
int hours = 0;
int minutes = 0;
int seconds = 0;
bool colon = false;
int blue_button;

void clock_mode() {
	/*** init segment ***/
	HAL_TIM_Base_Start_IT(&htim1);
	/*** main loop ***/
	while (1) {
		switch (s_clock) {
		case s_start:
			hours = 23;
			minutes = 59;
			seconds = 59;
			qs_put_digits(hours / 10, hours % 10, minutes / 10, minutes % 10,
					colon);
			s_clock = s_ms;
			break;
		case s_hm:
			if (blue_button == GPIO_PIN_RESET) {
				s_clock = s_ms;
			}
			if (hours == 24) {
				hours = 0;
				minutes = 0;
				seconds = 0;
			}
			qs_put_digits(hours / 10, hours % 10, minutes / 10, minutes % 10,
					colon);
			break;
		case s_ms:
			if (seconds == 60) {
				minutes++;
				seconds = 0;
				if (minutes == 60) {
					hours++;
					minutes = 0;
				}
			}
			if (blue_button == GPIO_PIN_SET) {
				s_clock = s_hm;
			}
			qs_put_digits(minutes / 10, minutes % 10, seconds / 10,
					seconds % 10, colon);
			break;
		default:
			break;
		}
		blue_button = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	colon = !colon;
	if(colon == false)
	{
		seconds += 1;
	}
}
