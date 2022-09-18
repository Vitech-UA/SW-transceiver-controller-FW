/*
 * menu.h
 *
 *  Created on: 2 сент. 2022 г.
 *      Author: Viktor
 */

#ifndef MENU_H_
#define MENU_H_
#define N_ELEMENTS(X) (sizeof(X)/sizeof(*(X))) // Макрос визначення к-ті елементів у масиві

void select_menu_item(uint8_t item);
void unselect_menu_item(uint8_t item);
void draw_menu(uint8_t menu_type);
void draw_menu_p(char** data);
void init_menu(void);

#endif /* MENU_H_ */
