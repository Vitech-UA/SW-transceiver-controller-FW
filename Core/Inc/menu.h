/*
 * menu.h
 *
 *  Created on: 2 сент. 2022 г.
 *      Author: Viktor
 */

#ifndef MENU_H_
#define MENU_H_
#define N_ELEMENTS(X) (sizeof(X)/sizeof(*(X))) // Макрос визначення к-ті елементів у масиві
#define LCD_BUFFER_LENGTH 15

void select_menu_item(uint8_t item);
void unselect_menu_item(uint8_t item);
void draw_menu(uint8_t menu_type);
void draw_menu_p(char **data);
void print_freq(uint32_t freq);

#endif /* MENU_H_ */
