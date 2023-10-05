/*
 * band.h
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor
 */

#ifndef INC_BAND_H_
#define INC_BAND_H_

#include "stdint.h"

#define EEPRON_I2C_ADDRESS 0xA0
#define SI5351_I2C_ADDRESS 0xC0
#define MEMORY_ADDRESS 0x08

typedef void (*band_handler)(band_data_t);

typedef struct {
	uint32_t max_freq;
	uint32_t min_freq;
	uint32_t current_freq;
	uint8_t band_code;
	uint8_t store_address;
	uint8_t index;
	char* band_name;
	// handlers
	band_handler pre_handler;
	band_handler handler;
	band_handler post_handler;

/* char *name; */

} band_data_t;






void init_bands(void);
void band_process(void);
band_data_t get_current_band(void);

// band_general
void pre_handler(band_data_t current_band);
void post_handler(band_data_t current_band);
void handler(band_data_t current_band);
//
uint32_t get_current_freq_from_eeprom(void);
void save_current_freq_to_eeprom(void);
void dds_set_freq(uint32_t freq);
void test_eeprom(void);
void print_freq(uint32_t freq);
#endif /* INC_BAND_H_ */
