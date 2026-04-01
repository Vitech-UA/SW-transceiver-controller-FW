/*
 * periph.c
 *
 *  Created on: Nov 2, 2023
 *      Author: Vitech-UA
 */

#include "periph.h"
#include "main.h"

volatile uint8_t ATT_EN_MODE_FLAG = 0;
volatile uint8_t AMP_EN_MODE_FLAG = 0;
volatile uint8_t TX_MODE_FLAG = 0;

void set_tranceiver_state(transiver_state_t state) {
	/* HIGH TX
	 * LOW RX*/

	HAL_GPIO_WritePin(TX_OUT_GPIO_Port, TX_OUT_Pin, state);

}

void set_preamp(state_PREAMP_t state) {
	if (TX_MODE_FLAG == Tx) {
		// Запобіжник, щоб в режимі передачі не включити вхідний підсилювач
		return;
	} else {

		HAL_GPIO_WritePin(PREAMP_GPIO_Port, PREAMP_Pin, state);
		if (state)
			AMP_EN_MODE_FLAG = 1;
		else
			AMP_EN_MODE_FLAG = 0;
	}
}

void set_ATT(state_ATT_t state) {
	HAL_GPIO_WritePin(ATT_GPIO_Port, ATT_Pin, state);
	if (state)
		ATT_EN_MODE_FLAG = 1;
	else
		ATT_EN_MODE_FLAG = 0;
}

void set_RxTx(state_RxTx_t state) {

	if (state == Tx) {
		// В режимі передачі - примусово вирубаю PREAMP, навіть, якщо він включений!
		if (AMP_EN_MODE_FLAG == 1) {
			set_preamp(DISABLE_PREAMP);
		}
		// В режимі передачі - примусово врубаю ATT, навіть, якщо він виключений!
		if (ATT_EN_MODE_FLAG == 0) {
			set_ATT(ENABLE_ATT);
		}
	}
	if (state == Rx) {
		if (AMP_EN_MODE_FLAG == 1) {
			set_preamp(ENABLE_PREAMP);
		}
		if (ATT_EN_MODE_FLAG == 0) {
			set_preamp(DISABLE_ATT);
		}
	}
	TX_MODE_FLAG = state;
	HAL_GPIO_WritePin(TX_OUT_GPIO_Port, TX_OUT_Pin, state);

}
