/*
 * interfaces.c
 *
 *  Created on: Apr 19, 2014
 *      Author: TV
 */
#include <compiler.h>
#include "interfaces.h"

BUTTON_STATUS_ST	global_button_status_st;
RELAY_STATUS_ST 	global_relay_status_st;
ADC_VALUES_ST 		global_adc_values_st;
DEF_TIME_ST		global_time_st;

DATACOLLECTION_RX_SERIAL_ST_DEF 		global_DataCollection_rx_serial_st;



BUTTON_STATUS_ST	*global_button_status_pst 	= &global_button_status_st;
RELAY_STATUS_ST 	*global_relay_status_pst	= &global_relay_status_st;
ADC_VALUES_ST 		*global_adc_values_pst		= &global_adc_values_st;
DEF_TIME_ST			*global_time_pst			= &global_time_st;
DATACOLLECTION_RX_SERIAL_ST_DEF 	*global_DataCollection_rx_serial_pst		= &global_DataCollection_rx_serial_st;
