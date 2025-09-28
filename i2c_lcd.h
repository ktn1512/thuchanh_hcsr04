/*
 * i2c_lcd.h
 *
 *  Created on: Sep 13, 2025
 *      Author: khanh
 */

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "stm32f1xx_hal.h"

#define LCD_ADDR (0x27<<1)

extern I2C_HandleTypeDef hi2c1;

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_put_cur(int row, int col);
void lcd_clear(void);


#endif /* INC_I2C_LCD_H_ */
