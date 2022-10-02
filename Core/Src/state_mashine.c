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
ENCODER_STATE_t encoder_flag = ENCODER_NONE;
extern uint8_t menu_items_count;
volatile uint8_t current_menu_index = 2;

void reset_enc_rot_flag(void) {
	encoder_flag = ENCODER_NONE;
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

	static int current_menu_item = 0;
	static int prev_menu_item = 0;

	reset_enc_rot_flag();
	draw_menu(0);
	select_menu_item(0);

	while (state == STATE_PRINT_MAIN_MENU) {
		if (encoder_flag == ENCODER_CLOCK) {
			prev_menu_item = current_menu_item;
			unselect_menu_item(prev_menu_item);
			current_menu_item++;
			if (current_menu_item > menu_items_count) {
				current_menu_item = menu_items_count;
			}
			select_menu_item(current_menu_item); // Відміняю попереднє виділення
			reset_enc_rot_flag();

		}
		if (encoder_flag == ENCODER_COUNTERCLOCK) {
			prev_menu_item = current_menu_item;
			unselect_menu_item(prev_menu_item); // Відміняю попереднє виділення
			current_menu_item--;
			if (current_menu_item < 0)
				current_menu_item = 0;

			select_menu_item(current_menu_item);
			reset_enc_rot_flag();

		}
		if ((current_menu_item == COMPONENT_TESTER)
				&& event == EVENT_BUTTON_PRESSED) {
			state = STATE_PRINT_COMPONENT_TESTER_MENU;
		}
		if ((current_menu_item == GENERATOR)
				&& encoder_flag == ENCODER_BTN_PRESSED) {
			state = STATE_PRINT_GENERATOR_MENU;
			reset_enc_rot_flag();
		}
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
		reset_enc_rot_flag();
		draw_menu(1);
		select_menu_item(0);
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
		reset_enc_rot_flag();

	}
	if (event == EVENT_ENC_COUNTERCLOCK) {
		prev_menu_item = current_menu_item;
		unselect_menu_item(prev_menu_item); // Відміняю попереднє виділення
		current_menu_item--;
		if (current_menu_item < 0)
			current_menu_item = 0;

		select_menu_item(current_menu_item);
		reset_enc_rot_flag();

	}
	if ((current_menu_item == Back) && event == EVENT_BUTTON_PRESSED) {
		state = STATE_PRINT_MAIN_MENU;
		display_comp_test_menu_flag = 0;
	}

}
void print_generator_menu_hanler(void) {

	enum main_menu_selected {
		Back = 0, START, STOP, SETTINGS,
	};

	static int current_menu_item = 0;
	static int prev_menu_item = 0;

	state = STATE_PRINT_GENERATOR_MENU;
	// Тут одноразово друкуємо меню.
	reset_enc_rot_flag();
	draw_menu(2);
	select_menu_item(0);

	while (state == STATE_PRINT_GENERATOR_MENU) {
		if (encoder_flag == ENCODER_CLOCK) {
			prev_menu_item = current_menu_item;
			unselect_menu_item(prev_menu_item);
			current_menu_item++;
			if (current_menu_item > menu_items_count) {
				current_menu_item = menu_items_count;
			}
			select_menu_item(current_menu_item); // Відміняю попереднє виділення
			reset_enc_rot_flag();

		}
		if (encoder_flag == ENCODER_COUNTERCLOCK) {
			prev_menu_item = current_menu_item;
			unselect_menu_item(prev_menu_item); // Відміняю попереднє виділення
			current_menu_item--;
			if (current_menu_item < 0)
				current_menu_item = 0;

			select_menu_item(current_menu_item);
			reset_enc_rot_flag();

		}
		if ((current_menu_item == Back)
		//.. Повернення до головного меню.
				&& encoder_flag == ENCODER_BTN_PRESSED) {
			state = STATE_PRINT_MAIN_MENU;
			reset_enc_rot_flag();
		}
		if ((current_menu_item == START)
				&& encoder_flag == ENCODER_BTN_PRESSED) {

			state = STATE_GENERATE_FREQ;
			reset_enc_rot_flag();
		}
	}
}

void generate_freq_handler(void) {

	uint32_t freq_buffer = 8000000;
	uint32_t freq_step = 100000;
	int16_t correction = 0;
	ST7789_Fill_Color(BLACK);
	print_freq(freq_buffer);

	// Зпуск генератора чаcтоти
	si5351_Init(correction);
	si5351_SetupCLK0(freq_buffer, SI5351_DRIVE_STRENGTH_8MA);
	si5351_EnableOutputs(1 << 0);

	while (state == STATE_GENERATE_FREQ) {

		if (encoder_flag == ENCODER_COUNTERCLOCK) {
			if (freq_buffer >= SI5351_MAX_FREQ) {
				freq_buffer = SI5351_MAX_FREQ;
			} else {
				freq_buffer += freq_step;
			}
			si5351_SetupCLK0(freq_buffer, SI5351_DRIVE_STRENGTH_8MA);
			print_freq(freq_buffer);
			reset_enc_rot_flag();
		}
		if (encoder_flag == ENCODER_CLOCK) {
			if (freq_buffer <= SI5351_MIN_FREQ) {
				freq_buffer = SI5351_MIN_FREQ;
			} else {
				freq_buffer -= freq_step;
			}
			si5351_SetupCLK0(freq_buffer, SI5351_DRIVE_STRENGTH_8MA);
			print_freq(freq_buffer);
			reset_enc_rot_flag();
		}

		if (encoder_flag == ENCODER_BTN_PRESSED) {

			state = STATE_PRINT_GENERATOR_MENU;
			si5351_EnableOutputs(0 << 0);
			reset_enc_rot_flag();
		}

	}
}
