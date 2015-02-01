/*
 * button_scan_pri.h
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */

#ifndef BUTTON_SCAN_PRI_H_
#define BUTTON_SCAN_PRI_H_
#include <general_define.h>
#include <digital_in_pub.h>
#include <gpio_hardware_config.h>

#include "button_scan_cfg.h"


UBYTE l_button_scan_counter_uw[NUMBER_BUTTON];
extern UBYTE button_cfg_id_ub[NUMBER_BUTTON];

#endif /* BUTTON_SCAN_PRI_H_ */
