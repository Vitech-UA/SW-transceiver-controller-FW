/*
 * band.c
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor
 */
#include "band.h"
#include "stdint.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "tim.h"

extern UART_HandleTypeDef huart2;
extern char UART_BUFFER[40];

uint8_t btn_pressed_flag = 0;
uint8_t active_20m_band_flag = 0;
uint8_t active_40m_band_flag = 0;
uint8_t active_80m_band_flag = 0;
uint8_t idle_band_flag = 0;

band_data_t band_80m;
band_data_t band_40m;
band_data_t band_20m;
uint8_t current_band;
uint8_t prev_band;
uint32_t prevCounter = 0;

enum {
	BAND_20M = 0, BAND_40M, BAND_80M,
};

void init_bands(void) {
	band_80m.max_freq = 3800000;
	band_80m.min_freq = 3500000;
	band_80m.band_code = 0b1000;
	band_80m.handler = handler;
	band_80m.pre_handler = pre_handler;
	band_80m.handler = handler;
	band_80m.post_handler = post_handler;
	band_80m.band_name = "80m (3.65 MHz)";

	band_40m.max_freq = 7200000;
	band_40m.min_freq = 7000000;
	band_40m.band_code = 0b0100;
	band_40m.pre_handler = pre_handler;
	band_40m.handler = handler;
	band_40m.post_handler = post_handler;
	band_40m.band_name = "40m (7.1 MHz)";

	band_20m.max_freq = 14350000;
	band_20m.min_freq = 14000000;
	band_20m.band_code = 0b0010;
	band_20m.pre_handler = pre_handler;
	band_20m.handler = handler;
	band_20m.post_handler = post_handler;
	band_20m.band_name = "20m (14.175 MHz)";

}

void pre_handler(band_data_t current_band) {
	sprintf(UART_BUFFER, "pre_handler: %s\r\n", current_band.band_name);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
}

void post_handler(band_data_t current_band) {
	sprintf(UART_BUFFER, "post_handler: %s\r\n", current_band.band_name);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
}

void handler(band_data_t current_band) {
	int32_t currCounter = __HAL_TIM_GET_COUNTER(&htim1);
	currCounter = 32767 - ((currCounter - 1) & 0xFFFF);

	if (currCounter != prevCounter) {
		int32_t delta = currCounter - prevCounter;
		prevCounter = currCounter;
		if ((delta > -10) && (delta < 10)) {
			if (delta < 0) {
				sprintf(UART_BUFFER, "Rotate right. Handler: %s\r\n", current_band.band_name);
				HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER,
						strlen(UART_BUFFER), 100);
				/* Обробляємо код коли енкодер крутиться вправо */
			} else {
				sprintf(UART_BUFFER, "Rotate left. Handler: %s\r\n", current_band.band_name);
				HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER,
						strlen(UART_BUFFER), 100);
				/* Обробляємо код коли енкодер крутиться вліво */
			}
		}
	}
}

void reset_band_flags(void) {
	active_20m_band_flag = 0;
	active_40m_band_flag = 0;
	active_80m_band_flag = 0;
	idle_band_flag = 0;
}

void band_process(void) {

	current_band = get_current_band();
	prev_band = current_band;

	switch (current_band) {
	case BAND_20M: {
		band_20m.pre_handler(band_20m);
		while (prev_band == current_band) {
			band_20m.handler(band_20m);
			current_band = get_current_band();
		}
		band_20m.post_handler(band_20m);
		break;
	}
	case BAND_40M: {
		band_40m.pre_handler(band_40m);
		while (prev_band == current_band) {
			band_40m.handler(band_40m);
			current_band = get_current_band();
		}
		band_40m.post_handler(band_40m);
		break;

	}
	case BAND_80M: {
		band_80m.pre_handler(band_80m);
		while (prev_band == current_band) {
			band_80m.handler(band_80m);
			current_band = get_current_band();
		}
		band_80m.post_handler(band_80m);
		break;

	}
	}
}
int get_current_band() {
	if (active_20m_band_flag == 1) {
		return BAND_20M;
	}

	if (active_40m_band_flag == 1) {
		return BAND_40M;
	}
	if (active_80m_band_flag == 1) {
		return BAND_80M;
	}

}
