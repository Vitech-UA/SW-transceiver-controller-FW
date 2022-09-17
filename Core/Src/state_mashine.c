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

extern uint8_t menu_items_count;
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
   if(event == EVENT_BUTTON_PRESSED){
	   display_freq_flag = 0;
	   reset_event();
	   state = STATE_PRINT_MENU;
   }
}

void print_menu_hanler(void) {
	state = STATE_PRINT_MENU;
	static uint8_t display_menu_flag = 0;
	static int current_menu_item = 0;
	static int prev_menu_item = 0;
	if (!display_menu_flag) {
		// Тут одноразово друкуємо меню.
		reset_event();
		draw_menu();
		display_menu_flag = 1;
	}

	if (event == EVENT_ENC_CLOCK) {
		prev_menu_item = current_menu_item;
		unselect_menu_item(prev_menu_item);
		current_menu_item++;
		if (current_menu_item > menu_items_count) {
			current_menu_item = menu_items_count;
		}
		select_menu_item(current_menu_item); // Відміняю попереднє виділення
		reset_event();

	}
	if (event == EVENT_ENC_COUNTERCLOCK) {
		prev_menu_item = current_menu_item;
		unselect_menu_item(prev_menu_item); // Відміняю попереднє виділення
		current_menu_item--;
		if (current_menu_item < 0)
			current_menu_item = 0;

		select_menu_item(current_menu_item);
		reset_event();

	}

	if ((current_menu_item == 0) && event == EVENT_BUTTON_PRESSED) {
		reset_event();
		state = STATE_PRINT_FREQ;
		display_menu_flag = 0;
	}
}

