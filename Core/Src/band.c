/*
 * band.c
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor
 */
#include "band.h"
#include "stdint.h"



band_t sw_bands;

void init_bands(void) {

	sw_bands.band_160m.max_freq = 2000000;
	sw_bands.band_160m.min_freq = 1810000;
	sw_bands.band_160m.band_code = 0b0000;

	sw_bands.band_80m.max_freq = 3800000;
	sw_bands.band_80m.min_freq = 3500000;
	sw_bands.band_80m.band_code = 0b1000;

	sw_bands.band_40m.max_freq = 7200000;
	sw_bands.band_40m.min_freq = 7000000;
	sw_bands.band_40m.band_code = 0b0100;

	sw_bands.band_30m.max_freq = 10150000;
	sw_bands.band_30m.min_freq = 10100000;
	sw_bands.band_30m.band_code = 0b1100;

	sw_bands.band_20m.max_freq = 14350000;
	sw_bands.band_20m.min_freq = 14000000;
	sw_bands.band_20m.band_code = 0b0010;

	sw_bands.band_17m.max_freq = 18380000;
	sw_bands.band_17m.min_freq = 18006888;
	sw_bands.band_17m.band_code = 0b1010;

	sw_bands.band_15m.max_freq = 21450000;
	sw_bands.band_15m.min_freq = 21000000;
	sw_bands.band_15m.band_code = 0b0110;

	sw_bands.band_12m.max_freq = 25140000;
	sw_bands.band_12m.min_freq = 24890000;
	sw_bands.band_12m.band_code = 0b1110;

	sw_bands.band_10m.max_freq = 29700000;
	sw_bands.band_10m.min_freq = 28000000;
	sw_bands.band_10m.band_code = 0b0001;
}
