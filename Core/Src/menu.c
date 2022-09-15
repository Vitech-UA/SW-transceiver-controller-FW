/*
 * menu.c
 *
 *  Created on: 2 сент. 2022 г.
 *      Author: Viktor
 */
#include "menu.h"
#include "main.h"



char menu_items[MENU_ITEMS_CNT][20] = { "..", "Step", "Intermediate", "Info",};
extern uint8_t enc_btn_pressed_flag;


void draw_menu(void) {
	uint8_t start_x = 5;
	uint8_t start_y = 45;
	uint8_t vertical_space = 15;


	//Друк пунктів меню  массиву
	for (uint8_t i = 0; i <= MENU_ITEMS_CNT-1; i++) {

	}

}

void select_menu_item(uint8_t item) {



}


