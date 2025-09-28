#include "hcsr04.h"

// Hàm delay micro giây dùng Timer
void delay_us(uint16_t us, TIM_HandleTypeDef *htim) {
    __HAL_TIM_SET_COUNTER(htim, 0);
    while (__HAL_TIM_GET_COUNTER(htim) < us);
}

void hcsr04_init(hcsr04_t *sensor,
                 GPIO_TypeDef *TRIG_Port, uint16_t TRIG_Pin,
                 GPIO_TypeDef *ECHO_Port, uint16_t ECHO_Pin,
                 TIM_HandleTypeDef *htim) {
    sensor -> TRIG_Port = TRIG_Port;
    sensor -> TRIG_Pin  = TRIG_Pin;
    sensor -> ECHO_Port = ECHO_Port;
    sensor -> ECHO_Pin  = ECHO_Pin;
    sensor -> htim      = htim;
}

uint32_t hcsr04_distance(hcsr04_t *sensor) {
    uint32_t local_time = 0;
    uint32_t distance = 0;
    uint32_t timeout = 60000;
    // Phát xung Trigger 10us
    HAL_GPIO_WritePin(sensor->TRIG_Port, sensor -> TRIG_Pin, GPIO_PIN_RESET);
    delay_us(2, sensor -> htim);

    HAL_GPIO_WritePin(sensor->TRIG_Port, sensor -> TRIG_Pin, GPIO_PIN_SET);
    delay_us(10, sensor -> htim);
    HAL_GPIO_WritePin(sensor->TRIG_Port, sensor -> TRIG_Pin, GPIO_PIN_RESET);

    // Chờ Echo lên HIGH
    while(!HAL_GPIO_ReadPin(sensor -> ECHO_Port, sensor -> ECHO_Pin) && timeout--);
    if (timeout == 0) {
		return 0;
	}
    // Đo thời gian Echo HIGH
    __HAL_TIM_SET_COUNTER(sensor -> htim, 0);
    while(HAL_GPIO_ReadPin(sensor -> ECHO_Port, sensor -> ECHO_Pin)) {
        local_time = __HAL_TIM_GET_COUNTER(sensor -> htim);
        if(local_time > 60000) break; // timeout tránh treo
    }

    // Tính khoảng cách (cm)
    distance = (local_time * 0.034) / 2;

    return distance;
}

uint16_t hcsr04_distance_avg(hcsr04_t *sensor){
	uint32_t sum = 0;
	for (int i = 0; i < 3; i++) {
		sum += hcsr04_distance(sensor);
		HAL_Delay(1);
	}
	return sum / 5;
}
