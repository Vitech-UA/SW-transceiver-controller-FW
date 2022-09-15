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

void print_freq_hanler(void) {
	static int display_freq_flag = 0;
	if (!display_freq_flag) {
		state = STATE_PRINT_FREQ;
		event = EVENT_NONE;
		ST7789_Fill_Color(BLACK);
        ST7789_WriteString(5, 5, "PRINT FREQ", Font_16x26, RED, BLACK);
		display_freq_flag = 1;

	}

}

void print_menu_hanler(void) {

	static int display_menu_flag = 0;
	if (!display_menu_flag) {
		state = STATE_PRINT_MENU;
		event = EVENT_NONE;
		ST7789_Fill_Color(BLACK);
		ST7789_WriteString(5, 5, "PRINT MENU", Font_16x26, RED, BLACK);
		display_menu_flag = 1;

	}

}
void menu_up_hanler(void) {
	static int menu_up_hanler = 0;
	if (!menu_up_hanler) {

		menu_up_hanler = 1;

	}

}
void menu_down_hanler(void) {
	static int menu_down_hanler = 0;
	if (!menu_down_hanler) {

		menu_down_hanler = 1;

	}
}
