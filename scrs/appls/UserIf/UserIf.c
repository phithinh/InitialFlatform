/*
 * UserIf_runnables.c
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */

#include <general_define.h>

#include <button_scan_pub.h>

#include <relay_controller.h>
#include "UserIf.h"

void UserIf_Init(void){
	button_scan_init_v();
}

void UserIf_Input_main(void){
	button_scan_main_v();
}

void UserIf_Ouput_main(void){
	relay_main();
}
UBYTE delay_time;
void UserIf_OuputLow_main(void){
	if (delay_time<50){
		OLED_DC_Set();
		OLED_CS_Set();
		delay_time++;
	}else if (delay_time == 50){
		delay_time++;
		lcd_init();
	}else{
		lcd_main();
	}
}
