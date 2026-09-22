/*
 * menu.c
 *
 *  Created on: 22 sep. 2026
 *      Author: nasra
 */


#include "menu.h"
#include <stdlib.h>
#include <stdio.h>

int uart_get_menu_choice()
{
	char str[1] = { '\0' };
	uint16_t str_len = 1;
	HAL_UART_Receive(&huart2,
	(uint8_t *) str,
	str_len,
	HAL_MAX_DELAY);
	int ret = -1;
	sscanf(str, "%d", &ret);
	return ret;
}

int uart_print_menu(int ret)
{
	char buffer[100];
	sprintf(buffer, "Choose your destiny\n 1. Clock Mode\n 2. Button Mode\n");
	sscanf("%d", &ret);

	switch(ret)
	{
		case 1:
			if(ret == 1)
			{
				return 1;
			}
			else
			{
				return uart_print_bad_choice(-1);
			}
			break;
		case 2:
			if(ret == 2)
			{
				return 2;
			}
			else {
				return uart_print_bad_choice(-1);
			}
			break;
		default:
			break;
	}
}

int uart_print_bad_choice(int error)
{
	return error;
}
