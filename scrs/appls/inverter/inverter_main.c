/*
 * inverter_main.c
 *
 *  Created on: May 17, 2015
 *      Author: Thinh
 */

#include "inv_ctr/inverter_controller_pub.h"
#include "inverter_main.h"

void inverter_init_v(void){
	inverter_controller_init_v();
}
void inverter_T10_v(void){
	inverter_controller_main_v();
}

void inverter_background_v(void){

}


