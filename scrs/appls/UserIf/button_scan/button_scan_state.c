/*
 * button_scan_state.c
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */
#include <general_define.h>
#include "button_scan_pub.h"

#include "button_scan_cfg.h"
UBYTE button_state_ub[NUMBER_BUTTON];

void button_scan_setButtonSta_v(UBYTE p_button_index_ub,UBYTE p_button_State_ub){
	button_state_ub[p_button_index_ub] = p_button_State_ub;
}

UBYTE button_scan_readButtonSta_ub(UBYTE p_button_index_ub){
	UBYTE t_button_sta_ub;
	t_button_sta_ub = button_state_ub[p_button_index_ub];
	switch (t_button_sta_ub){
	case BUTTON_SHORT_EV:
	case BUTTON_LONG_EV:
		return 1;
		break;
	case BUTTON_IDLE_EV:
	case BUTTON_RELEASE_EV:
	default:
		return(0);
		break;
	}
}
