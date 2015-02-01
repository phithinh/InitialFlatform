/*
 * interface.h
 *
 *  Created on: Apr 19, 2014
 *      Author: TV
 */

#ifndef INTERFACES_H_
#define INTERFACES_H_
#include "p_adc_values.h"
#include "p_button_status.h"
#include "p_relay_status.h"
#include "p_time.h"
#include "p_rx_serial.h"

extern BUTTON_STATUS_ST	*global_button_status_pst;
extern RELAY_STATUS_ST 	*global_relay_status_pst;
extern ADC_VALUES_ST 	*global_adc_values_pst;
extern DEF_TIME_ST		*global_time_pst;
extern DATACOLLECTION_RX_SERIAL_ST_DEF *global_DataCollection_rx_serial_pst;

#endif /* INTERFACES_H_ */
