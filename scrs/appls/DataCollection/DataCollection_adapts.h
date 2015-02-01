/*
 * DataCollection_adapts.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */

#ifndef DATACOLLECTION_ADAPTS_H_
#define DATACOLLECTION_ADAPTS_H_

#include <interfaces.h>

extern ADC_VALUES_ST *DataCollection_global_adc_values_pst;
extern DEF_TIME_ST *DataCollection_global_time_pst;

extern DATACOLLECTION_RX_SERIAL_ST_DEF *DataCollection_global_DataCollection_rx_serial_st;

#define VDB_DataCollection_rx_serial_data_aub		DataCollection_global_DataCollection_rx_serial_st->data_aub
#define VDB_DataCollection_rx_serial_status 		DataCollection_global_DataCollection_rx_serial_st->status
#define VDB_DataCollection_rx_serial_idx_ub			DataCollection_global_DataCollection_rx_serial_st->data_cnt_ub

#endif /* DATACOLLECTION_ADAPTS_H_ */
