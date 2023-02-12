#pragma once
#include "stdint.h"
#include "stdbool.h"

#define RS232_INPUT_BUF_SIZE  64
#define RS232_OUTPUT_BUF_SIZE  64

typedef struct
{
	uint32_t error_code;
	uint16_t rptr;
	uint8_t buf[RS232_INPUT_BUF_SIZE];
} rs232_input_t;

typedef struct
{
	uint16_t rptr;
	uint8_t dma_buf[RS232_OUTPUT_BUF_SIZE];
} rs232_output_t;

bool Rs232InputMessage(void);
void Rs232OutputMessage(void);
