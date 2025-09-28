/*
 * hcsr04.h
 *
 *  Created on: Sep 26, 2025
 *      Author: khanh
 */

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#include "stm32f1xx_hal.h"

typedef struct{
	GPIO_TypeDef *TRIG_Port;
	uint16_t TRIG_Pin;
	GPIO_TypeDef *ECHO_Port;
	uint16_t ECHO_Pin;
	TIM_HandleTypeDef *htim;
}hcsr04_t;

void hcsr04_init(hcsr04_t *sensor, GPIO_TypeDef *TRIG_Port,
				uint16_t TRIG_Pin, GPIO_TypeDef *ECHO_Port,
				uint16_t ECHO_Pin, TIM_HandleTypeDef *htim);

uint32_t hcsr04_distance(hcsr04_t *sensor);

uint16_t hcsr04_distance_avg(hcsr04_t *sensor);

#endif /* INC_HCSR04_H_ */
