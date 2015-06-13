/*
 * inverter_adpts.h
 *
 *  Created on: May 17, 2015
 *      Author: Thinh
 */

#ifndef NET_ADPTS_H_
#define NET_ADPTS_H_

#include <interfaces.h>

#ifdef __INV_MAIN
#define EXTERN
#else
#define EXTERN	extern
#endif

EXTERN INV_THRESHOLD_TDEF *inv_inv_threshold_pst;
EXTERN INV_SENSOR_FEEDBACK_TDEF *inv_inv_sensor_feedback_pst;

#define VDB_INV_LowVoltageDCThreshold_uw	inv_inv_threshold_pst->LowVoltageDCThreshold_uw
#define VDB_INV_HighVoltageDCThreshold_uw	inv_inv_threshold_pst->HighVoltageDCThreshold_uw
#define VDB_INV_LowIntensityThreshold_uw	inv_inv_threshold_pst->LowIntensityThreshold_uw
#define VDB_INV_HighIntensityThreshold_uw	inv_inv_threshold_pst->HighIntensityThreshold_uw
#define VDB_INV_LowTemperatureThreshold_uw		inv_inv_threshold_pst->LowTemperatureThreshold_uw
#define VDB_INV_HighTemperatureThreshold_uw		inv_inv_threshold_pst->HighTemperatureThreshold_uw

#define VDB_INV_Average_Voltage_uw			inv_inv_sensor_feedback_pst->Average_Voltage_uw
#define VDB_INV_Average_Intesity_uw			inv_inv_sensor_feedback_pst->Average_Intesity_uw
#define VDB_INV_Average_Temp_uw				inv_inv_sensor_feedback_pst->Average_Temp_uw
#define VDB_INV_Current_Voltage_uw			inv_inv_sensor_feedback_pst->Current_Voltage_uw
#define VDB_INV_Current_Intesity_uw			inv_inv_sensor_feedback_pst->Current_Intesity_uw
#define VDB_INV_Current_Temp_uw				inv_inv_sensor_feedback_pst->Current_Temp_uw

#undef EXTERN
#endif /* NET_ADPTS_H_ */
