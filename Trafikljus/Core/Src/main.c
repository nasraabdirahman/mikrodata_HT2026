/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "enum.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//car = RED YELLOW GREEN
//people = RED GREEN
//output[0] = s_init
//output[1] = s_car_stop = 10001
// output[2] = s_car_standing_by = 10110
//output[3] = s_people_walk = 10001
//output[4] = s_car_about_to_stop = 10010
//output[5] = s_car_go = 01001
//output[6] = s_people_stop = 01100
//output[7] = s_people_pushed_button = 01011
void set_traffic_lights(enum state s) {
	const int8_t output[8] = { 0b11111, 0b10001, 0b01001, 0b01011, 0b01100,
			0b01100, 0b01010, 0b01001 };
	switch (s) {
	case s_init:
		GPIOC->ODR = output[s_init];
		break;
	case s_people_walk:
		GPIOC->ODR = output[s_people_walk];
		break;
	case s_car_standing_by:
		GPIOC->ODR = output[s_car_standing_by];
		break;
	case s_people_stop:
		GPIOC->ODR = output[s_people_stop];
		break;
	case s_car_go:
		GPIOC->ODR = output[s_car_go];
		break;
	case s_pushed_wait:
		GPIOC->ODR = output[s_pushed_wait];
		break;
	case s_car_is_stopping:
		GPIOC->ODR = output[s_car_is_stopping];
		break;
	case s_car_stop:
		GPIOC->ODR = output[s_car_stop];
		break;
	default:
		break;
	}
}
int is_button_pressed() {
	return GPIOC->IDR & (1 << 13);
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */
	enum state st = s_init;
	enum event ev = ev_none;
	uint32_t ticks_left_in_state = 0;
	uint32_t curr_tick, last_tick = 0;
	bool temp = false;
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */
	int last_press = is_button_pressed();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		/* USER CODE BEGIN 3 */
		int curr_press = is_button_pressed();
		bool button_ev = curr_press && !last_press;
		last_press = curr_press;
		curr_tick = HAL_GetTick();
		uint32_t delta = curr_tick - last_tick;
		last_tick = curr_tick;
		ev = ev_none;
		if (ticks_left_in_state > 0) {
			if (delta >= ticks_left_in_state) {
				ticks_left_in_state = 0;
				ev = ev_state_timeout;
			} else {
				ticks_left_in_state -= delta;
			}
			last_tick = curr_tick;
		}
		if (button_ev) {
			ev = ev_button_push;
		}
		switch (st) {
		case s_init:
			if (ev == ev_button_push) {
				st = s_people_walk;
			}
			break;
		case s_people_walk:
			if (temp == false) {
				ticks_left_in_state = 5000;
				temp = true;
			}
			if (ev == ev_state_timeout) {
				st = s_car_standing_by;
				temp = false;
			}
			break;
		case s_car_standing_by:
			if (temp == false) {
				ticks_left_in_state = 5000;
				temp = true;
			}
			if (ev == ev_state_timeout) {
				st = s_people_stop;
				temp = false;
			}
			break;
		case s_people_stop:
			if (temp == false) {
				ticks_left_in_state = 5000;
				temp = true;
			}
			if (ev == ev_state_timeout) {
				st = s_car_go;
				temp = false;
			}
			break;
		case s_car_go:
			if (ev == ev_button_push) {
				st = s_pushed_wait;
			}
			break;
		case s_pushed_wait:
			if (temp == false) {
				ticks_left_in_state = 5000;
				temp = true;
			}
			if (ev == ev_state_timeout) {
				st = s_car_is_stopping;
				temp = false;
			}
			break;
		case s_car_is_stopping:
			if (temp == false) {
				ticks_left_in_state = 5000;
				temp = true;
			}
			if (ev == ev_state_timeout) {
				st = s_car_stop;
				temp = false;
			}
			break;
		case s_car_stop:
			if (temp == false) {
				ticks_left_in_state = 5000;
				temp = true;
			}
			if (ev == ev_state_timeout) {
				st = s_people_walk;
				temp = false;
			}
			break;
		default:
			break;
		}
		set_traffic_lights(st);
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1)
			!= HAL_OK) {
		Error_Handler();
	}

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 10;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC,
			DC_RED_Pin | DC_YELLOW_Pin | DC_GREEN_Pin | DP_RED_Pin
					| DP_GREEN_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : DC_RED_Pin DC_YELLOW_Pin DC_GREEN_Pin DP_RED_Pin
	 DP_GREEN_Pin */
	GPIO_InitStruct.Pin = DC_RED_Pin | DC_YELLOW_Pin | DC_GREEN_Pin | DP_RED_Pin
			| DP_GREEN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : LD4_Pin */
	GPIO_InitStruct.Pin = LD4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD4_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
