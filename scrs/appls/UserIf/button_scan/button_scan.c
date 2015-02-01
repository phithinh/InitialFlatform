/*
 * button_scan.c
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */

#include <general_define.h>
#include "button_scan_cfg.h"
#include "button_scan_pinAdapts.h"
#include "button_scan_pri.h"
#include "button_scan_pub.h"

void button_scan_init_v(void) {
	UBYTE t_button_index_ub;
	//clear button status
	for (t_button_index_ub = 0; t_button_index_ub < NUMBER_BUTTON;
				t_button_index_ub++) {
		l_button_scan_counter_uw[t_button_index_ub] = 0;
	}
}
void button_scan_main_v(void) {
	UBYTE t_button_index_ub;
	UWORD t_button_timestamp_uw;
	BOOL t_button_PhyState_b = 0;
	UBYTE t_button_State_ub;
	for (t_button_index_ub = 0; t_button_index_ub < NUMBER_BUTTON;
			t_button_index_ub++) {
		t_button_State_ub = BUTTON_IDLE_EV;
		// counting the duration of button falling
		t_button_PhyState_b = button_read_b(t_button_index_ub);
		t_button_timestamp_uw = l_button_scan_counter_uw[t_button_index_ub];
		if(!t_button_PhyState_b){
			if (t_button_timestamp_uw < (UWORD_MAX - BUTTON_CYCLIC_TIME)){
				t_button_timestamp_uw += BUTTON_CYCLIC_TIME;
			}
		} else {
			if (t_button_timestamp_uw >= BUTTON_SHORT_TIP){
				t_button_State_ub = BUTTON_RELEASE_EV;
			} else {
				t_button_State_ub = BUTTON_IDLE_EV;
			}
			t_button_timestamp_uw = 0;
		}

		//detecting event
		if ((t_button_timestamp_uw >= BUTTON_SHORT_TIP)	\
				&&(t_button_timestamp_uw < (BUTTON_SHORT_TIP+BUTTON_CYCLIC_TIME))){
			t_button_State_ub = BUTTON_SHORT_EV;
		} else if( (t_button_timestamp_uw >= BUTTON_LONG_TIP)
				&&(t_button_timestamp_uw < (BUTTON_LONG_TIP+BUTTON_CYCLIC_TIME))){
			t_button_State_ub = BUTTON_LONG_EV;
		} else if (t_button_timestamp_uw >= (BUTTON_LONG_TIP+BUTTON_NEXT_LONG_TIP)){
			t_button_timestamp_uw = BUTTON_LONG_TIP+BUTTON_CYCLIC_TIME;
			t_button_State_ub = BUTTON_LONG_EV;
		} else{
			//do no thing
		}
		l_button_scan_counter_uw[t_button_index_ub] = t_button_timestamp_uw;
		button_scan_setButtonSta_v(t_button_index_ub,t_button_State_ub);
	}

}
