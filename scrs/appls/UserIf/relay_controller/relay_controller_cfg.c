/*
 * relay_controller_cfg.c
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */
#include <general_define.h>
#include <digital_out_pub.h>
#include "relay_controller_cfg.h"

UBYTE relay_adapt_id[NUM_OF_RELAY] = {
		RELAY1,
		RELAY2,
		RELAY3
};

UBYTE relay_light_adapt_id[NUM_OF_RELAY] = {

		LED_OUT1,
		LED_OUT2,
		LED_OUT3
};
