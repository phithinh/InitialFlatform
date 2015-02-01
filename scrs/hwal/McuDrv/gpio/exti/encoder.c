/*
 * encoder.c
 *
 *  Created on: Mar 9, 2014
 *      Author: TV
 */

#include <stm32f10x_exti.h>
#include <stm32f10x_gpio.h>
#include <general_define.h>
#include <misc.h>
#include "../gpio_hardware_config.h"

struct {
	BOOL pre_statusA_b;
	BOOL pre_statusB_b;
	BOOL dir_status_b;
	SLONG value_sl;
} encoder_data_st;

void encoder_IRQ_A_Handler(void) {
	BOOL t_cur_staA_b,t_cur_staB_b,t_pre_sta_b;
	t_cur_staA_b = GPIO_phaseA_status_b;
	t_cur_staB_b = GPIO_phaseB_status_b;
	t_pre_sta_b = encoder_data_st.pre_statusA_b;
	if (t_cur_staA_b != t_pre_sta_b) {//trigger
		if (t_cur_staA_b^t_cur_staB_b){
			encoder_data_st.value_sl++;
			encoder_data_st.dir_status_b = TRUE;
		} else {
			encoder_data_st.value_sl--;
			encoder_data_st.dir_status_b = FALSE;
		}
	}
	//store the current status
	encoder_data_st.pre_statusA_b = t_cur_staA_b;
	encoder_data_st.pre_statusB_b = t_cur_staB_b;
}

void encoder_IRQ_B_Handler(void) {
	BOOL t_cur_staA_b,t_cur_staB_b,t_pre_sta_b;
	t_cur_staA_b = GPIO_phaseA_status_b;
	t_cur_staB_b = GPIO_phaseB_status_b;
	t_pre_sta_b = encoder_data_st.pre_statusB_b;
	if (t_cur_staB_b != t_pre_sta_b) {//trigger
		if (t_cur_staA_b^t_cur_staB_b){
			encoder_data_st.value_sl--;
			encoder_data_st.dir_status_b = FALSE;
		} else {
			encoder_data_st.value_sl++;
			encoder_data_st.dir_status_b = TRUE;
		}
	}
	//store the current status
	encoder_data_st.pre_statusA_b = t_cur_staA_b;
	encoder_data_st.pre_statusB_b = t_cur_staB_b;
}

