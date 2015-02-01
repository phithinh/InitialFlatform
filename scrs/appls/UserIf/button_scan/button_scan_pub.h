/*
 * button_scan_pub.h
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */

#ifndef BUTTON_SCAN_PUB_H_
#define BUTTON_SCAN_PUB_H_
#include <p_button_status.h>

typedef enum {
	BUTTON_IDLE_EV = 0,
	BUTTON_SHORT_EV,
	BUTTON_LONG_EV,
	BUTTON_RELEASE_EV
}BUTTON_EVENT;

void button_scan_init_v(void);
void button_scan_main_v(void);


void button_scan_setButtonSta_v(UBYTE p_button_index_ub,UBYTE p_button_State_ub);
UBYTE button_scan_readButtonSta_ub(UBYTE p_button_index_ub);
#endif /* BUTTON_SCAN_PUB_H_ */
