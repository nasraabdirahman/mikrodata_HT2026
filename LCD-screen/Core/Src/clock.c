/*
 * clock.c
 *
 *  Created on: 30 sep. 2026
 *      Author: nasra
 */
#include "clock.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern struct clock_data my_clock;
void cd_set(struct clock_data *pcd, uint8_t hrs, uint8_t min, uint8_t sec) {
	//set values
	pcd->hours = hrs;
	pcd->minutes = min;
	pcd->seconds = sec;
}

void _time(struct clock_data *pcd)
{
	if (pcd->seconds == 60)
			{
				pcd->minutes++;
				pcd->seconds = 0;
				if (pcd->minutes == 60)
				{
					pcd->minutes = 0;
					pcd->hours++;
					if (pcd->hours == 24)
					{
						pcd->hours = 0;
					}
				}
			}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	_time(&my_clock);
}
void cd_tick(struct clock_data *pcd) {
		HAL_TIM_Base_Start_IT(&htim6);
		pcd->seconds++;
		cd_set(pcd, pcd->hours, pcd->minutes, pcd->seconds++);
}

void uart_print_cd(UART_HandleTypeDef *huart, struct clock_data *pcd) {
	char buffer[10];
	cd_tick(&my_clock);
	sprintf(buffer, "%d:%d:%d", pcd->hours, pcd->minutes, pcd->seconds);
	HAL_UART_Transmit(&huart2, buffer,10,HAL_MAX_DELAY);

	//HAL_UART_Transmit(&huart2, “Hello World!\r\n”, 13, 100);
}
