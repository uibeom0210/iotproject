/*
 * parsing.c
 *
 *  Created on: May 24, 2021
 *      Author: Uibeom
 */

/* Includes ------------------------------------------------------------------*/
#include "parsing.h"

/* USER CODE BEGIN 0 */
fcstinfo fcst;
store cmd_msg;
sectorMatch sector[4];

void Data_parse1(char* temp)
{
	init_Data_parse(&fcst);
	int count = 0;
	char buff;
	int bracket = 0;
	char arr_data[1500] = { 0 };

	while ((buff = *(temp++)) != '\0') {
		if (buff == '{') bracket++;
		else if (buff == '[') bracket++;
		else if (buff == '}') bracket--;
		else if (buff == ']') bracket--;

		if (bracket == 6)
			arr_data[count++] = buff;
	}
	Data_parse2(arr_data);
}

void Data_parse2(char* temp)
{
	int i = 0;
	char buff;
	char arr_data[10][150] = { 0 };
	int row = -1;
	int count = 0;

	while ((buff = temp[i++]) != '\0') {
		if (buff == '{') {
			count = 0;
			row++;
		}
		arr_data[row][count++] = buff;
	}
	for (i = 0; i < 10; i++)
		Data_parse3(arr_data[i]);

//	for (i = 0; i < 14; i++) {
//		printf("category : %s  fcstDate : %s  fcstTime : %s  fcstValue : %s\n",
//			fcst.category[i], fcst.fcstDate[i], fcst.fcstTime[i], fcst.fcstValue[i]);
//	}      erased 21/06/21 07:50
}

void Data_parse3(char* temp)
{
	int i = 0;
	char buff;
	int comma = 0;
	int save_start = 0;
	char row_data[11] = { 0 };
	int count = 0;
	int item = 0;
	int category = 0;
	while ((buff = temp[i]) != '\0') {
		if (comma < 2) {
			i++;
			if (buff == ',') {
				comma++;
				continue;
			}
		}
		else {
			if (buff == '"') {
				if (save_start == 0)
					save_start = 1;
				else {
					save_start = 0;
					if (item != 0) {
						if (item == CATEGORY)
							category = check_category(row_data);
						Data_parse4(row_data, category, item);
					}
					item = check_item(row_data);
					memset(row_data, 0, sizeof(row_data));
					count = 0;
				}
				i++;
			}
			if (save_start == 1)
				row_data[count++] = temp[i];

			i++;
		}
	}
}

void Data_parse4(char* temp, int cat, int item)
{
	if (item == CATEGORY && fcst.category[cat][0] == 0)
		memcpy(fcst.category[cat], temp, strlen(temp));
	else if (item == FCSTDATE && fcst.fcstDate[cat][0] == 0)
		memcpy(fcst.fcstDate[cat], temp, strlen(temp));
	else if (item == FCSTTIME && fcst.fcstTime[cat][0] == 0)
		memcpy(fcst.fcstTime[cat], temp, strlen(temp));
	else if (item == FCSTVALUE && fcst.fcstValue[cat][0] == 0)
		memcpy(fcst.fcstValue[cat], temp, strlen(temp));
}

int check_category(char* temp)
{
	if (strcmp(temp, "POP") == 0) return POP;
	else if (strcmp(temp, "PTY") == 0) return PTY;
	else if (strcmp(temp, "R06") == 0) return R06;
	else if (strcmp(temp, "REH") == 0) return REH;
	else if (strcmp(temp, "S06") == 0) return S06;
	else if (strcmp(temp, "SKY") == 0) return SKY;
	else if (strcmp(temp, "T3H") == 0) return T3H;
	else if (strcmp(temp, "TMN") == 0) return TMN;
	else if (strcmp(temp, "TMX") == 0) return TMX;
	else if (strcmp(temp, "UUU") == 0) return UUU;
	else if (strcmp(temp, "VVV") == 0) return VVV;
	else if (strcmp(temp, "WAV") == 0) return WAV;
	else if (strcmp(temp, "VEC") == 0) return VEC;
	else if (strcmp(temp, "WSD") == 0) return WSD;
}

int check_item(char* temp)
{
	if (strcmp(temp, "category") == 0) return CATEGORY;
	else if (strcmp(temp, "fcstDate") == 0) return FCSTDATE;
	else if (strcmp(temp, "fcstTime") == 0) return FCSTTIME;
	else if (strcmp(temp, "fcstValue") == 0) return FCSTVALUE;
	else if (strcmp(temp, "nx") == 0) return NX;
	else if (strcmp(temp, "ny") == 0) return NY;
	else return 0;
}

void init_Data_parse(fcstinfo* fcst)
{
	memset((*fcst).category, 0, sizeof((*fcst).category));
	memset((*fcst).fcstDate, 0, sizeof((*fcst).fcstDate));
	memset((*fcst).fcstTime, 0, sizeof((*fcst).fcstTime));
	memset((*fcst).fcstValue, 0, sizeof((*fcst).fcstValue));
}
/////////////////////////////// service key parsing code ///////////////////////////////
int get_baseTimeIndex(char* serviceKey)
{
	char* temp = serviceKey;
	int count_index = 0;
	int found = 0;
	while(found!=6){
		if((*temp) == '&')
			found++;
		temp++;
		count_index++;
	}
	count_index -= 5;
	return count_index;
}

int get_baseDateIndex(char* serviceKey)
{
	char* temp = serviceKey;
	int count_index = 0;
	int found = 0;
	while(found!=5){
		if((*temp) == '&')
			found++;
		temp++;
		count_index++;
	}
	count_index -= 3;
	return count_index;
}
/////////////////////////////// bluetooth message parsing code ///////////////////////////////
int get_userMessage(char* RXD){
	int i=0;
	int buff_index=0;
	char received_msg[10];   // temporary storage for message(msg)
	char search = FindComma_1;   // variable for switch-case condition
	char check_cmd = check_command(RXD);   // temporary storage for command(cmd)

	while(check_cmd != is_Invalid) {   // if it's a valid command
		switch(search)
		{
			case FindComma_1:
				if(*(RXD) == ',')
					search = FindComma_2;
				break;
			case FindComma_2:
				if(*(RXD) != ',')
					received_msg[i++] = *(RXD);   // store message between two comma
				else{
					received_msg[i] = '\0';
					search = Find_at;
				}
				break;
			case Find_at:
				if(*RXD == '@')   // if '@' appears right after the second comma
					search = Finished;
				else {
					printf("Invalid command\r\n");
					return is_Invalid;
				}
				break;
		}
		if(search == Finished)
			break;

		RXD++;
		buff_index++;

		if(buff_index >= 2048){
			printf("Buffer is full\r\n");
			return is_Invalid;
		}
	}
	if(check_cmd == is_Invalid)
		return is_Invalid;

	check_msg(check_cmd, received_msg);
	return Valid;
}

char check_command(char *RXD)
{
	if(strstr((char*)RXD, "Ctrl")) return Ctrl;   // Ctrl == 1
	else if(strstr((char*)RXD, "View")) return View;   // View == 2
	else if(strstr((char*)RXD, "Select")) return Select;   // Select == 3
	else return is_Invalid;   // invalid command
}

void check_msg(char check_cmd, char* received_msg)
{
	int value = is_Invalid;
	int ten = 0;
	int one = 0;
	char* temp = received_msg;
	if(check_cmd == Ctrl) {
		ten = ((*(temp++))-0x30);
		one = ((*temp)-0x30);
		value = ten*10 + one;   // 0 -> sector1, 1 -> sector2, 2 -> sector3, 3 -> sector4
	}
	else if(check_cmd == View) {
		if(strstr((char*)received_msg, "weather")){
			//print weather data (should be modified)
		}
	}
	else if(check_cmd == Select) {
		ten = ((*(temp++))-0x30);
		one = ((*temp)-0x30);
		value = ten*10 + one;   // 0 -> SPRING/FALL, 1 -> SUMMER, 2 -> EARLY SPRING/LATE AUTUMN, 3 -> WINTER
	}

	cmd_msg.cmd = check_cmd;
	cmd_msg.msg = (char)value;
}

void init_cmd_msg(void)
{
	cmd_msg.cmd = is_Invalid;
	cmd_msg.msg = is_Invalid;
}

void init_sector_matching(void)
{
	for(int i=0; i<4; i++){
		sector[i].is_matched = 0;
		sector[i].matched_weather = is_Invalid;
	}
}
/* USER CODE END 0 */
