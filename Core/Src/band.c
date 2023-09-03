/*
 * band.c
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor
 */
#include "band.h"
#include "stdint.h"
#include "main.h"

band_t sw_bands;
extern UART_HandleTypeDef huart2;
extern char UART_BUFFER[40];

static const Handler_t cmd_tbl[] = { { "Band_20m", band_20m_pre_handler,
		band_20m_handler, band_20m_post_handler },

};

void init_bands(void) {
	sw_bands.band_80m.max_freq = 3800000;
	sw_bands.band_80m.min_freq = 3500000;
	sw_bands.band_80m.band_code = 0b1000;

	sw_bands.band_40m.max_freq = 7200000;
	sw_bands.band_40m.min_freq = 7000000;
	sw_bands.band_40m.band_code = 0b0100;

	sw_bands.band_20m.max_freq = 14350000;
	sw_bands.band_20m.min_freq = 14000000;
	sw_bands.band_20m.band_code = 0b0010;

}

void band_process(void) {
	cmd_tbl[0].pre_handler();
	cmd_tbl[0].handler();
	cmd_tbl[0].post_handler();
}

void band_20m_pre_handler(void) {
	sprintf(UART_BUFFER, "20m_pre_handler\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
}

void band_20m_post_handler(void) {
	sprintf(UART_BUFFER, "20m_post_handler\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
}

void band_20m_handler(void) {
	sprintf(UART_BUFFER, "20m_handler\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
}
