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
#include <string.h>
#include <stdbool.h>
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern struct clock_data my_clock;
extern bool cooldown;
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
	cooldown = true;
	my_clock.seconds +=1;
	cd_set(&my_clock, my_clock.hours, my_clock.minutes, my_clock.seconds);
	_time(&my_clock);
}

void uart_print_cd(UART_HandleTypeDef *huart, struct clock_data *pcd) {
	char buffer[20];
	sprintf(buffer, "%02d:%02d:%02d\r\n", pcd->hours, pcd->minutes, pcd->seconds);
	HAL_UART_Transmit(&huart2, (uint8_t*) buffer,strlen(buffer),HAL_MAX_DELAY);
}
