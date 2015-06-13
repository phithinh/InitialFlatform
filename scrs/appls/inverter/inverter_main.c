/*
 * inverter_main.c
 *
 *  Created on: May 17, 2015
 *      Author: Thinh
 */
#include <general_define.h>
#include "inv_ctr/inverter_controller_pub.h"
#include "inverter_main.h"

#define __INV_MAIN
#include "inverter_adpts.h"

void inverter_init_v(void){
	inv_inv_threshold_pst = &inv_threshold_st;
	inv_inv_sensor_feedback_pst = &inv_sensor_feedback_st;
	inverter_controller_init_v();
}
void inverter_T10_v(void){
	inverter_controller_main_v();
}

void inverter_background_v(void){

}

#undef __INV_MAIN
