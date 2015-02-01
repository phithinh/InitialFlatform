/*
 * digital_out_pub.h
 *
 *  Created on: Mar 8, 2014
 *      Author: TV
 */

#ifndef DIGITAL_OUT_PUB_H_
#define DIGITAL_OUT_PUB_H_
#include "../gpio_hardware_config.h"

void digital_out_init_v(void);
void digital_out_set_v(UBYTE t_digital_outNo_ub, BOOL t_digital_outSta_b);
void digital_out_toggle_v(UBYTE t_digital_outNo_ub);


#endif /* DIGITAL_OUT_PUB_H_ */
