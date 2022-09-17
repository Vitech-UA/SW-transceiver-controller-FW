/*
 * state_mashine.c
 *
 *  Created on: 15 сент. 2022 г.
 *      Author: Viktor
 */

#include "state_mashine.h"
#include "main.h"

STATE_t state = STATE_PRINT_FREQ;
EVENT_t event = EVENT_NONE;

extern uint8_t cw_flag;
extern uint8_t ccw_flag;
volatile uint8_t current_menu_index = 2;

void reset_event(void) {
	event = EVENT_NONE;
}

void empty_function() {
// Заглушка
}

void print_freq_hanler(void) {
	static uint8_t display_freq_flag = 0;
	if (!display_freq_flag) {
		reset_event();
		ST7789_Fill_Color(BLACK);
		ST7789_WriteString(5, 5, "PRINT FREQ", Font_16x26, GREEN, BLACK);
		display_freq_flag = 1;

	}

}

void print_menu_hanler(void) {
	state = STATE_PRINT_MENU;
	static uint8_t display_menu_flag = 0;
	if (!display_menu_flag) {
		reset_event();
		draw_menu();
		display_menu_flag = 1;

	}

	if (cw_flag == 1) {
		cw_flag = 0;
		reset_event();
		select_menu_item(1);
	}
	if (ccw_flag == 1) {
		ccw_flag = 0;
		reset_event();
		select_menu_item(2);
	}
}

