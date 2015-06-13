/*
 * net_reaction.c
 *
 *  Created on: Jun 2, 2015
 *      Author: Thinh
 */
#include <string.h>
#include <inv_com.h>
#include "net_reaction.h"

void net_input_reaction_v(unsigned char *p_data_ub, unsigned short p_lenght_uw){
	if(!memcmp(p_data_ub,"threshold",9)){
		inverter_com_send_threshold_v();
	} else if (!memcmp(p_data_ub,"data",4)){
		inverter_com_send_cur_data_v();
	}
}
