/*
 * band.h
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor
 */


#ifndef INC_BAND_H_
#define INC_BAND_H_

#include "stdint.h"

typedef struct {
	uint32_t max_freq;
	uint32_t min_freq;
	uint8_t store_address;
	uint8_t band_code;

} band_data_t;

typedef struct band {
	band_data_t band_160m;
	band_data_t band_80m;
	band_data_t band_40m;
	band_data_t band_30m;
	band_data_t band_20m;
	band_data_t band_17m;
	band_data_t band_15m;
	band_data_t band_12m;
	band_data_t band_10m;

} band_t;

void init_bands(void);

#endif /* INC_BAND_H_ */
