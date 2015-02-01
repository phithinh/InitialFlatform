
#ifndef LOGGER_ADAPTS_H
#define LOGGER_ADAPTS_H
#include <interfaces.h>

extern const BUTTON_STATUS_ST *logger_global_button_status_pst;
extern const RELAY_STATUS_ST *logger_global_relay_status_pst;
extern const ADC_VALUES_ST *logger_global_adc_values_pst;
extern const DEF_TIME_ST *logger_global_time_pst;
extern const DATACOLLECTION_RX_SERIAL_ST_DEF *logger_global_DataCollection_rx_serial_st;

#define VDB_DataCollection_rx_serial_data_aub		logger_global_DataCollection_rx_serial_st->data_aub
#define VDB_DataCollection_rx_serial_status 		logger_global_DataCollection_rx_serial_st->status
#define VDB_DataCollection_rx_serial_cnt_ub			logger_global_DataCollection_rx_serial_st->data_cnt_ub

#define Now	logger_global_time_pst

#endif
