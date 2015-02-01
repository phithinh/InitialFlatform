/*
 * Logger_runables.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */

#ifndef LOGGER_RUNABLES_H_
#define LOGGER_RUNABLES_H_

void Logger_Init_v(BUTTON_STATUS_ST *p_logger_global_button_status_pst,
		ADC_VALUES_ST *p_logger_global_adc_values_pst,
		DEF_TIME_ST *p_logger_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st
		);

void Logger_Main_1ms_v(BUTTON_STATUS_ST *p_logger_global_button_status_pst,
		ADC_VALUES_ST *p_logger_global_adc_values_pst,
		DEF_TIME_ST *p_logger_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st);
void Logger_Main_10msLow_v(BUTTON_STATUS_ST *p_logger_global_button_status_pst,
		ADC_VALUES_ST *p_logger_global_adc_values_pst,
		DEF_TIME_ST *p_logger_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st);
void Logger_Main_10ms_v(void);

#endif /* LOGGER_RUNABLES_H_ */
