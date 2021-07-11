/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
uart_hal_rx_type uart1_hal_rx;
uart_hal_tx_type uart1_hal_tx;
uart_hal_rx_type uart2_hal_rx;
uart_hal_tx_type uart2_hal_tx;
uart_hal_rx_type uart3_hal_rx;
uart_hal_tx_type uart3_hal_tx;

int flag = 0;
int RX1_IN_BUF_num = 0;
int RX1_OUT_BUF_num = 0;
int RX2_IN_BUF_num = 0;
int RX2_OUT_BUF_num = 0;
int RX3_IN_BUF_num = 0;
int RX3_OUT_BUF_num = 0;

void uart1_hal_tx_buffer_init(void)
{
	memset(uart1_hal_tx.buffer, 0, sizeof(uart1_hal_tx.buffer));
	uart1_hal_tx.input_p = 0;
	uart1_hal_tx.output_p = 0;
}
void uart1_hal_rx_buffer_init(void)
{
	memset(uart1_hal_rx.buffer, 0, sizeof(uart1_hal_rx.buffer));
	uart1_hal_rx.input_p = 0;
	uart1_hal_rx.output_p = 0;
	RX1_IN_BUF_num = 0;
	RX1_OUT_BUF_num = 0;
}
void uart2_hal_tx_buffer_init(void)
{
	memset(uart2_hal_tx.buffer, 0, sizeof(uart2_hal_tx.buffer));
	uart2_hal_tx.input_p = 0;
	uart2_hal_tx.output_p = 0;
}
void uart2_hal_rx_buffer_init(void)
{
	memset(uart2_hal_rx.buffer, 0, sizeof(uart2_hal_rx.buffer));
	uart2_hal_rx.input_p = 0;
	uart2_hal_rx.output_p = 0;
	RX2_IN_BUF_num = 0;
	RX2_OUT_BUF_num = 0;
}
void uart3_hal_tx_buffer_init(void)
{
	memset(uart3_hal_tx.buffer, 0, sizeof(uart3_hal_tx.buffer));
	uart3_hal_tx.input_p = 0;
	uart3_hal_tx.output_p = 0;
}
void uart3_hal_rx_buffer_init(void)
{
	memset(uart3_hal_rx.buffer, 0, sizeof(uart3_hal_rx.buffer));
	memset(uart3_hal_rx.rx_data, 0, sizeof(uart3_hal_rx.rx_data));
	uart3_hal_rx.input_p = 0;
	uart3_hal_rx.output_p = 0;
	RX3_IN_BUF_num = 0;
	RX3_OUT_BUF_num = 0;
}
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
  uart1_hal_rx_buffer_init();
  uart1_hal_tx_buffer_init();
  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  uart2_hal_rx_buffer_init();
  uart2_hal_tx_buffer_init();
  /* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */
  uart3_hal_rx_buffer_init();
  uart3_hal_tx_buffer_init();
  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
int _write(int file, unsigned char *p, int len)
{
   uart1_hal_putchar(p, len);
   setvbuf(stdout, NULL, _IONBF, 0);
   HAL_Delay(10);
   return len;
}

uint8_t uart1_hal_getchar(void)
{
	if(uart1_hal_rx.input_p == uart1_hal_rx.output_p){
		return 0;
	}
	uart1_hal_rx.rxd = uart1_hal_rx.buffer[RX1_OUT_BUF_num][uart1_hal_rx.output_p++];
	if(uart1_hal_rx.output_p >= UART_RX_BUFFER_SIZE){
		replace_Buff_uart1(1, RX1_OUT_BUF_num);
		uart1_hal_rx.output_p = 0;
	}
	return 1;
}

int uart1_hal_rx_monitor()
{
	int i = 0;
	while(uart1_hal_getchar() != 0){
		if(uart1_hal_rx.rxd == '\0'){
			HAL_Delay(100);
			for(i=0; i<RX1_OUT_BUF_num+1;i++){
				memcpy(uart1_hal_rx.rx_data[i], uart1_hal_rx.buffer[i], sizeof(uart1_hal_rx.buffer[i]));
			}
			printf("***RX1_OUT_BUF_num : %d\n", RX1_OUT_BUF_num);
			printf("%s\n", uart1_hal_rx.rx_data[0]);
		}
	}
	return 1;
}

uint8_t uart2_hal_getchar(void)
{
	if(uart2_hal_rx.input_p == uart2_hal_rx.output_p){
		return 0;
	}
	uart2_hal_rx.rxd = uart2_hal_rx.buffer[RX2_OUT_BUF_num][uart2_hal_rx.output_p++];
	if(uart2_hal_rx.output_p >= UART_RX_BUFFER_SIZE){
		replace_Buff_uart2(1, RX2_OUT_BUF_num);
		uart2_hal_rx.output_p = 0;
	}
	return 1;
}

int uart2_hal_rx_monitor(void)
{
	while(uart2_hal_getchar() != 0){
	    if(strstr((char*)uart2_hal_rx.buffer, "}}}")) {
	    	HAL_Delay(100);
			memcpy(uart2_hal_rx.rx_data, uart2_hal_rx.buffer, sizeof(uart2_hal_rx.buffer));
//	    	printf("%s\n", uart2_hal_rx.rx_data[0]);     erased 21/06/21 14:21
//		    printf(">> RECEIVED OK\r\n\n");     erased 21/06/21 14:21
		    return 2;
	    }
	}
	return 1;
}

uint8_t uart3_hal_getchar(void)
{
	if(uart3_hal_rx.input_p == uart3_hal_rx.output_p){
		return 0;
	}
	uart3_hal_rx.rxd = uart3_hal_rx.buffer[RX3_OUT_BUF_num][uart3_hal_rx.output_p++];
	if(uart3_hal_rx.output_p >= UART_RX_BUFFER_SIZE){
		replace_Buff_uart3(1, RX3_OUT_BUF_num);
		uart3_hal_rx.output_p = 0;
	}
	return 1;
}

int uart3_hal_rx_monitor(void)
{
	int i;
	while(uart3_hal_getchar() != 0){
	    if(uart3_hal_rx.rxd == '@') {
	    	for(i=0; i<RX2_OUT_BUF_num+1;i++){
				memcpy(uart3_hal_rx.rx_data, uart3_hal_rx.buffer, sizeof(uart3_hal_rx.buffer));
			}
//	    	printf("Received Data From Bluetooth : %s\r\n", uart3_hal_rx.rx_data[0]);   erased 21/06/21 07:50
		    return 1;
	    }
	}
	return 0;
}

//int uart3_hal_rx_monitor(void)
//{
//	int j = 0;
//	while(uart3_hal_getchar() != 0)
//	{
//	    if(strstr((char*)uart3_hal_rx.buffer, "@")) {
//	    	HAL_Delay(100);
//	    	memcpy(uart3_hal_rx.rx_data, uart3_hal_rx.buffer, sizeof(uart3_hal_rx.buffer));
//	    	for(int i=0 ; i<=RX3_OUT_BUF_num; i++){
//	    		do{
//   					printf("%c", uart3_hal_rx.rx_data[i][j]);
//   					if(j == UART_RX_BUFFER_SIZE - 1){
//   						j=0;
//   						break;
//   					}
//   					j++;
//   				}while(uart3_hal_rx.rx_data[i][j] != '@');
//	    	}
//	    	printf("\r\n");
//	    	uart3_hal_rx_buffer_init();
//		    return 4;
//	    }
//	}
//	return 3;
//}

void replace_Buff_uart1(int putcase, int num)
{
	if(putcase == 0){
		switch(num)
		{
			case 0:
				RX1_IN_BUF_num++;
				break;
			case 1:
				printf("\r\nUart1_IN_OVERFLOW\r\n");
				RX1_IN_BUF_num = 0;
				break;
			default:
				break;
		}
	}
	else if(putcase == 1){
		switch(num)
		{
			case 0:
				RX1_OUT_BUF_num++;
				break;
			case 1:
				printf("\r\nUart1_OUT_OVERFLOW\r\n");
				RX1_OUT_BUF_num = 0;
				break;
			default:
				break;
		}
	}
	return;
}

void replace_Buff_uart2(int putcase, int num)
{
	if(putcase == 0){
		switch(num)
		{
			case 0:
				RX2_IN_BUF_num++;
				break;
			case 1:
				printf("\r\nUart2_IN_OVERFLOW\r\n");
				RX2_IN_BUF_num = 0;
				break;
			default:
				break;
		}
	}
	else if(putcase == 1){
		switch(num)
		{
			case 0:
				RX2_OUT_BUF_num++;
				break;
			case 1:
				printf("\r\nUart2_OUT_OVERFLOW\r\n");
				RX2_OUT_BUF_num = 0;
				break;
			default:
				break;
		}
	}
	return;
}

void replace_Buff_uart3(int putcase, int num)
{
	if(putcase == 0){
		switch(num)
		{
			case 0:
				RX3_IN_BUF_num++;
				break;
			case 1:
				printf("\r\nUart3_IN_OVERFLOW\r\n");
				RX3_IN_BUF_num = 0;
				break;
			default:
				break;
		}
	}
	else if(putcase == 1){
		switch(num)
		{
			case 0:
				RX3_OUT_BUF_num++;
				break;
			case 1:
				printf("\r\nUart3_OUT_OVERFLOW\r\n");
				RX3_OUT_BUF_num = 0;
				break;
			default:
				break;
		}
	}
	return;
}

void uart1_hal_putchar(uint8_t *data, int len)
{
	uint16_t size = len;
	uint32_t reg = READ_REG(huart1.Instance->CR1);

	__HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
	__HAL_UART_DISABLE_IT(&huart1, UART_IT_TC);
	if((uart1_hal_tx.input_p + len) >= UART_TX_BUFFER_SIZE){
		size = UART_TX_BUFFER_SIZE - uart1_hal_tx.input_p;
		memcpy(&uart1_hal_tx.buffer[uart1_hal_tx.input_p], data, size);
		memcpy(&uart1_hal_tx.buffer[0], &data[size], len - size);
		uart1_hal_tx.input_p = len - size;
	}
	else{
		memcpy(&uart1_hal_tx.buffer[uart1_hal_tx.input_p], data, size);
		uart1_hal_tx.input_p += size;
	}
	WRITE_REG(huart1.Instance->CR1, reg);
	HAL_UART_Transmit_IT(&huart1, &uart1_hal_tx.buffer[uart1_hal_tx.output_p], size);
}

void uart2_hal_putchar(uint8_t *data, int len)
{
	uint16_t size = len;
	uint32_t reg = READ_REG(huart2.Instance->CR1);

	__HAL_UART_DISABLE_IT(&huart2, UART_IT_TXE);
	__HAL_UART_DISABLE_IT(&huart2, UART_IT_TC);
	if((uart2_hal_tx.input_p + len) >= UART_TX_BUFFER_SIZE){
		size = UART_TX_BUFFER_SIZE - uart2_hal_tx.input_p;
		memcpy(&uart2_hal_tx.buffer[uart2_hal_tx.input_p], data, size);
		memcpy(&uart2_hal_tx.buffer[0], &data[size], len - size);
		uart2_hal_tx.input_p = len - size;
	}
	else{
		memcpy(&uart2_hal_tx.buffer[uart2_hal_tx.input_p], data, size);
		uart2_hal_tx.input_p += size;
	}
	WRITE_REG(huart2.Instance->CR1, reg);
	HAL_UART_Transmit_IT(&huart2, &uart2_hal_tx.buffer[uart2_hal_tx.output_p], size);
}

void uart3_hal_putchar(uint8_t *data, int len)
{
	uint16_t size = len;
	uint32_t reg = READ_REG(huart3.Instance->CR1);

	__HAL_UART_DISABLE_IT(&huart3, UART_IT_TXE);
	__HAL_UART_DISABLE_IT(&huart3, UART_IT_TC);
	if((uart3_hal_tx.input_p + len) >= UART_TX_BUFFER_SIZE){
		size = UART_TX_BUFFER_SIZE - uart3_hal_tx.input_p;
		memcpy(&uart3_hal_tx.buffer[uart3_hal_tx.input_p], data, size);
		memcpy(&uart3_hal_tx.buffer[0], &data[size], len - size);
		uart3_hal_tx.input_p = len - size;
	}
	else{
		memcpy(&uart3_hal_tx.buffer[uart3_hal_tx.input_p], data, size);
		uart3_hal_tx.input_p += size;
	}
	WRITE_REG(huart3.Instance->CR1, reg);
	HAL_UART_Transmit_IT(&huart3, &uart3_hal_tx.buffer[uart3_hal_tx.output_p], size);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	uint16_t size;

	if(huart->Instance == USART1){
		uart1_hal_tx.output_p += huart->TxXferSize;
		if(uart1_hal_tx.output_p >= UART_TX_BUFFER_SIZE){
			uart1_hal_tx.output_p -= UART_TX_BUFFER_SIZE;
		}
		if(uart1_hal_tx.input_p != uart1_hal_tx.output_p){
			if(uart1_hal_tx.input_p > uart1_hal_tx.output_p){
				size = uart1_hal_tx.input_p - uart1_hal_tx.output_p;
			}
			else{
				size = UART_TX_BUFFER_SIZE - uart1_hal_tx.output_p;
			}
			HAL_UART_Transmit_IT(huart, &uart1_hal_tx.buffer[uart1_hal_tx.output_p], size);
		}
	}
	if(huart->Instance == USART2){
		uart2_hal_tx.output_p += huart->TxXferSize;
		if(uart2_hal_tx.output_p >= UART_TX_BUFFER_SIZE){
			uart2_hal_tx.output_p -= UART_TX_BUFFER_SIZE;
		}
		if(uart2_hal_tx.input_p != uart2_hal_tx.output_p){
			if(uart2_hal_tx.input_p > uart2_hal_tx.output_p){
				size = uart2_hal_tx.input_p - uart2_hal_tx.output_p;
			}
			else{
				size = UART_TX_BUFFER_SIZE - uart2_hal_tx.output_p;
			}
			HAL_UART_Transmit_IT(huart, &uart2_hal_tx.buffer[uart2_hal_tx.output_p], size);
		}
	}
	if(huart->Instance == USART3){
		uart3_hal_tx.output_p += huart->TxXferSize;
		if(uart3_hal_tx.output_p >= UART_TX_BUFFER_SIZE){
			uart3_hal_tx.output_p -= UART_TX_BUFFER_SIZE;
		}
		if(uart3_hal_tx.input_p != uart3_hal_tx.output_p){
			if(uart3_hal_tx.input_p > uart3_hal_tx.output_p){
				size = uart3_hal_tx.input_p - uart3_hal_tx.output_p;
			}
			else{
				size = UART_TX_BUFFER_SIZE - uart3_hal_tx.output_p;
			}
			HAL_UART_Transmit_IT(huart, &uart3_hal_tx.buffer[uart3_hal_tx.output_p], size);
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1){
		uart1_hal_rx.buffer[RX1_IN_BUF_num][uart1_hal_rx.input_p++] = uart1_hal_rx.temp;
		if(uart1_hal_rx.input_p >= UART_RX_BUFFER_SIZE){
			replace_Buff_uart1(0, RX1_IN_BUF_num);
			uart1_hal_rx.input_p = 0;
		}
		HAL_UART_Receive_IT(&huart1, &uart1_hal_rx.temp, 1);
	}
	if(huart->Instance == USART2){
		uart2_hal_rx.buffer[RX2_IN_BUF_num][uart2_hal_rx.input_p++] = uart2_hal_rx.temp;
		if(uart2_hal_rx.input_p >= UART_RX_BUFFER_SIZE){
			replace_Buff_uart2(0, RX2_IN_BUF_num);
			uart2_hal_rx.input_p = 0;
		}
		HAL_UART_Receive_IT(&huart2, &uart2_hal_rx.temp, 1);
	}
	if(huart->Instance == USART3){
		uart3_hal_rx.buffer[RX3_IN_BUF_num][uart3_hal_rx.input_p++] = uart3_hal_rx.temp;
		if(uart3_hal_rx.input_p >= UART_RX_BUFFER_SIZE){
			replace_Buff_uart3(0, RX3_IN_BUF_num);
			uart3_hal_rx.input_p = 0;
		}
		HAL_UART_Receive_IT(&huart3, &uart3_hal_rx.temp, 1);
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
