/*
 * relay_controller_adapt.h
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */

#ifndef RELAY_CONTROLLER_ADAPT_H_
#define RELAY_CONTROLLER_ADAPT_H_
#include "digital_out_pub.h"


#define relay_actuation_v(relay_id)		digital_out_set_v(relay_adapt_id[relay_id],1); digital_out_set_v(relay_light_adapt_id[relay_id],1)
#define relay_disable_v(relay_id)		digital_out_set_v(relay_adapt_id[relay_id],0); digital_out_set_v(relay_light_adapt_id[relay_id],0)


#endif /* RELAY_CONTROLLER_ADAPT_H_ */
