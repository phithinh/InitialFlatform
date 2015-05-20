/*
 * environment.c
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */

#include <compiler.h>
#include <interfaces.h>
#include <gpio_pub.h>

//===========================
#include <inverter_main.h>
#include <net.h>
//===========================

#include "environment.h"

void environment_init_v(void) {
  digital_out_init_v();

  inverter_init_v();
  net_init_v();
}
void environment_T10_v(void) {
	inverter_T10_v();
}
void environment_background_v(void){
	inverter_background_v();
	net_background_v();
}
