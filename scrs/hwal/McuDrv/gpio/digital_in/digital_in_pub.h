/*
 * button_pub.h
 *
 *  Created on: Mar 8, 2014
 *      Author: TV
 */

#ifndef DIGITAL_IN_PUB_H_
#define DIGITAL_IN_H_
#include "../gpio_hardware_config.h"

void digital_in_init_v(void);
BOOL digital_in_read(UBYTE t_buttonNo_ub);

#endif /* DIGITAL_IN_H_ */
