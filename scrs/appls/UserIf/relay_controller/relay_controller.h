/*
 * relay_controller.h
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */

#ifndef RELAY_CONTROLLER_H_
#define RELAY_CONTROLLER_H_

#ifdef RELAY_CONTROLLER
UBYTE relay_state_ub[NUM_OF_RELAY];
#endif

void relay_main(void);
void relay_set(UBYTE p_relayid_ub, UBYTE p_state_ub);
#endif /* RELAY_CONTROLLER_H_ */
