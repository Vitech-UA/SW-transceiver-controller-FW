/*
 * menu.c
 *
 *  Created on: 2 сент. 2022 г.
 *      Author: Viktor
 */
#include "menu.h"
#include "main.h"
#include "state_mashine.h"




/*Список пунктів головного меню.*/
char main_menu_items[][20] = { "Generator", "Component tester",
		"Frequency meter", "Filter responce", "About UCT" };
/*Список пунктів меню тестера компонентів*/
char component_tester_menu_items[][20] = { "..", "IGBT/MOSFET", "Triac",
		"Optocoupler", "Inductor", "Zenner", "Supressor" };
/*Список пунктів меню енератора*/
char generator_menu_items[][20] = { "..", "Start generation", "Stop generation",
		"Settings" };

enum menu_type {
	MAIN_MENU = 0, COMPONENT_TESTER_MENU, GENERATOR_MENU
};

uint8_t menu_items_count = 0;
extern STATE_t state;
extern EVENT_t event;



void select_menu_item(uint8_t item) {
	uint8_t current_position = item;
	const uint8_t x1_pos = 0;
	const uint8_t x2_pos = 239;
	uint8_t step_y_px = 30;
	ST7789_DrawRectangle(x1_pos, 0 + (current_position * step_y_px), x2_pos,
			30 + (current_position * step_y_px), BLUE);

}
void unselect_menu_item(uint8_t item) {
	const uint8_t x1_pos = 0;
	const uint8_t x2_pos = 239;
	uint8_t step_y_px = 30;
	//Затираю попереднє виділення
	ST7789_DrawRectangle(x1_pos, 0 + (item * step_y_px), x2_pos,
			30 + (item * step_y_px), BLACK);
}
void draw_menu_p(char **data) {

	uint8_t start_x = 10; // Відступ від верхнього краю екрану
	uint8_t start_y = 10; // Відступ від лівого краю екрану
	uint8_t vertical_space = 30;
	ST7789_Fill_Color(BLACK);

	menu_items_count = N_ELEMENTS(&data) - 1;
	//Друк пунктів меню  массиву
	for (uint8_t i = 0; i <= 4; i++) {

		ST7789_WriteString(start_y,
				(start_x += vertical_space) - vertical_space, &data[i],
				Font_11x18, RED, BLACK);

	}

}
void draw_menu(uint8_t menu_type) {

	uint8_t start_x = 10; // Відступ від верхнього краю екрану
	uint8_t start_y = 10; // Відступ від лівого краю екрану
	uint8_t vertical_space = 30;
	ST7789_Fill_Color(BLACK);
	switch (menu_type) {
	case MAIN_MENU:
		menu_items_count = N_ELEMENTS(main_menu_items) - 1;
		//Друк пунктів меню  массиву
		for (uint8_t i = 0; i <= menu_items_count; i++) {

			ST7789_WriteString(start_y,
					(start_x += vertical_space) - vertical_space,
					main_menu_items[i], Font_11x18, RED, BLACK);
		}
		break;
	case COMPONENT_TESTER_MENU:
		menu_items_count = N_ELEMENTS(component_tester_menu_items) - 1;

		//Друк пунктів меню  массиву
		for (uint8_t i = 0; i <= menu_items_count; i++) {

			ST7789_WriteString(start_y,
					(start_x += vertical_space) - vertical_space,
					component_tester_menu_items[i], Font_11x18, RED, BLACK);
		}
		break;
	case GENERATOR_MENU:
			menu_items_count = N_ELEMENTS(generator_menu_items) - 1;

			//Друк пунктів меню  массиву
			for (uint8_t i = 0; i <= menu_items_count; i++) {

				ST7789_WriteString(start_y,
						(start_x += vertical_space) - vertical_space,
						generator_menu_items[i], Font_11x18, RED, BLACK);
			}
			break;
	}

}

