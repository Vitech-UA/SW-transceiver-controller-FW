/*
 * menu.c
 *
 *  Created on: 2 сент. 2022 г.
 *      Author: Viktor
 */
#include "menu.h"
#include "main.h"
#include "lcd.h"



void draw_menu(void) {
	uint8_t start_x = 10;
	uint8_t start_y = 10;
	uint8_t vertical_space = 15;
	LCD_SetCursor(start_x, start_y);
	LCD_Printf("Item_1\n");
	LCD_SetCursor(start_x, start_y += vertical_space);
	LCD_Printf("Item_2\n");
	LCD_SetCursor(start_x, start_y += vertical_space);
	LCD_Printf("Item_3\n");
	LCD_SetCursor(start_x, start_y += vertical_space);
	LCD_Printf("Item_4\n");

}

void select_menu_item(uint8_t item) {

	LCD_DrawRoundRect(4, 6, 120, 16, 3, GREEN);

}
