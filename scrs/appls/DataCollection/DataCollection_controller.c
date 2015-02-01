/*
 * DataCollection_controller.c
 *
 *  Created on: Oct 9, 2014
 *      Author: Phi Thinh
 */
#include <compiler.h>
#include <interfaces.h>

#include "adc_reading/adc_reading.h"
#include "DataCollection_time/DataCollection_time.h"
#include "serial/serial_receiver.h"

#include "DataCollection_runnables.h"

ADC_VALUES_ST *DataCollection_global_adc_values_pst = 0;
DEF_TIME_ST *DataCollection_global_time_pst = 0;
DATACOLLECTION_RX_SERIAL_ST_DEF *DataCollection_global_DataCollection_rx_serial_st = 0;

void DataCollection_Init_v(ADC_VALUES_ST * p_adc_values_pst,
		DEF_TIME_ST *p_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st)
{
	DataCollection_global_adc_values_pst = p_adc_values_pst;
	DataCollection_global_time_pst = p_global_time_pst;
	DataCollection_global_DataCollection_rx_serial_st = p_logger_DataCollection_rx_serial_st;

	DataCollection_time_init_v();
	//adc_reading_init_v();
	//DataCollection_serial_init_v();

	DataCollection_global_adc_values_pst = 0;
	DataCollection_global_time_pst = 0;
	DataCollection_global_DataCollection_rx_serial_st = 0;
}
void DataCollection_Main_T10_v(
		DEF_TIME_ST *p_global_time_pst,
		ADC_VALUES_ST * p_adc_values_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st)
{
	DataCollection_global_time_pst = p_global_time_pst;
	DataCollection_global_adc_values_pst = p_adc_values_pst;
	DataCollection_global_DataCollection_rx_serial_st = p_logger_DataCollection_rx_serial_st;


	DataCollection_time_update_v();

	DataCollection_global_time_pst = 0;
	DataCollection_global_adc_values_pst = 0;
	DataCollection_global_DataCollection_rx_serial_st = 0;
}
void DataCollection_Main_T1_v(DEF_TIME_ST *p_global_time_pst,
		ADC_VALUES_ST * p_adc_values_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st)
{
	DataCollection_global_time_pst = p_global_time_pst;
	DataCollection_global_adc_values_pst = p_adc_values_pst;
	DataCollection_global_DataCollection_rx_serial_st = p_logger_DataCollection_rx_serial_st;


	DataCollection_time_update_v();
	//adc_reading_main_T1_v();
	//DataCollection_serial_receiver_mainT1_v();

	DataCollection_global_time_pst = 0;
	DataCollection_global_adc_values_pst = 0;
	DataCollection_global_DataCollection_rx_serial_st = 0;
}
