/*
 * motor_rotation.c
 *
 *  Created on: June 21, 2021
 *      Author: U.K.Min
 */

/* Includes ------------------------------------------------------------------*/
#include "motor_rotation.h"
#include "parsing.h"

/* USER CODE BEGIN 0 */
float char_to_float(char *a)
{
	float value = 0;
	int count_value = 0;
	int one = 0;
	int ten = 0;
	int hundred = 0;

	while(*(a++) != '\0'){ count_value++; }

	if(count_value == 1){
		a--;
		a--;
	    one = *a - 0x30;
	    value = one;
	}
	else if(count_value == 2){
		a--;
		a--;
		one = *(a--) - 0x30;
		ten = *a - 0x30;
		value = ten*10 + one;
	}
	else if(count_value == 3){
    	a--;
    	a--;
	  	one = *(a--) - 0x30;
	  	if((*a)=='.'){   // 소수일 경우 ex)2.4
	  		a--;
	  		ten = *a - 0x30;
	  		value = (ten*10 + one)/10.0;
	  	}
	  	else{
	  		ten = *(a--) - 0x30;
	  		hundred = *a - 0x30;
	  		value = hundred*100 + ten*10 + one;
	  	}
	}
	else if(count_value == 4){
	   	a--;
	   	a--;
	  	one = *(a--) - 0x30;
	  	if((*a)=='.'){
	  		a--;
	  		ten = *(a--) - 0x30;
	  		if(*a == '-') {   // 음수일 경우 ex)-2.3
	  			value = ((ten*10 + one)/10.0)*(-1);
	  		}
	  		else{   // 소수일 경우 ex)12.3
	  			hundred = *a - 0x30;
	  			value = (hundred*100 + ten*10 + one)/10.0;
	  		}
	  	}
	}
	else if(count_value == 5){
		a--;
		a--;
		one = *(a--) - 0x30;
		if((*a)=='.'){   // 음수일 경우 ex)-14.7
		  	a--;
		  	ten = *(a--) - 0x30;
		  	hundred = *(a--) - 0x30;
		  	if(*a == '-') {
		  		value = ((hundred*100 + ten*10 + one)/10.0)*(-1);
		  	}
		}
	}

	return value;
}

int analyze_weather(float temperature, float wind_speed, float humidity, float rain_prob, float sky)
{
	if(temperature > 18.0){
		if(humidity > 60.0)
			return HOT_HUMID;
		else if(humidity < 40.0)
			return HOT;
		else if(humidity >= 40.0 && humidity <= 60.0) {
			if(rain_prob > 50.0)
				return HOT_HUMID;
			else
				return HOT;
		}
	}
	else{
		if(wind_speed > 3.0)
			return CHILLY;
		else if(wind_speed < 1.0)
			return SUNNY;
		else if(wind_speed >= 1.0 && wind_speed <= 3.0) {
			if(sky == 3.0 || sky == 4.0)
				return CHILLY;
			else if(sky == 1.0)
				return SUNNY;
		}
	}

	return NO_RELATED_DATA;
}

char find_sector(char msg)
{
	int i;
	for(i=0; i<4; i++) {
		if(sector[i].matched_weather == msg)
			return 1;
	}
	for(int i=0; i<4; i++) {
		if(sector[i].is_matched == 0) {
			switch(i)
			{
				case Sector1:
//					TIM2 -> CCR1 = PWM_SECTOR1;
					PWM_SECTOR1();
					break;
				case Sector2:
				case Sector3:
//					TIM2 -> CCR1 = PWM_SECTOR2;
					PWM_SECTOR2();
					break;
				case Sector4:
//	  				TIM2 -> CCR1 = PWM_SECTOR4;
					PWM_SECTOR4();
					break;
	  		}
			return 0;
	  	}
	}
}

void PWM_SECTOR1(void)
{
	while(TIM2->CCR1 != PWM_350){
		TIM2->CCR1--;
		HAL_Delay(1);
	}
}

void PWM_SECTOR2(void)
{
	while(TIM2->CCR1 != PWM_750){
		if(TIM2->CCR1 > PWM_750)
			TIM2->CCR1--;
		else if(TIM2->CCR1 < PWM_750)
			TIM2->CCR1++;

		HAL_Delay(1);
	}
}

void PWM_SECTOR4(void)
{
	while(TIM2->CCR1 != PWM_1200){
		TIM2->CCR1++;
		HAL_Delay(1);
	}
}
/* USER CODE END 0 */
