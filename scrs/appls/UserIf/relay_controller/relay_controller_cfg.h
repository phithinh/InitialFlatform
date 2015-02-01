/*
 * relay_controller_cfg.h
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */

#ifndef RELAY_CONTROLLER_CFG_H_
#define RELAY_CONTROLLER_CFG_H_


typedef enum{
	Relay_1 = 0,
	Relay_2,
	Relay_3,
	NUM_OF_RELAY
}RELAY_NAME;

extern UBYTE relay_adapt_id[NUM_OF_RELAY];
extern UBYTE relay_light_adapt_id[NUM_OF_RELAY];

#endif /* RELAY_CONTROLLER_CFG_H_ */
