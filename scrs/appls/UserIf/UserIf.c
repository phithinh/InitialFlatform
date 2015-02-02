/*
 * UserIf_runnables.c
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */

#include <general_define.h>
#include <relay_controller.h>
#include <interfaces.h>
#include <UserIf.h>
#include <button_input_pub.h>
#include <main_process_pub.h>
#include <string.h>
#include <stdio.h>


void UserIf_Init(void){
	button_scan_init_v();
	main_init_v();
}

void UserIf_Input_main(void){
	button_scan_main_v();
}

void UserIf_Ouput_main(void){
	relay_main();
}

void UserIf_Proc_main(void)
{

	char t_buf1_aub[16];
	char t_buf2_aub[16];
	char t_buf3_aub[16];
	char t_buf4_aub[16];
	int lentop, lenbot;
	sprintf(t_buf1_aub, "%d : %d : %d ", global_time_pst->hour, global_time_pst->min, global_time_pst->sec);
	strcpy(t_buf2_aub, "Hello Sweet <3");

	button_get_event_v();

	main_process_v();
	lentop=strlen(main_cmd_top);
	lenbot=strlen(main_cmd_bot);

	strcpy(t_buf3_aub, main_cmd_top);
	strcpy(t_buf4_aub, main_cmd_bot);
	memset(t_buf3_aub+lentop, 0, 16-lentop);
	memset(t_buf4_aub+lenbot, 0, 16-lenbot);
	lcd_write_str_v(0, t_buf1_aub, 16);
	lcd_write_str_v(1, t_buf2_aub, 16);
	lcd_write_str_v(2, t_buf3_aub, 16);
	lcd_write_str_v(3, t_buf4_aub, 16);



}

void UserIf_OuputLow_main(void){
	static UBYTE delay_time = 0;
	if (delay_time<50){
		OLED_DC_Set();
		OLED_CS_Set();
		delay_time++;
	}else if (delay_time == 50){
		delay_time++;
		lcd_init();
	}else{
		lcd_main();
	}
}
