/*
 * p_com_tx.h
 *
 *  Created on: May 17, 2015
 *      Author: Thinh
 */

#ifndef P_COM_TX_H_
#define P_COM_TX_H_

#define NET_TX_MAX_RINGBUFF	127
typedef struct{
	UBYTE RingBuff_aub[NET_TX_MAX_RINGBUFF];
	UBYTE RingBuff_front_ub;
}NET_TX_DATA_REQUEST_TDEF;
typedef struct{
	UBYTE RingBuff_rear_ub;
}NET_TX_CTR_REQUEST_TDEF;

#endif /* P_COM_TX_H_ */
