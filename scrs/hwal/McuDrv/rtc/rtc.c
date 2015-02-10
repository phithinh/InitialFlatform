/*
 * rtc.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */

#include <compiler.h>

#include <stm32f10x_rtc.h>
#include <stm32f10x_rcc.h>
#include <misc.h>

#include <rtc.h>
#include "rtc_cfg.h"

const u8 *COMPILED_DATE=__DATE__;//get the date of compilation
const u8 *COMPILED_TIME=__TIME__;//get compile time

tm timer; // clock structure
// Real-time clock configuration
// Initialize the RTC clock, the clock is working properly while testing
// BKP-> DR1 is the first time to save the configuration settings
// Returns 0: normal
// Other: error code
u8 RTC_Init(void) {
	uint32 Clk1S;
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset Backup Domain */
	//BKP_DeInit(); //??0XA5A5 ?????????

#ifdef USE_LSE
	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{}

	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	Clk1S = 32767;
#else
	/* Enable LSI */
	RCC_LSICmd(ENABLE);
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{}

	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

	Clk1S = 39999;
#endif
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(Clk1S); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	if (BKP->DR1 != 0X5050){ // for the first time configuration
		Auto_Time_Set();
		BKP->DR1 = 0X5050;
	}
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	RTC_Get(); // update
	return 0; // ok
}
// RTC interrupt service function
// Const u8 * Week [2] [7] =
// {
// {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"},
// {"Day" and "one" "two" "three", "four", "five", "six"}
//};
// RTC interrupt
// Trigger a second
// Extern u16 tcnt;
void RTC_IRQHandler(void) {
	// Static u16 last = 0;
	if (RTC->CRL & 0x0001) // second interrupt
			{
		RTC_Get(); // update
	}
	if (RTC->CRL & 0x0002) // clock interrupt
		{
		RTC->CRL &= ~(0x0002); // clear alarm interrupt
		// Alarm handling
	}
	RTC->CRL &= 0X0FFA; // clear the overflow, the second interrupt flag
	while (!(RTC->CRL & (1 << 5)))
		; // wait for completion of the RTC registers operating
}
// Function to determine whether it is a leap year
// Month 123,456,789,101,112
// Leap year 31 29 31 30 3,130,313,130,313,031
// Non-leap year 31 28 31 30 3,130,313,130,313,031
// Input: Year
// Output: This year is a leap year .1, .0 is not
u8 Is_Leap_Year(u16 year) {
	if (year % 4 == 0) // must be divisible by 4
			{
		if (year % 100 == 0) {
			if (year % 400 == 0)
				return 1; // end if 00, also divisible by 400
			else
				return 0;
		} else
			return 1;
	} else
		return 0;
}
// Set the clock
// Convert the input clock seconds
// To January 1, 1970 as the base
// 1970 to the year 2099 as a legal
// Return value: 0, success; others: error code.
// Month data table
u8 const table_week[12] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 }; // month revised data sheet
// Average year of the month table
const u8 mon_table[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
u8 RTC_Set(u16 syear, u8 smon, u8 sday, u8 hour, u8 min, u8 sec) {
	u16 t;
	u32 seccount = 0;
	if (syear < 1970 || syear > 2099)
		return 1;
	for (t = 1970; t < syear; t++) // sum of all second year
			{
		if (Is_Leap_Year(t))
			seccount += 31622400; // leap year the number of seconds
		else
			seccount += 31536000; //-average number of seconds
	}
	smon -= 1;
	for (t = 0; t < smon; t++) // the sum of the number of seconds the previous month
			{
		seccount += (u32) mon_table[t] * 86400; // add the number of seconds in January
		if (Is_Leap_Year(syear) && t == 1)
			seccount += 86400; // leap year day in February to increase the number of seconds
	}
	seccount += (u32) (sday - 1) * 86400; // the sum of the number of seconds in front of date
	seccount += (u32) hour * 3600; // h the number of seconds
	seccount += (u32) min * 60; // min number of seconds
	seccount += sec; // add to the final seconds

	// Set the clock
	RCC->APB1ENR |= 1 << 28; // Enable Clock Power
	RCC->APB1ENR |= 1 << 27; // Enable the clock back
	PWR->CR |= 1 << 8; // cancel the write-protect the backup area
	// The above three steps is a must!
	RTC->CRL |= 1 << 4; // allow configuration
	RTC->CNTL = seccount & 0xffff;
	RTC->CNTH = seccount >> 16;
	RTC->CRL &= ~(1 << 4); // configuration update
	while (!(RTC->CRL & (1 << 5)))
		; // wait for completion of the RTC registers operating
	return 0;
}
// Get the current time
// Return value: 0, success; others: error code.
u8 RTC_Get(void) {
	static u16 daycnt = 0;
	u32 timecount = 0;
	u32 temp = 0;
	u16 temp1 = 0;

	timecount = RTC->CNTH; // get counter values ??(second number)
	timecount <<= 16;
	timecount += RTC->CNTL;

	temp = timecount / 86400; // get the number of days (corresponding to the number of seconds)
	if (daycnt != temp) // more than one day a
			{
		daycnt = temp;
		temp1 = 1970; // since 1970.
		while (temp >= 365) {
			if (Is_Leap_Year(temp1)) // is a leap year
					{
				if (temp >= 366)
					temp -= 366; // leap year the number of seconds
				else {
					temp1++;
					break;
				}
			} else
				temp -= 365; // leap year
			temp1++;
		}
		timer.w_year = temp1; // get the year
		temp1 = 0;
		while (temp >= 28) // more than a month
		{
			if (Is_Leap_Year(timer.w_year) && temp1 == 1) // year is a leap year / February
					{
				if (temp >= 29)
					temp -= 29; // leap year the number of seconds
				else
					break;
			} else {
				if (temp >= mon_table[temp1])
					temp -= mon_table[temp1]; // leap year
				else
					break;
			}
			temp1++;
		}
		timer.w_month = temp1 + 1; // get the month
		timer.w_date = temp + 1; // get date
	}
	temp = timecount % 86400; // get the number of seconds
	timer.hour = temp / 3600; // hour
	timer.min = (temp % 3600) / 60; // min
	timer.sec = (temp % 3600) % 60; // seconds
	timer.week = RTC_Get_Week(timer.w_year, timer.w_month, timer.w_date); // get week
	return 0;
}
// Get now is the day of the week
// Description: Enter the calendar date to get a week (only 1901-2099 years)
// Input parameters: month, day calendar
// Return value: number of weeks
u8 RTC_Get_Week(u16 year, u8 month, u8 day) {
	u16 temp2;
	u8 yearH, yearL;

	yearH = year / 100;
	yearL = year % 100;
	// If the 21st century, the number of years and 100
	if (yearH > 19)
		yearL += 100;
	// Only count the number of leap years over after 1900
	temp2 = yearL + yearL / 4;
	temp2 = temp2 % 7;
	temp2 = temp2 + day + table_week[month - 1];
	if (yearL % 4 == 0 && month < 3)
		temp2--;
	return (temp2 % 7);
}
// Compare two strings are equal to the contents of a specified length
// Parameters: s1, s2 to compare two strings; len, compare the length of
// Return value: 1, equal; 0, not equal
u8 str_cmpx(u8 * s1, u8 * s2, u8 len) {
	u8 i;
	for (i = 0; i < len; i++)
		if ((*s1++) != *s2++)
			return 0;
	return 1;
}
extern const u8 * COMPILED_DATE; // get the date of compilation
extern const u8 * COMPILED_TIME; // get compile time
const u8 Month_Tab[12][3] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
		"Aug", "Sep", "Oct", "Nov", "Dec" };
// Compiler automatically sets the time for time
void Auto_Time_Set(void) {
	u8 temp[3];
	u8 i;
	u8 mon, date;
	u16 year;
	u8 sec, min, hour;
	for (i = 0; i < 3; i++)
		temp[i] = COMPILED_DATE[i];
	for (i = 0; i < 12; i++)
		if (str_cmpx((u8 *) Month_Tab[i], temp, 3))
			break;
	mon = i + 1; // get the month
	if (COMPILED_DATE[4] == ' ')
		date = COMPILED_DATE[5] - '0';
	else
		date = 10 * (COMPILED_DATE[4] - '0') + COMPILED_DATE[5] - '0';
	year = 1000 * (COMPILED_DATE[7] - '0') + 100 * (COMPILED_DATE[8] - '0')
			+ 10 * (COMPILED_DATE[9] - '0') + COMPILED_DATE[10] - '0';
	hour = 10 * (COMPILED_TIME[0] - '0') + COMPILED_TIME[1] - '0';
	min = 10 * (COMPILED_TIME[3] - '0') + COMPILED_TIME[4] - '0';
	sec = 10 * (COMPILED_TIME[6] - '0') + COMPILED_TIME[7] - '0';
	RTC_Set(year, mon, date, hour, min, sec);
}
