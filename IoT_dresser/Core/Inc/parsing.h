/*
 * parsing.h
 *
 *  Created on: May 24, 2021
 *      Author: Uibeom
 */

#ifndef INC_PARSING_H_
#define INC_PARSING_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
///////////////////// weather data parsing ///////////////////////
#define MAX_LEN 1500
#define FALSE 0
#define TRUE 1

#define CATEGORY 1
#define FCSTDATE 2
#define FCSTTIME 3
#define FCSTVALUE 4
#define NX 5
#define NY 6

#define POP 0  // probability of precipitation
#define PTY 1  // precipitation form
#define R06 2  // rain 6 hours
#define REH 3  // humidity
#define S06 4  // snow 6 hours
#define SKY 5  // shy state
#define T3H 6  // temperature 3 hours
#define TMN 7  // MIN temperature, morning
#define TMX 8  // MAX temperature
#define UUU 9  // wind speed(east-west)
#define VVV 10  // wind speed(north-south)
#define WAV 11  // wave height
#define VEC 12  // wind direction
#define WSD 13  // wind speed

typedef struct forecast_information {
	char category[14][4];
	char fcstDate[14][9];
	char fcstTime[14][6];
	char fcstValue[14][5];
} fcstinfo;

extern fcstinfo fcst;
/////////////////////////////// bluetooth message parsing ///////////////////////////////
#define FindComma_1 0
#define FindComma_2 1
#define Find_at 2
#define Finished 3

#define is_Invalid 10
#define Valid 0
#define Ctrl 1
#define View 2
#define Select 3

typedef struct sector_matching {
	char is_matched;
	char matched_weather;
} sectorMatch;
typedef struct store_command_message {
	char cmd;
	char msg;
} store;

extern store cmd_msg;
extern sectorMatch sector[4];
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
//////// weather data parsing code ////////
void Data_parse1(char* temp);
void Data_parse2(char* temp);
void Data_parse3(char* temp);
void Data_parse4(char* temp, int cat, int item);
void init_Data_parse(fcstinfo* fcst);
int check_item(char* temp);
int check_category(char* temp);
//////// service key parsing code ////////
int get_baseTimeIndex(char* serviceKey);
int get_baseDateIndex(char* serviceKey);
//////// bluetooth message parsing code ////////
int get_userMessage(char* RXD);
char check_command(char *RXD);
void check_msg(char check, char* received_data);
void init_cmd_msg();
void init_sector_matching();
/* USER CODE END Prototypes */

#endif /* INC_PARSING_H_ */
