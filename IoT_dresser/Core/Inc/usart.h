/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define UART_RX_BUFFER_SIZE   1024
#define UART_TX_BUFFER_SIZE   1024

typedef struct  {
   uint8_t buffer[UART_TX_BUFFER_SIZE];
   volatile uint16_t input_p;
   volatile uint16_t output_p;
} uart_hal_tx_type;
typedef struct  {
	uint8_t buffer[2][UART_RX_BUFFER_SIZE];
	uint8_t rx_data[2][UART_RX_BUFFER_SIZE];
	uint8_t temp;
	uint8_t rxd;
	volatile uint16_t input_p;
	volatile uint16_t output_p;
} uart_hal_rx_type;

extern uart_hal_rx_type uart1_hal_rx;
extern uart_hal_tx_type uart1_hal_tx;
extern uart_hal_rx_type uart2_hal_rx;
extern uart_hal_tx_type uart2_hal_tx;
extern uart_hal_rx_type uart3_hal_rx;
extern uart_hal_tx_type uart3_hal_tx;

extern int flag;
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void uart1_hal_tx_buffer_init(void);
void uart1_hal_rx_buffer_init(void);
void uart2_hal_tx_buffer_init(void);
void uart2_hal_rx_buffer_init(void);
void uart3_hal_tx_buffer_init(void);
void uart3_hal_rx_buffer_init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
int _write(int file, unsigned char *p, int len);
uint8_t uart1_hal_getchar(void);
int uart1_hal_rx_monitor();
uint8_t uart2_hal_getchar(void);
int uart2_hal_rx_monitor();
uint8_t uart3_hal_getchar(void);
int uart3_hal_rx_monitor();
void replace_Buff_uart1(int putcase, int num);
void replace_Buff_uart2(int putcase, int num);
void replace_Buff_uart3(int putcase, int num);
void uart1_hal_putchar(uint8_t *data, int len);
void uart2_hal_putchar(uint8_t *data, int len);
void uart3_hal_putchar(uint8_t *data, int len);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
