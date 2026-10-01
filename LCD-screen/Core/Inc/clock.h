/*
 * clock.h
 *
 *  Created on: 30 sep. 2026
 *      Author: nasra
 */
#include "main.h"

struct clock_data {
	/* your clock variables goes here */
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};

void cd_set(struct clock_data *pcd, uint8_t hrs, uint8_t min, uint8_t sec);
void cd_tick(struct clock_data * pcd);

void uart_print_cd (UART_HandleTypeDef * huart,struct clock_data * pcd);

