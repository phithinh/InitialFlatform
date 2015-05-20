/*
 * inverter_controller_pri.h
 *
 *  Created on: May 16, 2015
 *      Author: Thinh
 */

#ifndef INVERTER_CONTROLLER_PRI_H_
#define INVERTER_CONTROLLER_PRI_H_

#ifdef _IV_CTR_M_
#define EXTERN	extern
#else
#define EXTERN
#endif
//////////////////////////////////////////////////////////////////////////
EXTERN uint16 u16AvgCurrent;
EXTERN uint16 u16AvgVol;
EXTERN uint16 u16AvgTemp;

typedef struct {
	uint16 LowCurrentThreshold;
	uint16 HighCurrentThreshold;
	uint16 LowVoltageDCThreshold;
	uint16 HighVoltageDCThreshold;
} _StrFeedbackThreshold;

EXTERN _StrFeedbackThreshold StrFeedbackThreshold;

EXTERN uint8 FlashWriteParameter[1024];
EXTERN uint8 FlashReadParameter[1024];
//todo: why we need 2 page

EXTERN signed short l_inverter_ctr_request_duty_uw;
EXTERN signed short l_inverter_ctr_time_base;
EXTERN signed short l_inverter_ctr_time_stamp;
EXTERN signed short l_inverter_ctr_sample_time_stamp;
EXTERN signed short l_inverter_ctr_mil_time_stamp;

EXTERN unsigned short l_inverter_ctr_tx_com_timer;

EXTERN unsigned char l_inverter_ctr_high_vol_cap_sta_b;
EXTERN unsigned char l_inverter_ctr_sm_doneflag_b;
EXTERN unsigned char l_inverter_ctr_calib_doneflag_b;
EXTERN unsigned char l_inverter_ctr_fls_wrt_flag_b;	//flash writing request flash

EXTERN unsigned char l_inverter_ctr_fault_vol_ub;	//voltage fault
EXTERN unsigned char l_inverter_ctr_fault_i_ub;	//intensity fault
EXTERN unsigned char l_inverter_ctr_fault_temp_ub;	//temperature fault
EXTERN unsigned char l_inverter_ctr_fault_IGBT_ub;	//temperature IGBT

EXTERN enum {
	IV_CTR_UNINIT = 0,
	IV_CTR_PRE_INIT,
	IV_CTR_INIT,
	IV_CTR_CALIB_VOLT,
	IV_CTR_CALIB_I,
	IV_CTR_SOFT_START,
	IV_CTR_RUNNING,
	IV_CTR_SOFT_STOP,
	IV_CTR_FLS_LOGGING,
} inverter_controller_sta;
EXTERN unsigned char inverter_controller_pre_sta;

void inverter_ctr_preinit_entry_v(void);
void inverter_ctr_init_entry_v(void);
void inverter_ctr_soft_start_entry_v(void);
void inverter_ctr_vol_calib_entry_v(void);
void inverter_ctr_i_calib_entry_v(void);
void inverter_ctr_running_v(void);
void inverter_ctr_soft_stopping_v(void);
void inverter_ctr_vol_calib_exit_v(void);
void inverter_ctr_i_calib_exit_v(void);
void inverter_ctr_fls_write_v(void);

void inverter_controller_mon_v(void);
uint16 AverageCurrent(uint16 Value, uint16 Smooth);
uint16 AverageVdc(uint16 Value, uint16 Smooth);
uint16 AverageTemp(uint16 Value, uint16 Smooth);

void inverter_controller_vol_calibration_v(void);
void inverter_controller_intensity_calibration_v(void);

void inverter_controller_soft_starting_v(void);
void inverter_controller_soft_stopping_v(void);
#endif /* INVERTER_CONTROLLER_PRI_H_ */
