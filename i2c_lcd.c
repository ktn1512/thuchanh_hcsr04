/*
 * i2c_lcd.c
 *
 *  Created on: Sep 13, 2025
 *      Author: khanh
 */
#include "i2c_lcd.h"
#include "string.h"

extern I2C_HandleTypeDef hi2c1;

static void lcd_send(uint8_t data, uint8_t rs){
	uint8_t data_u, data_l;
	uint8_t data_t[4];
	data_u = (data & 0xF0);
	data_l = ((data<<4)&0xF0);
	if(rs==0){
		data_t[0] = data_u|0x0C;//en=1  rs=0
		data_t[1] = data_u|0x08;//en=0  rs=0
		data_t[2] = data_l|0x0C;//en=1  rs=0
		data_t[3] = data_l|0x08;//en=0  rs=0
	}
	else {
		data_t[0] = data_u|0x0D;//en=1  rs=0
		data_t[1] = data_u|0x09;//en=0  rs=0
		data_t[2] = data_l|0x0D;//en=1  rs=0
		data_t[3] = data_l|0x09;//en=0  rs=0
	}
	HAL_I2C_Master_Transmit(&hi2c1,LCD_ADDR,data_t,4,100);
}

void lcd_send_cmd(char cmd){
	lcd_send(cmd, 0);
}

void lcd_send_data(char data){
	lcd_send(data, 1);
}

void lcd_clear(void){
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_put_cur(int row, int col){
	switch(row){
	case 0:
		lcd_send_cmd(0x80 + col);
		break;
	case 1:
		lcd_send_cmd(0xC0 + col);
		break;
	}
}

void lcd_init(void){
	HAL_Delay(50);
	lcd_send_cmd(0x30);
	HAL_Delay(5);
	lcd_send_cmd(0x30);
	HAL_Delay(1);
	lcd_send_cmd(0x30);
	HAL_Delay(10);
	lcd_send_cmd(0x20);
	HAL_Delay(10);

	lcd_send_cmd(0x28);
	HAL_Delay(1);
	lcd_send_cmd(0x0C);
	HAL_Delay(1);
	lcd_clear();
	lcd_send_cmd(0x06);

}

void lcd_send_string(char *str){
	while(*str){
		lcd_send_data(*str++);
	}
	HAL_Delay(10);
}













