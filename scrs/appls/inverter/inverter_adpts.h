/*
 * inverter_adpts.h
 *
 *  Created on: May 17, 2015
 *      Author: Thinh
 */

#ifndef NET_ADPTS_H_
#define NET_ADPTS_H_

#include <interfaces.h>

#define l_inv_txRingBuff_front_ub	net_tx_data_request_st.RingBuff_front_ub
#define l_inv_txRingBuff_rear_ub	net_tx_ctr_request_st.RingBuff_rear_ub
#define l_inv_txRingBuff_aub		net_tx_data_request_st.RingBuff_aub

__STATIC_INLINE void l_inv_sent_char_v(unsigned char p_data_ub)
{
	l_inv_txRingBuff_aub[l_inv_txRingBuff_front_ub] = p_data_ub;
	l_inv_txRingBuff_front_ub = (l_inv_txRingBuff_front_ub+1)%NET_TX_MAX_RINGBUFF;
}

#endif /* NET_ADPTS_H_ */
