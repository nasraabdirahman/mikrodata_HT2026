/*
 * menu.c
 *
 *  Created on: 29 sep. 2026
 *      Author: nasra
 */
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
extern UART_HandleTypeDef huart2;
char buffer[100];
int uart_get_menu_choice() {
	char str[2] = {'\0' };
	uint16_t str_len = 1;
	HAL_UART_Receive(&huart2, (uint8_t*) str, str_len,
	HAL_MAX_DELAY);
	int ret = -1;
	sscanf(str, "%d", &ret);
	return ret;
}
void uart_print_bad_choice(int ret) {
		sprintf(buffer, "Wrong choice. Choose either 1 or 2");
		HAL_UART_Transmit(&huart2, (uint8_t*) buffer, 100, HAL_MAX_DELAY);
}


void uart_print_menu() {
	snprintf(buffer, 100,
			"Choose your destiny\r\n\n 1. Clock Mode\r\n 2. Button Mode\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, 100, HAL_MAX_DELAY);
}


