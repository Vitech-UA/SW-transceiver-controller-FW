#include "commands_head.h"
#include "command_handler.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stm32f1xx_hal.h"
#include "main.h"



const char Ver_Date[] = __DATE__;
char prn[PRINT_BLOCK_SIZE];
console_t con;

static const DebugCommand_t cmd_tbl[] =
{
		{ "set_led", led_handler },
		{ "version", version_handler },
		{ NULL, NULL },
};

void PrintString(char *str) {
	uint16_t len, len_remind;

	len = strlen(str);
	len_remind = OUTPUT_BUF_SIZE - con.out.wptr;
	if (len < len_remind) {
		memcpy(&con.out.buf[con.out.wptr], str, len);
		con.out.wptr += len;
	} else {
		memcpy(&con.out.buf[con.out.wptr], str, len_remind);
		con.out.wptr = 0;
		len -= len_remind;
		memcpy(con.out.buf, &str[len_remind], len);
		con.out.wptr += len;
	}
}

bool GetCommand(void) {
	return Rs232InputMessage();
}

void CommandHandler(void) {
	char *str_ptr = NULL;
	uint16_t len = 0, table_index = 0;

	if (GetCommand()) {
		con.command.len = 0;
		while (cmd_tbl[table_index].cmd_name != NULL) {
			char *ptr = (char*) cmd_tbl[table_index].cmd_name;
			str_ptr = con.command.buf;
			len = strlen(ptr);
			uint16_t i = 0;
			while (ptr[i] == str_ptr[i])
				i++;
			if (i >= len) {
				str_ptr += len;
				prn[0] = 0;
				cmd_tbl[table_index].handler(str_ptr);
				break;
			} else {
				table_index++;
				str_ptr = NULL;
			}
		}

		HAL_Delay(10);
		PrintString(prn);
	}
	HAL_Delay(10);
	Rs232OutputMessage();
}

void led_handler(char *param_ptr) {
	uint32_t led_state;


	if (sscanf(param_ptr, "%u", (unsigned int*) &led_state) == 1) {

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, led_state);
		sprintf(prn, "SET_LED;%u\r\n", (unsigned int) led_state);
	}

}

void version_handler(char *param_ptr)
{
	sprintf(prn, "VERSION:1.0\r\n");
}
