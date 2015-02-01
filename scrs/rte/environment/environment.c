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
UBYTE tgl_1, tgl_2, tgl_3;
UWORD timer_uw, button_cnt1='!';
void environment_T10_process_v(void) {

	//real time reading
	DataCollection_Main_T10_v (global_time_pst,
			global_adc_values_pst,
			global_DataCollection_rx_serial_pst);

	//input reading
	UserIf_Input_main();

	//processing
	lcd_write(0,button_cnt1);
	lcd_write(1,0);

	//clock demonstration
	lcd_write(2,global_time_pst->min/10 +'0');
	lcd_write(3,global_time_pst->min%10 +'0');
	if(global_time_pst->sec%2){
		lcd_write(4,':');
	}else{
		lcd_write(4,0);
	}
	lcd_write(5,global_time_pst->sec/10 +'0');
	lcd_write(6,global_time_pst->sec%10 +'0');
	lcd_write(7,0);

	//button state reading
	if (button_scan_readButtonSta_ub(0)){
		button_cnt1++;
		tgl_1 = !tgl_1;
	}
	if (button_scan_readButtonSta_ub(1)){
		button_cnt1--;
		tgl_2 = !tgl_2;
	}
	if (timer_uw++>1000){
		tgl_3 = !tgl_3;
		timer_uw = 0;
	}
	relay_set(0,tgl_1);
	relay_set(1,tgl_2);
	relay_set(2,tgl_3);
	//out put: relay
	UserIf_Ouput_main();
}
void environment_T10Low_process_v(void){
	//lcd
	UserIf_OuputLow_main();
}
