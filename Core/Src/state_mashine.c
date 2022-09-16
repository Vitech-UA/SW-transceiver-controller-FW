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

void reset_event(void) {
	event = EVENT_NONE;
}

void empty_function(){
// Заглушка
}

void print_freq_hanler(void) {
	static uint8_t display_freq_flag = 0;
	if (!display_freq_flag) {
		reset_event();
		ST7789_Fill_Color(BLACK);
		ST7789_WriteString(5, 5, "PRINT FREQ", Font_16x26, RED, BLACK);
		display_freq_flag = 1;

	}


}

void print_menu_hanler(void) {
    state = STATE_PRINT_MENU;
	static uint8_t display_menu_flag = 0;
	if (!display_menu_flag) {
		reset_event();
		ST7789_Fill_Color(BLACK);
		ST7789_WriteString(0, 0, "..", Font_16x26, RED, BLACK);
		ST7789_WriteString(5, 30, "Item 1", Font_16x26, RED, BLACK);
		ST7789_WriteString(5, 60, "Item 2", Font_16x26, RED, BLACK);
		ST7789_WriteString(5, 90, "Item 3", Font_16x26, RED, BLACK);
		display_menu_flag = 1;

	}


}
void menu_up_hanler(void) {
	static uint8_t menu_up_hanler = 0;
	if (!menu_up_hanler) {
		reset_event();
		ST7789_Fill_Color(BLACK);
		ST7789_WriteString(5, 5, "Menu UP", Font_16x26, RED, BLACK);
		menu_up_hanler = 1;

	}
	if (event == EVENT_ENC_COUNTERCLOCK) {
		menu_up_hanler = 0;
		reset_event();
		state = STATE_PRINT_FREQ;
	}

}
void menu_down_hanler(void) {
	static uint8_t menu_down_hanler = 0;
	if (!menu_down_hanler) {
		reset_event();
		ST7789_Fill_Color(BLACK);
		ST7789_WriteString(5, 5, "Menu DOWN", Font_16x26, RED, BLACK);
		menu_down_hanler = 1;

	}
	if (event == EVENT_ENC_CLOCK) {
		menu_down_hanler = 0;
		reset_event();
		state = STATE_PRINT_FREQ;
	}

}
