/*
 * p_rx_serial.h
 *
 *  Created on: Nov 9, 2014
 *      Author: Phi Thinh
 */

#ifndef P_RX_SERIAL_H_
#define P_RX_SERIAL_H_

#define RX_SERIAL_MAX_BUFF	100

typedef enum{
	RX_SERIAL_INVALID = 0,
	RX_SERIAL_VALID
}RX_SERIAL_STA_DEF;

typedef struct{
	RX_SERIAL_STA_DEF status;
	UBYTE data_aub[RX_SERIAL_MAX_BUFF];
	UBYTE data_cnt_ub;
}DATACOLLECTION_RX_SERIAL_ST_DEF;

#endif /* P_RX_SERIAL_H_ */
