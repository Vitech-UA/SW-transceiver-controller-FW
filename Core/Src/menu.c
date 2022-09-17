/*
 * menu.c
 *
 *  Created on: 2 сент. 2022 г.
 *      Author: Viktor
 */
#include "menu.h"
#include "main.h"
#include "state_mashine.h"

char menu_items[MENU_ITEMS_CNT][20] = { "..", "Step", "Intermediate", "Info", };
extern uint8_t enc_btn_pressed_flag;
extern STATE_t state;
extern EVENT_t event;

void select_menu_item(uint8_t item) {
	uint8_t current_position = item;
	uint8_t previos_position = item - 1;
	const uint8_t x1_pos = 0;
	const uint8_t x2_pos = 239;
	uint8_t step_y_px = 30;
	//Затираю попереднє виділення
	ST7789_DrawRectangle(x1_pos, 0 + (previos_position * step_y_px), x2_pos,
			30 + (previos_position * step_y_px), BLACK);
	ST7789_DrawRectangle(x1_pos, 0 + (current_position * step_y_px), x2_pos,
			30 + (current_position * step_y_px), BLUE);

}
void unselect_menu_item(uint8_t item) {
	const uint8_t x1_pos = 0;
	const uint8_t x2_pos = 239;
	uint8_t step_y_px = 30;
	ST7789_DrawRectangle(x1_pos, 0 + (item * step_y_px), x2_pos,
			30 + (item * step_y_px), BLACK);
}
void draw_menu(void) {
	reset_event();
	uint8_t start_x = 10; // Відступ від верхнього краю екрану
	uint8_t start_y = 10; // Відступ від лівого краю екрану
	uint8_t vertical_space = 30;
	uint8_t menu_items_cnt = N_ELEMENTS(menu_items) - 1;
	ST7789_Fill_Color(BLACK);
	//Друк пунктів меню  массиву
	for (uint8_t i = 0; i <= menu_items_cnt; i++) {

		ST7789_WriteString(start_y,
				(start_x += vertical_space) - vertical_space, menu_items[i],
				Font_11x18, RED, BLACK);
	}

}

