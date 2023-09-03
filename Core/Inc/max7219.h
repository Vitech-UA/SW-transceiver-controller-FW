#ifndef MAX7219_H_
#define MAX7219_H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include "math.h"
void MAX7219_init(void);
void MAX7219_write_register (uint8_t rg, uint8_t dt);
void MAX7219_clear (void);
void MAX7219_print_int(volatile uint32_t number);
void MAX7219_print_temperature(volatile uint32_t number);
void MAX7219_print_float(float number);
void MAX7219_set_brightness(uint8_t Intensity);
void MAX7219_print_char(uint8_t position, uint8_t symbol);
void MAX7219_init (void);

#endif /* MAX7219_H_ */
