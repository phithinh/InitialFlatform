/*
 * systick.c
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */
#define __SYSTICK
#include "systick.h"
#include "stm32f10x.h"
//#include "stm32f10x_it.h"

void systick_init(void){
	SysTick_Config(SystemCoreClock / 100000);
}

void SysTick_Handler(void)
{
	g_systick_sl++;
}
