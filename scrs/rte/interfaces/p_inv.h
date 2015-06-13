/*
 * p_inv.h
 *
 *  Created on: May 25, 2015
 *      Author: Thinh
 */

#ifndef P_INV_H_
#define P_INV_H_

typedef struct {
	UWORD LowVoltageDCThreshold_uw;
	UWORD HighVoltageDCThreshold_uw;
	UWORD LowIntensityThreshold_uw;
	UWORD HighIntensityThreshold_uw;
	UWORD LowTemperatureThreshold_uw;
	UWORD HighTemperatureThreshold_uw;
}INV_THRESHOLD_TDEF;

typedef struct {
	UWORD Average_Voltage_uw;
	UWORD Average_Intesity_uw;
	UWORD Average_Temp_uw;
	UWORD Current_Voltage_uw;
	UWORD Current_Intesity_uw;
	UWORD Current_Temp_uw;
}INV_SENSOR_FEEDBACK_TDEF;

#endif /* P_INV_H_ */
