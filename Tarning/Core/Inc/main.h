/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define A_Pin GPIO_PIN_1
#define A_GPIO_Port GPIOC
#define B_Pin GPIO_PIN_2
#define B_GPIO_Port GPIOC
#define C_Pin GPIO_PIN_3
#define C_GPIO_Port GPIOC
#define D_Pin GPIO_PIN_4
#define D_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_13
#define LED4_GPIO_Port GPIOB
#define BOTTOM_MIDDLE_Pin GPIO_PIN_14
#define BOTTOM_MIDDLE_GPIO_Port GPIOB
#define TOP_MIDDLE_Pin GPIO_PIN_15
#define TOP_MIDDLE_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_6
#define E_GPIO_Port GPIOC
#define F_Pin GPIO_PIN_7
#define F_GPIO_Port GPIOC
#define G_Pin GPIO_PIN_8
#define G_GPIO_Port GPIOC
#define DI_middle_Pin GPIO_PIN_8
#define DI_middle_GPIO_Port GPIOA
#define TOP_LEFT_Pin GPIO_PIN_11
#define TOP_LEFT_GPIO_Port GPIOA
#define BOTTOM_RIGHT_Pin GPIO_PIN_6
#define BOTTOM_RIGHT_GPIO_Port GPIOB
#define TOP_RIGHT_Pin GPIO_PIN_7
#define TOP_RIGHT_GPIO_Port GPIOB
#define BOTTOM_LEFT_Pin GPIO_PIN_8
#define BOTTOM_LEFT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
