/*
 * DataCollection_runnables.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */

#ifndef DATACOLLECTION_RUNNABLES_H_
#define DATACOLLECTION_RUNNABLES_H_

void DataCollection_Init_v(ADC_VALUES_ST * p_adc_values_pst,
		DEF_TIME_ST *p_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st);
void DataCollection_Main_T10_v(
		DEF_TIME_ST *p_global_time_pst,
		ADC_VALUES_ST * p_adc_values_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st);
void DataCollection_Main_T1_v(DEF_TIME_ST *p_global_time_pst,
		ADC_VALUES_ST * p_adc_values_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st);

#endif /* DATACOLLECTION_RUNNABLES_H_ */
