#include "main.h"
#include "con_rs232.h"
#include "con_rs232.h"
#include "command_handler.h"
#include "string.h"

extern UART_HandleTypeDef huart1;

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

bool Rs232InputMessage(void)
{
	uint8_t bt;

	uint16_t wptr = RS232_INPUT_BUF_SIZE - hdma_usart1_rx.Instance->CNDTR;
	while(con.in.rs232.rptr != wptr)
	{
		bt = con.in.rs232.buf[con.in.rs232.rptr++];
		if(con.in.rs232.rptr == RS232_INPUT_BUF_SIZE)
			con.in.rs232.rptr = 0;
		if(bt == 0x0A || bt == 0x0D || bt == '/')
		{
			if(con.command.len > 2)
			{
				con.command.buf[con.command.len] = 0;
				return true;
			}
			else
			{
				con.command.len = 0;
			}
		}
		else
		{
			con.command.buf[con.command.len++] = bt;
			con.command.buf[con.command.len] = 0;
		}
	}
	return false;
}

void Rs232OutputMessage(void)
{
	uint8_t res;
	uint16_t len;
	uint8_t endbuf = 0;

	if(hdma_usart1_tx.State != HAL_DMA_STATE_READY)
		return;
	if(con.out.wptr == con.out.rs232.rptr)
		return;
	if(con.out.wptr > con.out.rs232.rptr)
	{
		len = con.out.wptr - con.out.rs232.rptr;
	}
	else
	{
		len = OUTPUT_BUF_SIZE - con.out.rs232.rptr;
		endbuf = 1;
	}
	huart1.gState = HAL_UART_STATE_READY;
	if(len > RS232_OUTPUT_BUF_SIZE)
		len = RS232_OUTPUT_BUF_SIZE;
	memcpy(con.out.rs232.dma_buf, &con.out.buf[con.out.rs232.rptr], len);
	res = HAL_UART_Transmit_DMA(&huart1, con.out.rs232.dma_buf, len);
	if(res == HAL_OK)
	{
		if(endbuf)
			con.out.rs232.rptr = 0;
		else
			con.out.rs232.rptr += len;
	}
}

