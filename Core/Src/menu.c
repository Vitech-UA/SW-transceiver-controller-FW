/*
 * menu.c
 *
 *  Created on: 2 сент. 2022 г.
 *      Author: Viktor
 */
#include "menu.h"
#include "main.h"
#include "lcd.h"

char menu_itens[][20] = { "..", "Step", "Intermediate" };
extern bool enc_rotation_left_flag;
extern bool enc_rotation_right_flag;
extern bool enc_btn_pressed_flag;

void draw_menu(void) {
	uint8_t start_x = 5;
	uint8_t start_y = 45;
	uint8_t vertical_space = 15;
	LCD_SetTextColor(WHITE, BLACK);
	LCD_SetTextSize(0);
	LCD_SetCursor(start_x, start_y);

	//Друк пунктів меню  массиву
	for (uint8_t i = 0; i <= 2; i++) {
		LCD_Printf("%s", menu_itens[i]);
		LCD_SetCursor(start_x, start_y += vertical_space);
	}

}

void select_menu_item(uint8_t item) {
	if(enc_btn_pressed_flag){
		LCD_FillRect(0, 45, 128, 140, BLACK);
		draw_menu();
		LCD_DrawRoundRect(4, 44 + (item * 15), 120, 14, 3, GREEN);
	}
    enc_btn_pressed_flag = false;

}
