/*
 * net.c
 *
 *  Created on: Apr 22, 2014
 *      Author: TV
 */
#include <general_define.h>
#include <serial_com.h>
#include "net.h"

#include "net_adpts.h"

void net_sending_v(void);

void net_init_v(void){
	RS485_init_v();
	l_net_txRingBuff_front_ub = 0;
	l_net_txRingBuff_rear_ub = 0;
}
void net_background_v(void)
{
	net_sending_v();
}

void net_sending_v(void){
	UBYTE t_data_ub, t_index_ub;
	if(l_net_txRingBuff_front_ub != l_net_txRingBuff_rear_ub){
		RS485_SendEnable();

		t_index_ub = l_net_txRingBuff_rear_ub;
		t_data_ub = l_net_txRingBuff_aub[t_index_ub];
		if (RS485_send_v(t_data_ub)){
			t_index_ub = (UBYTE)((t_index_ub+1)%NET_TX_MAX_RINGBUFF); //rolling;
		}
		l_net_txRingBuff_rear_ub = t_index_ub;

		if (l_net_txRingBuff_front_ub == l_net_txRingBuff_rear_ub){
			RS485_ReadEnable();
		}
	}
}
