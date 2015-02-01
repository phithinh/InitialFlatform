
#include <compiler.h>
#include <interfaces.h>

//#include "_lib/Logger.h"
#include "Logger_sdw.h"

const BUTTON_STATUS_ST *logger_global_button_status_pst = 0;
//const RELAY_STATUS_ST *logger_global_relay_status_pst = 0;
const ADC_VALUES_ST *logger_global_adc_values_pst = 0;
const DEF_TIME_ST *logger_global_time_pst = 0;
const DATACOLLECTION_RX_SERIAL_ST_DEF *logger_global_DataCollection_rx_serial_st = 0;

void Logger_Init_v(BUTTON_STATUS_ST *p_logger_global_button_status_pst,
		ADC_VALUES_ST *p_logger_global_adc_values_pst,
		DEF_TIME_ST *p_logger_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st
		) {
	logger_global_button_status_pst = p_logger_global_button_status_pst;
	logger_global_adc_values_pst = p_logger_global_adc_values_pst;
	logger_global_time_pst = p_logger_global_time_pst;
	logger_global_DataCollection_rx_serial_st = p_logger_DataCollection_rx_serial_st;

	Logger_sdw_Init_v();

	logger_global_button_status_pst = 0;
	logger_global_adc_values_pst = 0;
	logger_global_time_pst = 0;
	logger_global_DataCollection_rx_serial_st = 0;

}

void Logger_Main_1ms_v(BUTTON_STATUS_ST *p_logger_global_button_status_pst,
		ADC_VALUES_ST *p_logger_global_adc_values_pst,
		DEF_TIME_ST *p_logger_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st) {

	logger_global_button_status_pst = p_logger_global_button_status_pst;
	logger_global_adc_values_pst = p_logger_global_adc_values_pst;
	logger_global_time_pst = p_logger_global_time_pst;
	logger_global_DataCollection_rx_serial_st = p_logger_DataCollection_rx_serial_st;


	Logger_sdw_Main_T1_v();

	logger_global_button_status_pst = 0;
	logger_global_adc_values_pst = 0;
	logger_global_time_pst = 0;
	logger_global_DataCollection_rx_serial_st = 0;
}
void Logger_Main_10msLow_v(BUTTON_STATUS_ST *p_logger_global_button_status_pst,
		ADC_VALUES_ST *p_logger_global_adc_values_pst,
		DEF_TIME_ST *p_logger_global_time_pst,
		DATACOLLECTION_RX_SERIAL_ST_DEF *p_logger_DataCollection_rx_serial_st) {

	logger_global_button_status_pst = p_logger_global_button_status_pst;
	logger_global_adc_values_pst = p_logger_global_adc_values_pst;
	logger_global_time_pst = p_logger_global_time_pst;
	logger_global_DataCollection_rx_serial_st = p_logger_DataCollection_rx_serial_st;


	Logger_sdw_Main_T10Low_v();

	logger_global_button_status_pst = 0;
	logger_global_adc_values_pst = 0;
	logger_global_time_pst = 0;
	logger_global_DataCollection_rx_serial_st = 0;
}


void Logger_Main_10ms_v(void) {

	Logger_sdw_Main_T10_v();
}
