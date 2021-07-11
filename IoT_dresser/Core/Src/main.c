/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include "WizFi250Handler.h"
#include "parsing.h"
#include "motor_rotation.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SSID 		"iptime"
#define PASSWORD	"102102102"
#define SERVER_PORT	"80"
#define SERVER_IP	"27.101.215.194"
#define WEATHER_DATA "GET /1360000/VilageFcstInfoService/getVilageFcst?serviceKey=uDysCHb6Gh1sE7MHh9uKxayz%2FYJeRdird8CFIpHqgWuIPY95Z5%2Bp19ADhm54wFOpk4YIPwY2pZEJWhLh4Ws6zw%3D%3D&pageNo=1&numOfRows=10&dataType=JSON&base_date=20210621&base_time=2000&nx=60&ny=121\r\n\r\n"

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char service_key[256] = WEATHER_DATA;
uint8_t exti_flag = 0;
uint32_t is_connected=0;
uint32_t pwm_value;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	float value_T3H = 0;
	float value_Wind = 0;
	float value_REH = 0;
	float value_POP = 0;
	float value_SKY = 0;
	int i;
	char cmd[256];
	char sendView[512];
	char exists_sector = 0;
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
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  init_cmd_msg();
  init_sector_matching();

  printf("uart test\r\n");
  printf("Buffer check : %s\r\n", &uart2_hal_rx.buffer[0]);

  HAL_UART_Receive_IT(&huart1, &uart1_hal_rx.temp, 1);
  HAL_UART_Receive_IT(&huart2, &uart2_hal_rx.temp, 1);
  HAL_UART_Receive_IT(&huart3, &uart3_hal_rx.temp, 1);

  /////START/////
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
  if ( send_and_check_command("AT+WLEAVE", 1, 500,  50, "[OK]", "", 1) !=0 )	{ printf("DBG>>> Error : AT Command\r\n");}
  if ( send_and_check_command("AT+WNET=1", 1, 500,  10, "[OK]", "", 1) !=0 )	{ printf("DBG>>> Error : AT Command\r\n");}
  sprintf(cmd,"AT+WSET=0,%s",SSID);
  if ( send_and_check_command(cmd, 1, 500,  10, "[OK]", "", 1) !=0 )			{ printf("DBG>>> Error : AT Command\r\n");}
  sprintf(cmd,"AT+WSEC=0,,%s",PASSWORD);
  if ( send_and_check_command(cmd, 1, 500,  10, "[OK]", "", 1) !=0 )			{ printf("DBG>>> Error : AT Command\r\n");}
  if ( send_and_check_command("AT+WJOIN", 1, 500,  100, "[OK]", "", 1) !=0 )	{ printf("DBG>>> Error : AT Command\r\n"); Error_Handler();}
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
  HAL_Delay(500);

  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK){
    Error_Handler();
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  switch(is_connected)
	  {
	  	  case CONNECTION_TO_SERVER:
	  		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, RESET);
	  		  sprintf(cmd,"AT+SCON=O,TCN,%s,%s,,1",SERVER_IP,SERVER_PORT);
//			if ( send_and_check_command(cmd, 1, 500,  100, "[OK]", "[CONNECT", 1) !=0 )	{ printf("DBG>>> Error : AT Command\r\n"); break;}
	  		  if ( send_and_check_command(cmd, 1, 500,  100, "[OK]", "[CONNECT", 1) !=0 )	{ printf("DBG>>> Error : AT Command\r\n"); Error_Handler();}
	  		  is_connected = GET_WEATHER_DATA;
	  		  uart1_hal_putchar("Send Query\r\n", strlen("Send Query\r\n"));
	  		  uart2_hal_putchar(service_key, 247);
	  		  uart2_hal_rx_buffer_init();
	  		  printf("Received Data : ");
	  		  break;
	  	  case GET_WEATHER_DATA:
	  		  is_connected = uart2_hal_rx_monitor();
	  		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
	  		  HAL_Delay(1000);
	  		  break;
	  	  case DATA_PARSING:
	  		  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, RESET);
	  		  printf("\n\nStart Parsing\n");
	  		  Data_parse1((char*)uart2_hal_rx.rx_data);
	  		  printf("End Parsing\n\n");
	  		  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, SET);
	  		  is_connected = ROTATE_MOTOR;
	  		  break;
	  	  case ROTATE_MOTOR:
	  		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, RESET);
	  		  if(cmd_msg.cmd == Ctrl){   // if control command is sent(manual)
	  			  if(cmd_msg.msg == Sector1)
	  				  PWM_SECTOR1();
	  			  else if(cmd_msg.msg == Sector2 || cmd_msg.msg == Sector3)
	  				  PWM_SECTOR2();
	  			  else if(cmd_msg.msg == Sector4)
	  				  PWM_SECTOR4();
	  		  }
	  		  else if(cmd_msg.cmd == Select){   // if searching command is sent
	  			  for(i=0; i<4; i++){
	  				  if(sector[i].matched_weather == cmd_msg.msg){
	  					  if(i == Sector1)
	  						  PWM_SECTOR1();
	  					  else if(i == Sector2 || i == Sector3)
	  						  PWM_SECTOR2();
	  					  else if(i == Sector4)
	  						  PWM_SECTOR4();
	  					  break;
	  				  }
	  			  }
	  		  }
	  		  else if(cmd_msg.cmd == is_Invalid || cmd_msg.cmd == View){   // if no command is sent(auto)
	  			  printf("Start auto motor rotation\n");

	  			  value_T3H = char_to_float(fcst.fcstValue[T3H]);
	  			  value_Wind = (char_to_float(fcst.fcstValue[UUU]) > char_to_float(fcst.fcstValue[VVV])) ? char_to_float(fcst.fcstValue[UUU]) : char_to_float(fcst.fcstValue[VVV]);
	  			  value_Wind = (char_to_float(fcst.fcstValue[WSD]) > value_Wind) ? char_to_float(fcst.fcstValue[WSD]) : value_Wind;
	  			  value_REH = char_to_float(fcst.fcstValue[REH]);
	  			  value_POP = char_to_float(fcst.fcstValue[POP]);
	  			  value_SKY = char_to_float(fcst.fcstValue[SKY]);

	  			  printf("temperature : %f\n", value_T3H);
	  			  printf("wind speed : %f\n", value_Wind);
	  			  printf("humidity : %f\n", value_REH);
	  			  printf("precipitation probability : %f\n", value_POP);
	  			  printf("sky : %f\n", value_SKY);

	  			  for(int i = 0; i < 4; i++) {
	  				  if(sector[i].is_matched) {
	  					  if(sector[i].matched_weather == analyze_weather(value_T3H, value_Wind, value_REH, value_POP, value_SKY)){
	  						  switch(i)
	  						  {
	  						  	  case Sector1:
	  						  		  PWM_SECTOR1();
	  						  		  break;
	  						  	  case Sector2:
	  						  	  case Sector3:
	  						  		  PWM_SECTOR2();
	  						  		  break;
	  						  	  case Sector4:
	  						  		  PWM_SECTOR4();
	  						  		  break;
	  						  	  default:
	  						  		  printf("No corresponding sector found\r\n");
	  						  		  break;
	  						  }   // End switch
	  						  break;
	  					  }   // End if
	  				  }   // End if
	  			  }   // End for
	  		  }
	  		  is_connected = BT_WAITING;
	  		  HAL_Delay(100);
	  		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
	  		  break;
	  	  case BT_WAITING:
	  		  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, RESET);
	  		  HAL_Delay(200);
	  		  if(uart3_hal_rx_monitor() == 1) {   // if '@'is received
	  			  init_cmd_msg();   // initialize command and message for new one
	  			  if(get_userMessage((char*)uart3_hal_rx.rx_data) != is_Invalid) {
	  				  if(cmd_msg.cmd == Ctrl)
	  					  is_connected = ROTATE_MOTOR;   // for manual control
	  				  else if(cmd_msg.cmd == View){
	  					  i = sprintf(sendView, "City : Suwon\n");
	  					  i += sprintf(sendView + i, "Forecast time : ");
	  					  for(int j = 0; j<4; j++){
	  						  i += sprintf(sendView + i, "%c", fcst.fcstTime[T3H][j]);
	  						  if(j==1)
	  							  i += sprintf(sendView + i, ":");
	  						  else if(j==3)
	  							  i += sprintf(sendView + i, "\n\n");
	  					  }

	  					  i += sprintf(sendView + i, "--------------- Weather Information ---------------\n");
	  					  i += sprintf(sendView + i, "Temperature : %s degrees Celsius\n", fcst.fcstValue[T3H]);
	  					  i += sprintf(sendView + i, "Humidity : %s percentage\n", fcst.fcstValue[REH]);
	  					  i += sprintf(sendView + i, "Wind speed : ");

	  					  if(char_to_float(fcst.fcstValue[UUU]) > char_to_float(fcst.fcstValue[VVV]))
	  						  i += sprintf(sendView + i, "%s m/s\n", fcst.fcstValue[UUU]);
	  					  else
	  						  i += sprintf(sendView + i, "%s m/s\n", fcst.fcstValue[VVV]);

	  					  i += sprintf(sendView + i, "Precipitation : %s percentage\n", fcst.fcstValue[POP]);
	  					  i += sprintf(sendView + i, "Sky status : ");

	  					  if(char_to_float(fcst.fcstValue[SKY]) == 1.0)
	  						  i += sprintf(sendView + i, "Clear\n");
	  					  else if(char_to_float(fcst.fcstValue[SKY]) == 3.0 || char_to_float(fcst.fcstValue[SKY]) == 4.0)
	  						  i += sprintf(sendView + i, "Cloudy\n");

	  					  uart3_hal_putchar(sendView, strlen(sendView));
	  					  is_connected = ROTATE_MOTOR;
	  				  }
	  				  else if(cmd_msg.cmd == Select){
	  					  is_connected = REGISTER_CLOTHES;   // for matching or searching sector
	  				  }
	  			  }
	  			  else {
	  				  // invalid message received
	  			  }
	  			  uart3_hal_rx_buffer_init();   // initialize uart3 receiver for future communication
	  		  }
	  		  HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, SET);
	  		  HAL_Delay(200);
	  		  break;
	  	  case REGISTER_CLOTHES:
	  		  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
	  		  exists_sector = find_sector(cmd_msg.msg);   // find empty sector only when sector is not matched (should be modified)
	  		  if(exists_sector == 0){   // there is no sector related to msg(weather)
	  			  is_connected = BT_WAITING;   // when the weather is matched for the first time -> no need for motor rotation
	  		  }
	  		  else {   // there is a sector related to msg(weather)
	  			  is_connected = ROTATE_MOTOR;   // when the weather is already matched with sector -> should rotate motor for related sector
	  		  }
	  		  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
	  		  HAL_Delay(100);
	  		  break;
	  	  default:
	  		  break;
	  }  // END SWITCH
	  /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV128;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
