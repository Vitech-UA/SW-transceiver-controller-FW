/*
 * periph.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Vitech-UA
 */

#ifndef INC_PERIPH_H_
#define INC_PERIPH_H_

typedef enum {
	RECEIVE = 0, TRANSMIT,

} transiver_state_t;

typedef enum {
	DISABLE_SWR_METER = 0, ENABLE_SWR_METER,

} state_SWR_t;

typedef enum {
	DISABLE_PREAMP = 0, ENABLE_PREAMP,

} state_PREAMP_t;
typedef enum {
	DISABLE_ATT = 0, ENABLE_ATT,

} state_ATT_t;

typedef enum {
	Rx = 0, Tx,

} state_RxTx_t;

void set_tranceiver_state(transiver_state_t state);
void set_swr_meter(state_SWR_t state);
void set_preamp(state_PREAMP_t state);
void set_ATT(state_ATT_t state);
void set_RxTx(state_RxTx_t state);

#endif /* INC_PERIPH_H_ */
