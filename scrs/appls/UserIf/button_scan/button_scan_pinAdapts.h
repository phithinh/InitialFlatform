/*
 * button_scan_pinAdapts.h
 *
 *  Created on: Apr 19, 2014
 *      Author: TV
 */

#ifndef BUTTON_SCAN_PINADAPTS_H_
#define BUTTON_SCAN_PINADAPTS_H_
#include <digital_out_pub.h>

#define button_read_b(t_button_index_ub)	digital_in_read(button_cfg_id_ub[t_button_index_ub])
	
#endif /* BUTTON_SCAN_PINADAPTS_H_ */
