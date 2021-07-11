/*
 * motor_rotation.h
 *
 *  Created on: June 21, 2021
 *      Author: U.K.Min
 */

#ifndef INC_MOTOR_ROTATION_H_
#define INC_MOTOR_ROTATION_H_

/* USER CODE BEGIN Includes */
#include "parsing.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define PWM_350 350-1
#define PWM_750 800-1
#define PWM_1200 1200-1

#define NO_RELATED_DATA -1
#define HOT 2
#define HOT_HUMID 3
#define CHILLY 1
#define SUNNY 0
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
float char_to_float(char *a);
int analyze_weather(float temperature, float wind_speed, float humidity, float rain_prob, float sky);
char find_sector(char msg);

void PWM_SECTOR1(void);
void PWM_SECTOR2(void);
void PWM_SECTOR4(void);
/* USER CODE END Prototypes */

#endif /* INC_MOTOR_ROTATION_H_ */
