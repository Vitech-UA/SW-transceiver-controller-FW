/*
 * state_mashine.c
 *
 *  Created on: 15 сент. 2022 г.
 *      Author: Viktor
 */

#include "state_mashine.h"
#include "main.h"

STATE_t state = STATE_PRINT_MAIN_MENU;
EVENT_t event = EVENT_NONE;

extern uint8_t menu_items_count;
volatile uint8_t current_menu_index = 2;

void reset_event(void) {
	event = EVENT_NONE;
}

void empty_function() {
// Заглушка
}

void print_main_menu_hanler(void) {

	enum main_menu_selected {
		GENERATOR = 0,
		COMPONENT_TESTER,
		FREQUENCY_METER,
		FILTER_RESPONCE,
		ABOUT_UCT,
	};
	static uint8_t display_main_menu_flag = 0;
	static int current_menu_item = 0;
	static int prev_menu_item = 0;
	if (!display_main_menu_flag) {
		// Тут одноразово друкуємо меню.
		reset_event();
		draw_menu(0);
		display_main_menu_flag = 1;
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
	if ((current_menu_item == COMPONENT_TESTER)
			&& event == EVENT_BUTTON_PRESSED) {
		display_main_menu_flag = 0;
		state = STATE_PRINT_COMPONENT_TESTER_MENU;
	}
	if ((current_menu_item == GENERATOR)
				&& event == EVENT_BUTTON_PRESSED) {
			display_main_menu_flag = 0;
			state = STATE_PRINT_GENERATOR_MENU;
		}
}

void print_component_tester_menu_hanler(void) {

	enum main_menu_selected {
		Back = 0, IGBT_MOSFET, TRIAC, Otocoupler, Inductor, Zenner, Supressor,
	};

	static uint8_t display_comp_test_menu_flag = 0;
	static int current_menu_item = 0;
	static int prev_menu_item = 0;
	if (!display_comp_test_menu_flag) {
		// Тут одноразово друкуємо меню.
		reset_event();
		draw_menu(1);
		display_comp_test_menu_flag = 1;
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
	if ((current_menu_item == Back) && event == EVENT_BUTTON_PRESSED) {
		state = STATE_PRINT_MAIN_MENU;
		display_comp_test_menu_flag = 0;
	}

}
void print_generator_menu_hanler(void) {
	enum main_menu_selected {
			Back = 0, START, STOP, SETTINGS,};

		static uint8_t display_generator_menu_flag = 0;
		static int current_menu_item = 0;
		static int prev_menu_item = 0;
		if (!display_generator_menu_flag) {
			// Тут одноразово друкуємо меню.
			reset_event();
			draw_menu(2);
			display_generator_menu_flag = 1;
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
		if ((current_menu_item == Back) && event == EVENT_BUTTON_PRESSED) {
			state = STATE_PRINT_MAIN_MENU;
			display_generator_menu_flag = 0;
		}
}
