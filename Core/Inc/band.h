/*
 * band.h
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor
 */

#ifndef INC_BAND_H_
#define INC_BAND_H_

#include "stdint.h"

typedef void (*band_handler)(void);

typedef struct
{
	const char *band_name;
	band_handler pre_handler;
	band_handler handler;
	band_handler post_handler;
} Handler_t;




typedef struct {
	uint32_t max_freq;
	uint32_t min_freq;
	uint8_t store_address;
	uint32_t current_freq;
	uint8_t band_code;
/* char *name; */

} band_data_t;

typedef struct band {
	band_data_t band_80m;
	band_data_t band_40m;
	band_data_t band_20m;

} band_t;

void init_bands(void);
void band_process(void);
// 20m
void band_20m_pre_handler(void);
void band_20m_post_handler(void);
void band_20m_handler(void);

#endif /* INC_BAND_H_ */
