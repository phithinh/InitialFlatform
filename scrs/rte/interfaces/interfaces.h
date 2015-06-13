/*
 * interface.h
 *
 *  Created on: Apr 19, 2014
 *      Author: TV
 */

#ifndef INTERFACES_H_
#define INTERFACES_H_
#include "p_com_tx.h"
#include "p_inv.h"

#ifdef __INTERFACES_
#define EXTERN
#else
#define EXTERN	extern
#endif

EXTERN NET_TX_DATA_REQUEST_TDEF net_tx_data_request_st;
EXTERN NET_TX_CTR_REQUEST_TDEF net_tx_ctr_request_st;

EXTERN INV_THRESHOLD_TDEF inv_threshold_st;
EXTERN INV_SENSOR_FEEDBACK_TDEF inv_sensor_feedback_st;

#undef EXTERN
#endif /* INTERFACES_H_ */
