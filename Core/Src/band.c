/*
 * band.c
 *
 *  Created on: Feb 6, 2023
 *      Author: Viktor Starovit
 */
#include "band.h"
#include "stdint.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "tim.h"
#include "si5351.h"
#include "max7219.h"
#include "EEPROM.h"
extern UART_HandleTypeDef huart2;
extern char UART_BUFFER[40];

uint8_t btn_pressed_flag = 0;
uint8_t active_20m_band_flag = 0;
uint8_t active_40m_band_flag = 0;
uint8_t active_80m_band_flag = 0;

extern I2C_HandleTypeDef hi2c1;

band_data_t band_80m;
band_data_t band_40m;
band_data_t band_20m;
band_data_t current_band;
band_data_t prev_band;
uint32_t prevCounter = 0;
uint32_t freq = 0;
uint32_t freq_change_step = 1000;

enum {
	BAND_20M = 0, BAND_40M, BAND_80M,
};

void init_bands(void) {
	band_80m.max_freq = 3800000;
	band_80m.min_freq = 3500000;
	band_80m.band_code = 0b1000;
	band_80m.pre_handler = pre_handler;
	band_80m.handler = handler;
	band_80m.post_handler = post_handler;
	band_80m.band_name = "80m (3.65 MHz)";
	band_80m.current_freq = 3650000;
	band_80m.index = BAND_80M;

	band_40m.max_freq = 7200000;
	band_40m.min_freq = 7000000;
	band_40m.band_code = 0b0100;
	band_40m.pre_handler = pre_handler;
	band_40m.handler = handler;
	band_40m.post_handler = post_handler;
	band_40m.band_name = "40m (7.1 MHz)";
	band_40m.current_freq = 7100000;
	band_40m.index = BAND_40M;

	band_20m.max_freq = 14350000;
	band_20m.min_freq = 14000000;
	band_20m.band_code = 0b0010;
	band_20m.pre_handler = pre_handler;
	band_20m.handler = handler;
	band_20m.post_handler = post_handler;
	band_20m.band_name = "20m (14.175 MHz)";
	band_20m.current_freq = 14250000;
	band_20m.index = BAND_20M;

}

void pre_handler(band_data_t current_band) {
	//freq = get_current_freq_from_eeprom(current_band);
	dds_set_freq(freq);
}

void post_handler(band_data_t current_band) {
	sprintf(UART_BUFFER, "post_handler: %s\r\n", current_band.band_name);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
}

void save_current_freq_to_eeprom(void) {

	uint8_t data_to_save[4];
	data_to_save[0] = 0x11;
	data_to_save[1] = 0x22;
	data_to_save[2] = 0x33;
	data_to_save[3] = 0x44;
	sprintf(UART_BUFFER, "Save to eeprom:\n0x%02X\n0x%02X\n0x%02X\n0x%02X\n",
			data_to_save[0], data_to_save[1], data_to_save[2], data_to_save[2]);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);

	EEPROM_Write(3, 10, data_to_save, 4);

}

uint32_t get_current_freq_from_eeprom(void) {

	uint8_t data_to_read[4];
	EEPROM_Read(3, 10, data_to_read, 4);
	sprintf(UART_BUFFER, "Read to eeprom:\n0x%02X\n0x%02X\n0x%02X\n0x%02X\n",
			data_to_read[0], data_to_read[1], data_to_read[2], data_to_read[2]);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
	return current_band.current_freq;
}

void handler(band_data_t current_band) {

	_encoder_process(current_band);
	print_freq(freq);

}

void band_process(void) {

	current_band = get_current_band();
	prev_band = current_band;

	current_band.pre_handler(current_band);

	while (prev_band.index == current_band.index) {
		current_band.handler(current_band);
		current_band = get_current_band();
	}

	current_band.post_handler(current_band);

}

void _encoder_process(band_data_t current_band) {
	int32_t currCounter = __HAL_TIM_GET_COUNTER(&htim1);
	currCounter = 32767 - ((currCounter - 1) & 0xFFFF);
	if (currCounter != prevCounter) {
		int32_t delta = currCounter - prevCounter;
		prevCounter = currCounter;
		if ((delta > -10) && (delta < 10)) {
			if (delta < 0) {

				freq = (freq >= current_band.max_freq) ?
						current_band.max_freq : (freq += freq_change_step);
				dds_set_freq(freq);
			} else {
				freq = (freq <= current_band.min_freq) ?
						current_band.min_freq : (freq -= freq_change_step);
			}
			dds_set_freq(freq);
		}
	}
}

band_data_t get_current_band() {
	band_data_t band_to_return;
	if (active_20m_band_flag == 1) {
		band_to_return = band_20m;
	}

	if (active_40m_band_flag == 1) {
		band_to_return = band_40m;
	}
	if (active_80m_band_flag == 1) {
		band_to_return = band_80m;
	}
	return band_to_return;
}

void dds_set_freq(uint32_t freq) {
	si5351PLLConfig_t pll_conf;
	si5351OutputConfig_t out_conf;
	si5351_Calc(freq, &pll_conf, &out_conf);
	si5351_SetupPLL(SI5351_PLL_A, &pll_conf);
	si5351_SetupOutput(0, SI5351_PLL_A, SI5351_DRIVE_STRENGTH_8MA, &out_conf,
			0);
	si5351_EnableOutputs(1 << 0);

}

void print_freq(uint32_t freq) {
	MAX7219_print_int(freq);

}

void test_eeprom(void) {
	uint8_t xBuffer[2];
	xBuffer[0] = 'M'; //0x4D
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t) EEPRON_I2C_ADDRESS,
	MEMORY_ADDRESS, 1, xBuffer, 1, 5);
	HAL_Delay(10);
	xBuffer[0] = 0x00; //clear buffer
	HAL_Delay(100);
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) EEPRON_I2C_ADDRESS, MEMORY_ADDRESS, 1,
			xBuffer, 1, 5);

	sprintf(UART_BUFFER, "Read from EEPROM: 0x%d\r\n", xBuffer[0]);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);

}
