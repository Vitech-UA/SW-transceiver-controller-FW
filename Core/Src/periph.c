/*
 * periph.c
 *
 *  Created on: Nov 2, 2023
 *      Author: Vitech-UA
 */

#include "periph.h"
#include "main.h"

void set_tranceiver_state(transiver_state_t state) {
	/* HIGH TX
	 * LOW RX*/

	HAL_GPIO_WritePin(TX_OUT_GPIO_Port, TX_OUT_Pin, state);

}

void set_swr_meter(state_SWR_t state) {
	HAL_GPIO_WritePin(SWR_GPIO_Port, SWR_Pin, state);

}

void set_preamp(state_PREAMP_t state){
    HAL_GPIO_WritePin(PREAMP_GPIO_Port, PREAMP_Pin, state);
}

void set_ATT(state_ATT_t state){
    HAL_GPIO_WritePin(ATT_GPIO_Port, ATT_Pin, state);
}

void set_RxTx(state_RxTx_t state){
    HAL_GPIO_WritePin(TX_OUT_GPIO_Port, TX_OUT_Pin, !state);
}
