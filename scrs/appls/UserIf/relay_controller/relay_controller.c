/*
 * relay_controller.c
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */
#include <general_define.h>
#include "relay_controller_cfg.h"
#include "relay_controller_adapt.h"

#define RELAY_CONTROLLER
#include "relay_controller.h"

void relay_main(void){
	UBYTE t_relay_id_ub;
	UBYTE t_relay_sta_ub;
	if (NUM_OF_RELAY == 0)
		return;
	for (t_relay_id_ub = 0;t_relay_id_ub <NUM_OF_RELAY;t_relay_id_ub++){
		t_relay_sta_ub = relay_state_ub[t_relay_id_ub];
		if (t_relay_sta_ub){
			relay_actuation_v(t_relay_id_ub);
		} else {
			relay_disable_v(t_relay_id_ub);
		}
	}
}

void relay_set(UBYTE p_relayid_ub, UBYTE p_state_ub){
	if (p_relayid_ub<NUM_OF_RELAY){
		relay_state_ub[p_relayid_ub] = p_state_ub;
	}
}
