/*
 * inverter_controller.c
 *
 *  Created on: May 6, 2015
 *      Author: Thinh
 */


#include <general_define.h>

#include <string.h>

#include <SVPWM.h>
#include <ADC_DMA.h>
#include <FlashRW.h>
#include <MemoryMap.h>

#include "inverter_controller_cfg.h"
#include "inverter_controller_pub.h"
#include "inverter_controller_adapts.h"
#define _IV_CTR_M_
#include "inverter_controller_pri.h"

void inverter_controller_init_v(void) {
	unsigned short u16Count3;
	ADC_DMA_Init();
	SVPWMInit();
	
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	
	l_inverter_ctr_time_base = 0;
	l_inverter_ctr_fls_wrt_flag_b = FALSE;

	l_inverter_ctr_fault_vol_ub = FALSE;
	l_inverter_ctr_fault_i_ub = FALSE;
	l_inverter_ctr_fault_temp_ub = FALSE;
	l_inverter_ctr_fault_IGBT_ub = FALSE;

	///////////////////////////////////
	//RS485_DIR_SEND;
	//////////////////////////////////
	////////////////////////////EEprom test/////////////////////////////
	//  HWModuleTest();
	////////////////////////////////////////////////////////////////////
	memcpy(&FlashReadParameter[0],
			(uint32*) (FW_DECRIP_START_ADDR + 0 * PAGE_SIZE),
			sizeof(FlashReadParameter)); //page 0
	//T1Us_DelayMs(2000);
	//Todo: why?
	for (u16Count3 = 0; u16Count3 < 1024; u16Count3++) {
		FlashWriteParameter[u16Count3] = FlashReadParameter[u16Count3];
	}

	StrFeedbackThreshold.LowVoltageDCThreshold = (uint16) FlashWriteParameter[0]
			+ (uint16) FlashWriteParameter[1] * 256;

	StrFeedbackThreshold.HighVoltageDCThreshold =
			(uint16) FlashWriteParameter[2]
					+ (uint16) FlashWriteParameter[3] * 256;

	StrFeedbackThreshold.LowCurrentThreshold = (uint16) FlashWriteParameter[4]
			+ (uint16) FlashWriteParameter[5] * 256;

	StrFeedbackThreshold.HighCurrentThreshold = (uint16) FlashWriteParameter[6]
			+ (uint16) FlashWriteParameter[7] * 256;

	inverter_ctr_preinit_entry_v();

	//update the local variables to VDB
	VDB_INV_LowVoltageDCThreshold_uw  	= StrFeedbackThreshold.LowVoltageDCThreshold;
	VDB_INV_HighVoltageDCThreshold_uw 	= StrFeedbackThreshold.HighVoltageDCThreshold;
	VDB_INV_LowIntensityThreshold_uw  	= StrFeedbackThreshold.LowCurrentThreshold;
	VDB_INV_HighIntensityThreshold_uw 	= StrFeedbackThreshold.HighCurrentThreshold;
	VDB_INV_LowTemperatureThreshold_uw 	= (UWORD)TEMP_LOW_THRESHOLD;
	VDB_INV_HighTemperatureThreshold_uw	= (UWORD)TEMP_UP_THRESHOLD;
}
void inverter_controller_main_v(void) {
	l_inverter_ctr_time_base += IV_CTR_CYCLE;

	inverter_controller_mon_v();

	switch (inverter_controller_sta) {
	case IV_CTR_RUNNING:
		if (l_inverter_ctr_stop_requested_b){
			inverter_ctr_soft_stopping_entry_v();
		}
		break;
	case IV_CTR_SOFT_START:
		inverter_controller_soft_starting_v();
		if (u16AvgCurrent >= STARTCURTHRESHOLD) {
			l_inverter_ctr_fault_i_ub = TRUE;
			inverter_ctr_soft_stopping_entry_v();
		}
		if (l_inverter_ctr_sm_doneflag_b) {
			if (!DipSw2) {
				if (DipSw1) {
					inverter_ctr_i_calib_entry_v();
				} else {
					inverter_ctr_running_entry_v();
				}
			} else {
				inverter_ctr_soft_stopping_entry_v();
			}
		}
		break;
	case IV_CTR_SOFT_STOP:
		inverter_controller_soft_stopping_v();
		
		//condition
		if (l_inverter_ctr_sm_doneflag_b) {
			if (l_inverter_ctr_fls_wrt_flag_b) {
				inverter_ctr_fls_write_entry_v();
			}
			if ((l_inverter_ctr_fault_vol_ub)
					&& ((l_inverter_ctr_time_base - l_inverter_ctr_time_stamp)
							> IV_CTR_WAIT4RETRY)
					&& ((IV_CTR_SOFT_START == inverter_controller_pre_sta)
							|| (IV_CTR_RUNNING == inverter_controller_pre_sta))) {
				l_inverter_ctr_fault_vol_ub = FALSE; //clear fault
				inverter_ctr_soft_start_entry_v();
			} else if ((!l_inverter_ctr_fault_i_ub)
					&&(!l_inverter_ctr_fault_temp_ub)
					&&(!l_inverter_ctr_fault_IGBT_ub)
					&&(l_inverter_ctr_start_requested_b)){
				inverter_ctr_soft_start_entry_v();
			}
		}
		//Malfunction indicator lamp - diagnostic
		if ((l_inverter_ctr_time_base - l_inverter_ctr_mil_time_stamp)
							> IV_CTR_BLINK_LED){
			l_inverter_ctr_mil_time_stamp = l_inverter_ctr_time_base;
			if(l_inverter_ctr_fault_vol_ub){
				//LED1_TOG;
				//LED2_TOG;
			} else if (l_inverter_ctr_fault_i_ub){
				LED1_TOG;
				if (IV_CTR_SOFT_START == inverter_controller_pre_sta){
					LED2_OFF;
				} else {
					LED2_ON;
				}
			} else if (l_inverter_ctr_fault_temp_ub){
				LED1_OFF;
				LED2_TOG;
			} else if (l_inverter_ctr_fault_IGBT_ub){
				LED1_ON;
				LED2_TOG;
			} else if ((IV_CTR_CALIB_I == inverter_controller_pre_sta)
                  ||(IV_CTR_CALIB_VOLT == inverter_controller_pre_sta)){
				LED1_TOG;
				LED2_TOG;
			}
		}
		
		break;
	case IV_CTR_CALIB_VOLT:
		inverter_controller_vol_calibration_v();
		if (TRUE == l_inverter_ctr_sm_doneflag_b) {
			inverter_ctr_vol_calib_exit_v();
			inverter_ctr_soft_stopping_entry_v();
		}
		break;
	case IV_CTR_CALIB_I:
		inverter_controller_intensity_calibration_v();
		if (TRUE == l_inverter_ctr_sm_doneflag_b) {
			inverter_ctr_i_calib_exit_v();
			inverter_ctr_soft_stopping_entry_v();
		}
		break;
	case IV_CTR_INIT:
		//check condition
		if (DipSw1 == TRUE) {
			if (DipSw2 == TRUE) {
				//do nothing
			} else {
				inverter_ctr_soft_start_entry_v();
			}
		} else {
			if (DipSw2 == TRUE) {
				inverter_ctr_vol_calib_entry_v();
			} else {
				if (l_inverter_ctr_start_requested_b){
					inverter_ctr_soft_start_entry_v();
				}
			}
		}
		break;
	case IV_CTR_PRE_INIT:
		//check condition
		if ((l_inverter_ctr_time_base - l_inverter_ctr_time_stamp)
				> IV_CTR_LOADING_CAP_DURATION) {
			if (TRUE == l_inverter_ctr_high_vol_cap_sta_b) { //after relay on by 2s
				inverter_ctr_init_entry_v();
			}
			RELAY_ON; //disable high voltage capacities
			l_inverter_ctr_high_vol_cap_sta_b = TRUE;
		}
		break;
	case IV_CTR_UNINIT:
	case IV_CTR_FLS_LOGGING:
	default:
		break;
	}
	
	VDB_INV_LowVoltageDCThreshold_uw  	= StrFeedbackThreshold.LowVoltageDCThreshold;
	VDB_INV_HighVoltageDCThreshold_uw 	= StrFeedbackThreshold.HighVoltageDCThreshold;
	VDB_INV_LowIntensityThreshold_uw  	= StrFeedbackThreshold.LowCurrentThreshold;
	VDB_INV_HighIntensityThreshold_uw 	= StrFeedbackThreshold.HighCurrentThreshold;
	VDB_INV_LowTemperatureThreshold_uw 	= (UWORD)TEMP_LOW_THRESHOLD;
	VDB_INV_HighTemperatureThreshold_uw	= (UWORD)TEMP_UP_THRESHOLD;

	VDB_INV_Average_Voltage_uw   = u16AvgVol;
	VDB_INV_Average_Intesity_uw  = u16AvgCurrent;
	VDB_INV_Average_Temp_uw      = u16AvgTemp;
	VDB_INV_Current_Voltage_uw   = StrAnalog.u16HVDC;
	VDB_INV_Current_Intesity_uw  = StrAnalog.u16DcCurrent;
	VDB_INV_Current_Temp_uw      = StrAnalog.u16Temp;
}
void inverter_ctr_preinit_entry_v(void) {
	RELAY_OFF;
	l_inverter_ctr_high_vol_cap_sta_b = FALSE;
	l_inverter_ctr_time_stamp = l_inverter_ctr_time_base;
	inverter_controller_sta = IV_CTR_PRE_INIT;
}
void inverter_ctr_init_entry_v(void) {
	inverter_controller_sta = IV_CTR_INIT;
}
void inverter_ctr_soft_start_entry_v(void) {
	l_inverter_ctr_request_duty_uw = 0;
	inverter_controller_sta = IV_CTR_SOFT_START;
}
void inverter_ctr_vol_calib_entry_v(void) {
	LED1_ON;
	LED2_OFF;
	inverter_controller_sta = IV_CTR_CALIB_VOLT;
}
void inverter_ctr_i_calib_entry_v(void) {
	LED2_ON;
	LED1_OFF;
	inverter_controller_sta = IV_CTR_CALIB_I;
}
void inverter_ctr_running_entry_v(void) {
	LED1_ON;
	LED2_ON;
	inverter_controller_sta = IV_CTR_RUNNING;
}
void inverter_ctr_soft_stopping_entry_v(void) {
	l_inverter_ctr_time_stamp = l_inverter_ctr_time_base;
	inverter_controller_pre_sta = inverter_controller_sta;
	inverter_controller_sta = IV_CTR_SOFT_STOP;
}
void inverter_ctr_vol_calib_exit_v(void) {
	inverter_controller_pre_sta = inverter_controller_sta;
}
void inverter_ctr_i_calib_exit_v(void) {
	inverter_controller_pre_sta = inverter_controller_sta;
}
void inverter_ctr_fls_write_entry_v(void) {
	inverter_controller_sta = IV_CTR_FLS_LOGGING;
	SaveSysParameter((SYS_PARAMETER*) &FlashWriteParameter[0], 0);
	l_inverter_ctr_fls_wrt_flag_b = FALSE;	// writing is done
}
/*
 * =====================================================
 * =============== FEATURE: MONINTORING ================
 * =====================================================
 * */
void inverter_controller_mon_v(void) {
/////////////////////////////////////////////////////////////
	ReadAnalogInput();
	if ((l_inverter_ctr_time_base - l_inverter_ctr_sample_time_stamp)
			> IV_CTR_ADC_UPDATE_CYCLE) {
		l_inverter_ctr_sample_time_stamp = l_inverter_ctr_time_base;
		u16AvgCurrent = AverageCurrent(StrAnalog.u16DcCurrent, CURR_AVG_SMOOTH);
		u16AvgVol = AverageVdc(StrAnalog.u16HVDC, HVDC_AVG_SMOOTH);
		u16AvgTemp = AverageTemp(StrAnalog.u16Temp, TEMP_AVG_SMOOTH);
	}
#ifdef HWFAULTPROTECT
	if (SDIn == FALSE) {
		l_inverter_ctr_fault_IGBT_ub = TRUE;
		inverter_ctr_soft_stopping_entry_v();
	}
#endif
#ifdef VDCPROTECT
	if((u16AvgVol<=(StrFeedbackThreshold.LowVoltageDCThreshold-FEEDBACK_OFFSET))
       ||(u16AvgVol>=(StrFeedbackThreshold.HighVoltageDCThreshold+FEEDBACK_OFFSET)))
	{
		l_inverter_ctr_fault_vol_ub = TRUE;
		inverter_ctr_soft_stopping_entry_v();
	}
#endif

#ifdef TEMPPROTECT
	if ((u16AvgTemp <= TEMP_LOW_THRESHOLD)
			|| (u16AvgTemp >= TEMP_UP_THRESHOLD)) {
		l_inverter_ctr_fault_temp_ub = TRUE;
		inverter_ctr_soft_stopping_entry_v();
	}
#endif

//intensity current monitoring is mandatory
	if ((u16AvgCurrent
			<= (StrFeedbackThreshold.LowCurrentThreshold - FEEDBACK_OFFSET))
			|| (u16AvgCurrent
					>= StrFeedbackThreshold.HighCurrentThreshold
							+ FEEDBACK_OFFSET)) {
		l_inverter_ctr_fault_i_ub = TRUE;
		inverter_ctr_soft_stopping_entry_v();
		;
	}
}
uint16 AverageCurrent(uint16 Value, uint16 Smooth) {
	static uint16 count;
	static uint32 u32Value;
	static uint32 u32OldValue;
	u32Value += Value;
	count++;
	if (count >= Smooth) {
		u32OldValue = u32Value / (uint32) count;
		u32Value = 0;
		count = 0;
		return (uint16) u32OldValue;
	} else
		return (uint16) u32OldValue;
}

uint16 AverageVdc(uint16 Value, uint16 Smooth) {
	static uint16 count;
	static uint32 u32Value;
	static uint32 u32OldValue;
	u32Value += Value;
	count++;
	if (count >= Smooth) {
		u32OldValue = u32Value / (uint32) count;
		u32Value = 0;
		count = 0;
		return (uint16) u32OldValue;
	} else
		return (uint16) u32OldValue;
}

uint16 AverageTemp(uint16 Value, uint16 Smooth) {
	static uint16 count;
	static uint32 u32Value;
	static uint32 u32OldValue;
	u32Value += Value;
	count++;
	if (count >= Smooth) {
		u32OldValue = u32Value / (uint32) count;
		u32Value = 0;
		count = 0;
		return (uint16) u32OldValue;
	} else
		return (uint16) u32OldValue;
}
/*
 * =====================================================
 * =============== FEATURE: CALIBRATION ================
 * =====================================================
 * */
void inverter_controller_vol_calibration_v(void) {
//Low voltage
	l_inverter_ctr_calib_doneflag_b = FALSE;
	if (Btn1 == FALSE) {
		FlashWriteParameter[1] = (u16AvgVol & 0xFF00) >> 8; //Byte cao
		FlashWriteParameter[0] = (u16AvgVol & 0x00FF); //Byte thap
		l_inverter_ctr_calib_doneflag_b = TRUE;
		l_inverter_ctr_fls_wrt_flag_b = TRUE;
	}
//High voltage
	if (Btn2 == FALSE) {
		FlashWriteParameter[3] = (u16AvgVol & 0xFF00) >> 8; //Byte cao
		FlashWriteParameter[2] = (u16AvgVol & 0x00FF); //Byte thap
		l_inverter_ctr_calib_doneflag_b = TRUE;
		l_inverter_ctr_fls_wrt_flag_b = TRUE;
	}
}
void inverter_controller_intensity_calibration_v(void) {
	l_inverter_ctr_calib_doneflag_b = FALSE;
//Low Current
	if (Btn1 == FALSE) {
		FlashWriteParameter[5] = (u16AvgCurrent & 0xFF00) >> 8; //Byte cao
		FlashWriteParameter[4] = (u16AvgCurrent & 0x00FF); //Byte thap
		l_inverter_ctr_calib_doneflag_b = TRUE;
		l_inverter_ctr_fls_wrt_flag_b = TRUE;
	}
//High Current
	if (Btn2 == FALSE) {
		FlashWriteParameter[7] = (u16AvgCurrent & 0xFF00) >> 8; //Byte cao
		FlashWriteParameter[6] = (u16AvgCurrent & 0x00FF); //Byte thap
		l_inverter_ctr_calib_doneflag_b = TRUE;
		l_inverter_ctr_fls_wrt_flag_b = TRUE;
	}
}
/*
 * =====================================================
 * =============== FEATURE: SOFT MODE ==================
 * =====================================================
 * */
//Motor soft starting
//	+ duty will be increased per 100ms and during 10s
//	+ during soft starting is proceed, if the averaged current exceed threshold, 
//  the motor will be stopped with soft mode (soft stopping)
void inverter_controller_soft_starting_v(void) {
	unsigned short t_counter_uw;

	l_inverter_ctr_sm_doneflag_b = FALSE;
	t_counter_uw = IV_CTR_SOFT_STARTING_DURATION / IV_CTR_SOFT_STARTING_CYCLE;
	l_inverter_ctr_request_duty_uw = SVPWM.ModulIndex;
///Khoi dong tu tu dong co tu 1-->100 - Sau moi lan tick
	if ((l_inverter_ctr_time_base - l_inverter_ctr_time_stamp)
			> IV_CTR_SOFT_STARTING_CYCLE) {
		UpdateSpeedMotor(l_inverter_ctr_request_duty_uw);
		if ((l_inverter_ctr_request_duty_uw < t_counter_uw)
				&& (l_inverter_ctr_request_duty_uw < IV_CTR_MAX_DUTY)) {
			l_inverter_ctr_request_duty_uw++;
		}
		l_inverter_ctr_time_stamp = l_inverter_ctr_time_base;
	}

//duty is equal 100 means starting up is done
	if (SVPWM.ModulIndex == 100) {
		l_inverter_ctr_sm_doneflag_b = TRUE;
	}
}
//Motor soft stopping
//	+ duty will be decreased per 20ms and during 2s
void inverter_controller_soft_stopping_v(void) {
//Soft Stop tu Module Index tru xuong ve den 0
	l_inverter_ctr_sm_doneflag_b = FALSE;
	l_inverter_ctr_request_duty_uw = SVPWM.ModulIndex;
	if ((l_inverter_ctr_request_duty_uw >= 0)
			&& (l_inverter_ctr_request_duty_uw <= 100)) {
		if ((l_inverter_ctr_time_base - l_inverter_ctr_time_stamp)
				> IV_CTR_SOFT_STOPPING_CYCLE) {
			UpdateSpeedMotor(l_inverter_ctr_request_duty_uw);
			l_inverter_ctr_request_duty_uw--;
			l_inverter_ctr_time_stamp = l_inverter_ctr_time_base;
		}
	} else if (l_inverter_ctr_request_duty_uw > 100) {
		l_inverter_ctr_request_duty_uw = 100;
		UpdateSpeedMotor(l_inverter_ctr_request_duty_uw);
	} else {
		SVPWM.StopEmer = 1;
		l_inverter_ctr_sm_doneflag_b = TRUE;
	}
}

#undef _IV_CTR_M_

