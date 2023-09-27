/*
 * band.h
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor
 */

#ifndef INC_BAND_H_
#define INC_BAND_H_

#include "stdint.h"

typedef void (*band_handler)(band_data_t);

typedef struct {
	uint32_t max_freq;
	uint32_t min_freq;
	uint8_t store_address;
	uint32_t current_freq;
	uint8_t band_code;
	char* band_name;
	// handlers
	band_handler pre_handler;
	band_handler handler;
	band_handler post_handler;

/* char *name; */

} band_data_t;






void init_bands(void);
void band_process(void);
int get_current_band(void);
// band_general
void pre_handler(band_data_t current_band);
void post_handler(band_data_t current_band);
void handler(band_data_t current_band);

#endif /* INC_BAND_H_ */
