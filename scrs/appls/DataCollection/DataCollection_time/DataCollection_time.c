/*
 * DataCollection_time.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */
#include <compiler.h>
#include <rtc.h>

#include "DataCollection_time.h"
#include "../DataCollection_adapts.h"


//extern tm timer; // clock structure

void DataCollection_time_init_v(void) {
	RTC_Init();
	DataCollection_global_time_pst->sec = timer.sec;
	DataCollection_global_time_pst->min = timer.min;
	DataCollection_global_time_pst->hour = timer.hour;
	DataCollection_global_time_pst->day = timer.w_date;
	DataCollection_global_time_pst->mon = timer.w_month;
	DataCollection_global_time_pst->year = timer.w_year;
}

/*
 * Description:
 * 		- Detection the time changing
 * 		- Update the time
 */
void DataCollection_time_update_v(void) {
	DataCollection_global_time_pst->sec = timer.sec;
	DataCollection_global_time_pst->min = timer.min;
	DataCollection_global_time_pst->hour = timer.hour;
	DataCollection_global_time_pst->day = timer.w_date;
	DataCollection_global_time_pst->mon = timer.w_month;
	DataCollection_global_time_pst->year = timer.w_year;
}
void DataCollection_set_time_v(UBYTE hour, UBYTE min){
	timer.hour = hour;
	timer.min = min;
	RTC_Set(timer.w_year, timer.w_month, timer.w_date, timer.hour, timer.min,timer.sec);
}
void DataCollection_set_bk1_v(UWORD p_data_uw){
	BKP->DR2 = p_data_uw;
}
void DataCollection_set_bk2_v(UWORD p_data_uw){
	BKP->DR3 = p_data_uw;
}
UWORD DataCollection_read_bk1_v(void){
	return(BKP->DR2);
}
UWORD DataCollection_read_bk2_v(void){
	return(BKP->DR3);
}
