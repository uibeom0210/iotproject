/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
#define SECTOR1_Pin GPIO_PIN_6
#define SECTOR1_GPIO_Port GPIOE
#define SECTOR1_EXTI_IRQn EXTI9_5_IRQn
#define SECTOR2_Pin GPIO_PIN_7
#define SECTOR2_GPIO_Port GPIOE
#define SECTOR2_EXTI_IRQn EXTI9_5_IRQn
#define SECTOR3_Pin GPIO_PIN_8
#define SECTOR3_GPIO_Port GPIOE
#define SECTOR3_EXTI_IRQn EXTI9_5_IRQn
#define SECTOR4_Pin GPIO_PIN_9
#define SECTOR4_GPIO_Port GPIOE
#define SECTOR4_EXTI_IRQn EXTI9_5_IRQn
#define LED_RED_Pin GPIO_PIN_6
#define LED_RED_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_8
#define LED_GREEN_GPIO_Port GPIOC
#define LED_BLUE_Pin GPIO_PIN_9
#define LED_BLUE_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
#define CONNECTION_TO_SERVER 0
#define GET_WEATHER_DATA 1
#define DATA_PARSING 2
#define ROTATE_MOTOR 3
#define BT_WAITING 4
#define REGISTER_CLOTHES 5

#define Sector1 0
#define Sector2 1
#define Sector3 2
#define Sector4 3
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
