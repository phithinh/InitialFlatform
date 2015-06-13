/*
 * inverter_controller_cfg.h
 *
 *  Created on: May 6, 2015
 *      Author: Thinh
 */

#ifndef INVERTER_CONTROLLER_CFG_H_
#define INVERTER_CONTROLLER_CFG_H_

#define HWFAULTPROTECT
#define VDCPROTECT
#define TEMPPROTECT

#define IV_CTR_CYCLE					10	//ms
#define IV_CTR_LOADING_CAP_DURATION		1000	//ms
#define IV_CTR_SOFT_STARTING_DURATION	10000 //MS
#define IV_CTR_SOFT_STOPPING_DURATION	2000 //MS
#define IV_CTR_ADC_UPDATE_CYCLE			500	//ms
#define IV_CTR_SOFT_STARTING_CYCLE		100 //MS
#define IV_CTR_SOFT_STOPPING_CYCLE		20 //MS
#define IV_CTR_WAIT4RETRY				10000	//ms

#define IV_CTR_BLINK_LED				500	//ms

#define IV_CTR_MAX_DUTY	100

#define CUR_UP_THRESHOLD   (3.2*(4096/3.3))
#define CUR_LOW_THRESHOLD  (0.2*(4096/3.3))
////////////////////////////////////////////////
#define VOL_UP_THRESHOLD    (1.8*(4096/3.3))
#define VOL_LOW_THRESHOLD    (0.7*(4096/3.3))
//////////////////////////////////////////////////
#define TEMP_UP_THRESHOLD   (2.0*(4096/3.3))
#define TEMP_LOW_THRESHOLD  (0.45*(4096/3.3))

#define FEEDBACK_OFFSET     (0.03*(4096/3.3))

//#define VDCPROTECT
#define TEMPPROTECT
#define HWFAULTPROTECT

#define STARTCURTHRESHOLD      4000
#define CURR_AVG_SMOOTH 12000
#define HVDC_AVG_SMOOTH 5000
#define TEMP_AVG_SMOOTH 5000
/////////define for PID
#define OUT_MAX         1000
#define OUT_MIN         0
#define KP_EV			5// Tuong duong
#define KI_EV           0.5

#endif /* INVERTER_CONTROLLER_CFG_H_ */
