/*
 * WizFi250Handler.c
 *
 *  Created on: June 15, 2021
 *      Author: Uibeom
 */

/* Includes ------------------------------------------------------------------*/
#include "WizFi250Handler.h"

/* USER CODE BEGIN 0 */

uint8_t send_and_check_command(char* send_command, uint8_t cr_lf, uint32_t check_delay, uint32_t check_count, char* str_find1, char* str_find2, uint8_t debug_print)
{
	uint32_t i = 0;
	uint8_t is_found1=0, is_found2=0;
	uint32_t nResult = 0;
	char crlf_string[3];
	uart1_hal_rx_buffer_init();
	uart2_hal_rx_buffer_init();

	// Send Command
	uart2_hal_putchar((uint8_t*)send_command, strlen(send_command));

	// Send CR, LF
	if ( cr_lf==1 )		strcpy(crlf_string, "\r");
	else if ( cr_lf==2 )	strcpy(crlf_string, "\n");
	else if ( cr_lf==3 )	strcpy(crlf_string, "\r\n");
	if ( cr_lf==1 || cr_lf==2 || cr_lf==3 ){
		uart2_hal_putchar((uint8_t*)crlf_string, strlen(crlf_string));
	}
	if ( debug_print==1 )	printf("\r\nDBG>>> Send : %s\r\n", send_command);

	// Recv Response
	if ( str_find1==0 ) is_found1 = 1;
	if ( str_find2==0 ) is_found2 = 1;

	while(uart2_hal_getchar() != 0){

		if ( is_found1==0 ){
			if ( strstr((char*)uart2_hal_rx.buffer, str_find1) ) is_found1 = 1;
		}
		if ( is_found2==0 ){
			if ( strstr((char*)uart2_hal_rx.buffer, str_find2) ) is_found2 = 1;
		}
		if( (is_found1 == 1) && (is_found2 == 1) ) {
			HAL_Delay(100);
			if ( debug_print==1 )	printf("%s", uart2_hal_rx.buffer[0]);
			break;
		}
		if( (i++ >= check_count))
			break;

		HAL_Delay(check_delay);
	}

	// Error : Timeout or Not Found Success String
	if ( !(is_found1 && is_found2) ){
		printf("DBG>>> Error : Timeout or Not Found Success String\r\n");
		nResult = 2;
		return nResult;
	}

	return nResult;
}

/* USER CODE END 0 */
