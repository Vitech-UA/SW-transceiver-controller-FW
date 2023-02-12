#pragma once
#include "con_rs232.h"
#include "stdint.h"

#define PRINT_BLOCK_SIZE 			1024+256
#define COMMAND_BUF_SIZE			1024+200
#define OUTPUT_BUF_SIZE   		256


#define HEX_STRING_MAX		64


typedef void (*cmd_handler)(char *data_ptr);

typedef struct
{
	const char *cmd_name;
	cmd_handler handler;
} DebugCommand_t;

typedef struct
{
	uint16_t len;
	char buf[COMMAND_BUF_SIZE + 1];
} command_pack_t;

typedef struct
{
  rs232_input_t rs232;
} console_input_t;

typedef struct
{
	rs232_output_t rs232;
	uint16_t wptr;
	uint8_t buf[OUTPUT_BUF_SIZE];
} console_output_t;

typedef struct
{
	command_pack_t command;
	console_input_t in;
	console_output_t out;
} console_t;

extern console_t con;

void CommandHandler(void);
