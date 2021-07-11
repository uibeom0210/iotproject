/*
 * WizFi250Handler.h
 *
 *  Created on: Jul 11, 2021
 *      Author: Uibeom
 */

#ifndef INC_WIZFI250HANDLER_H_
#define INC_WIZFI250HANDLER_H_

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "main.h"
#include "usart.h"

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
uint8_t send_and_check_command(char* send_command, uint8_t cr_lf, uint32_t check_delay, uint32_t check_count, char* str_find1, char* str_find2, uint8_t debug_print);

/* USER CODE END Prototypes */

#endif /* INC_WIZFI250HANDLER_H_ */
