/*
 * net.h
 *
 *  Created on: Apr 29, 2014
 *      Author: TV
 */

#ifndef NET_H_
#define NET_H_
#include <interfaces.h>

void net_T1_process_v(button_status_tst*	p_button_status_st,
						adc_values_tst* 	p_adc_values_st);
void net_T10_process_v(button_status_tst*	p_button_status_st,
						adc_values_tst* 	p_adc_values_st);


#endif /* NET_H_ */
