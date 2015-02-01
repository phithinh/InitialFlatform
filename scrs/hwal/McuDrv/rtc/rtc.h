/*
 * rtc.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */

#ifndef RTC_H_
#define RTC_H_
typedef struct{
	void (* rtc_indicate_v)(void);
}DEF_RTC_CONFIG;

extern DEF_RTC_CONFIG rtc_Config_st;
void RTC_Configuration(void);


// Time structure
typedef struct
{
	u16 w_year;
	u8 hour;
	u8 min;
	u8 sec;
	// Calendar week month year
	u8 w_month;
	u8 w_date;
	u8 week;
}tm;
extern tm timer;

extern u8 const mon_table [12]; // day of the month table
void Disp_Time (u8 x, u8 y, u8 size); // display the time in the development of position
void Disp_Week (u8 x, u8 y, u8 size, u8 lang); // shows a week at the specified location
u8 RTC_Init (void); // initialize the RTC, return 0, failure; a success;
u8 Is_Leap_Year (u16 year); // leap year, leap year to determine
u8 RTC_Get (void); // update time
u8 RTC_Get_Week (u16 year, u8 month, u8 day);
u8 RTC_Set (u16 syear, u8 smon, u8 sday, u8 hour, u8 min, u8 sec); // set time
void Auto_Time_Set (void); // set the time to compile-time



#endif /* RTC_H_ */
