/*
 * environment.c
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */

#include <compiler.h>
#include <interfaces.h>

#include <digital_out_pub.h>
//#include <DataCollection_runnables.h>
//#include <UserIf.h>

#include "environment.h"

void environment_init_v(void) {
//	DataCollection_Init_v(global_adc_values_pst,
//					global_time_pst,
//					global_DataCollection_rx_serial_pst);
//	UserIf_Init();
  digital_out_init_v();
  digital_out_toggle_v (LED_OUT2);
}
unsigned char g_tick_test_ub;
void environment_T10_process_v(void) {

	//real time reading
//	DataCollection_Main_T10_v (global_time_pst,
//			global_adc_values_pst,
//			global_DataCollection_rx_serial_pst);

	//input reading
//	UserIf_Input_main();

	//processing
//	UserIf_Proc_main();

	//out put: relay
//	UserIf_Ouput_main();
  g_tick_test_ub++;
  if(g_tick_test_ub>50){
    g_tick_test_ub = 0;
    digital_out_toggle_v (LED_OUT1);
    digital_out_toggle_v (LED_OUT2);
    digital_out_toggle_v (LED_OUT3);
  }
}
void environment_T10Low_process_v(void){
	//lcd
//	UserIf_OuputLow_main();
}
