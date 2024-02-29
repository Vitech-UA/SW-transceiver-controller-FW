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
#include "periph.h"

#include "driver.h"
extern UART_HandleTypeDef huart2;
extern char UART_BUFFER[40];

#define USE_EEPROM

uint8_t btn_pressed_flag = 0;
uint8_t active_20m_band_flag = 0;
uint8_t active_40m_band_flag = 0;
uint8_t active_80m_band_flag = 0;

TM1638_Handler_t Handler;

uint32_t intermediate_frequency_hz = 8865000;

extern I2C_HandleTypeDef hi2c1;

band_data_t band_80m;
band_data_t band_40m;
band_data_t band_20m;
band_data_t current_band;
band_data_t prev_band;
uint32_t prevCounter = 0;
volatile uint32_t current_freq = 0;
uint32_t freq_change_step = 50;

enum
{
	BAND_20M = 0, BAND_40M, BAND_80M,
};

void init_bands(void)
{
	band_80m.max_freq = 3800000;
	band_80m.default_freq = 3650000;
	band_80m.min_freq = 3500000;
	band_80m.band_code = 0b1000;
	band_80m.pre_handler = pre_handler;
	band_80m.handler = handler;
	band_80m.post_handler = post_handler;
	band_80m.band_name = "80m (3.65 MHz)";
	band_80m.current_freq = 0;
	band_80m.index = BAND_80M;
	band_80m.store_address = 0x00;

	band_40m.max_freq = 7200000;
	band_40m.default_freq = 7100000;
	band_40m.min_freq = 7000000;
	band_40m.band_code = 0b0100;
	band_40m.pre_handler = pre_handler;
	band_40m.handler = handler;
	band_40m.post_handler = post_handler;
	band_40m.band_name = "40m (7.1 MHz)";
	band_40m.current_freq = 0;
	band_40m.index = BAND_40M;
	band_40m.store_address = 0x10;


	band_20m.max_freq = 14350000;
	band_20m.default_freq = 14175000;
	band_20m.min_freq = 14000000;
	band_20m.band_code = 0b0010;
	band_20m.pre_handler = pre_handler;
	band_20m.handler = handler;
	band_20m.post_handler = post_handler;
	band_20m.band_name = "20m (14.175 MHz)";
	band_20m.current_freq = 0;
	band_20m.index = BAND_20M;
	band_20m.store_address = 0x20;

}

void pre_handler(band_data_t current_band)
{
	sprintf(UART_BUFFER, "Current band: %s\n", current_band.band_name);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
#ifdef USE_EEPROM
	current_freq = get_current_freq_from_eeprom(current_band.store_address);
#endif
	// Якщо з eeprom вичитано якесь не валідне значення частоти, то сетимо туди дефолтне. Кейс нової eeprom/
	if (current_freq > current_band.max_freq
			|| current_freq < current_band.min_freq)
	{
		current_freq = current_band.default_freq;
	}
	sprintf(UART_BUFFER, "Current freq: %lu\n", current_freq);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
	set_band_code(current_band);
	dds_set_freq(current_freq + intermediate_frequency_hz);
	print_freq(current_freq);

}

void post_handler(band_data_t current_band)
{
#ifdef USE_EEPROM
	save_current_freq_to_eeprom(current_band);
#endif
	current_band.current_freq = current_freq;
}

void save_current_freq_to_eeprom(band_data_t band_data)
{
	sprintf(UART_BUFFER, "Save to eeprom: %lu\n", current_freq);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);
	EEPROM_write_HAL_based(band_data.store_address, current_freq);

}

uint32_t get_current_freq_from_eeprom(uint16_t store_address)
{
	uint32_t freq_from_eeprom = 0;
	freq_from_eeprom = EEPROM_read_HAL_based(store_address);
	sprintf(UART_BUFFER, "Read from eeprom: %lu\n", freq_from_eeprom);
	HAL_UART_Transmit(&huart2, (uint8_t*) UART_BUFFER, strlen(UART_BUFFER),
			100);

	return freq_from_eeprom;
}

void handler(band_data_t current_band)
{

	encoder_process(current_band);
	set_preamp(!HAL_GPIO_ReadPin(cEN_PREAMPL_GPIO_Port, cEN_PREAMPL_Pin));
	set_ATT(!HAL_GPIO_ReadPin(cEN_ATT_GPIO_Port, cEN_ATT_Pin));
	set_RxTx(!HAL_GPIO_ReadPin(cTx_Rx_GPIO_Port, cTx_Rx_Pin));

}

void band_process(void)
{
	current_band = get_current_band();
	prev_band = current_band;
	current_band.pre_handler(current_band);
	while (prev_band.index == current_band.index)
	{
		current_band.handler(current_band);
		prev_band = get_current_band();
	}
	current_band.post_handler(current_band);

}

void encoder_process(band_data_t current_band)
{
	int32_t currCounter = __HAL_TIM_GET_COUNTER(&htim1);
	currCounter = 32767 - ((currCounter - 1) & 0xFFFF);
	if (currCounter != prevCounter)
	{
		int32_t delta = currCounter - prevCounter;
		prevCounter = currCounter;
		if ((delta > -10) && (delta < 10))
		{
			if (delta < 0)
			{

				if (current_freq >= current_band.max_freq)
				{
					current_freq = current_band.max_freq;
				}
				else
				{
					current_freq += freq_change_step;
				}

			}
			else
			{
				if (current_freq <= current_band.min_freq)
				{
					current_freq = current_band.min_freq;
				}
				else
				{
					current_freq -= freq_change_step;
				}

			}
			current_band.current_freq = current_freq;
			dds_set_freq(current_freq + intermediate_frequency_hz);
			print_freq(current_freq);
		}
	}
}

band_data_t get_current_band()
{
	band_data_t band_to_return;
	if (active_20m_band_flag == 1)
	{
		band_to_return = band_20m;
	}

	if (active_40m_band_flag == 1)
	{
		band_to_return = band_40m;
	}
	if (active_80m_band_flag == 1)
	{
		band_to_return = band_80m;
	}
	return band_to_return;
}

void dds_set_freq(uint32_t freq)
{
	si5351_set_freq(freq);

}

void print_freq(uint32_t freq)
{
	uint8_t data_to_display[6];
	data_to_display[0] = freq % 100000000 / 10000000;
	data_to_display[1] = freq % 10000000 / 1000000;
	data_to_display[2] = freq % 1000000 / 100000;
	data_to_display[3] = freq % 100000 / 10000;
	data_to_display[4] = freq % 10000 / 1000;
	data_to_display[5] = freq % 1000 / 100;
	TM1638_SetSingleDigit_HEX(&Handler, data_to_display[0], 0);
	TM1638_SetSingleDigit_HEX(&Handler, data_to_display[1] | TM1638DecimalPoint,
			1);
	TM1638_SetSingleDigit_HEX(&Handler, data_to_display[2], 2);
	TM1638_SetSingleDigit_HEX(&Handler, data_to_display[3], 3);
	TM1638_SetSingleDigit_HEX(&Handler, data_to_display[4] | TM1638DecimalPoint,
			4);
	TM1638_SetSingleDigit_HEX(&Handler, data_to_display[5], 5);

}

void set_band_code(band_data_t current_band)
{

	uint8_t mask = current_band.band_code;
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin,
			(mask & 0b1000) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin,
			(mask & 0b0100) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin,
			(mask & 0b0010) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin,
			(mask & 0b0001) ? GPIO_PIN_SET : GPIO_PIN_RESET);

}

