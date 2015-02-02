/*
 * environment.c
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */

#include <compiler.h>
#include <interfaces.h>

#include <DataCollection_runnables.h>
#include <UserIf.h>

#include "environment.h"

void environment_init_v(void) {
	DataCollection_Init_v(global_adc_values_pst,
					global_time_pst,
					global_DataCollection_rx_serial_pst);
	UserIf_Init();
}

void environment_T10_process_v(void) {

	//real time reading
	DataCollection_Main_T10_v (global_time_pst,
			global_adc_values_pst,
			global_DataCollection_rx_serial_pst);

	//input reading
	UserIf_Input_main();

	//processing
	UserIf_Proc_main();

	//out put: relay
	UserIf_Ouput_main();
}
void environment_T10Low_process_v(void){
	//lcd
	UserIf_OuputLow_main();
}
