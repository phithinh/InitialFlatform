/*
 * relay_controller.c
 *
 *  Created on: Apr 29, 2014
 *      Author: TV
 */

#include <general_define.h>
#include <digital_out_pub.h>
#include <gpio_pinName.h>

#ifdef _BOARD_RELAY

#define RELAY_NUM		24
void relay_controller_set_v(ULONG p_relay_data_ub){
	UBYTE t_iloop_ub;
	for(t_iloop_ub=0;t_iloop_ub<RELAY_NUM;t_iloop_ub++){
		digital_out_set_v(SERIAL_DATA_IN1,(BOOL)p_relay_data_ub&0x0001);
		p_relay_data_ub=p_relay_data_ub>>1;
		digital_out_set_v(SHIFT,FALSE);
		digital_out_set_v(SHIFT,TRUE);
	}
	digital_out_set_v(LATCH, FALSE);
	digital_out_set_v(LATCH, TRUE);
}
#endif

