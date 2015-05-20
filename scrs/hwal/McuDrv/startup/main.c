/******************** (C) COPYRIGHT 2013 H3ElTeam ********************
* File Name          : main.c
* Author             : OS Team
* Date First Issued  : 20/09/2014
* Description        : 
********************************************************************************
* History: DD/MM/YY
* 20/09/2014: v0.1
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Include header file */
#include <misc.h>
#include <environment.h>
#include <OS.h>

#include <stm32f10x_rcc.h>


/* Prototype static function main source use */
static void vMCU_Init_Hardware( void );

/*-----------------------------------------------------------*/

/* Main source */
int main(void)
{
	/* Init hardware module for MCU*/
	vMCU_Init_Hardware();

	//create the task
	OS_Init();

	//calling OS scheduler
	OS_Start();
	return 1;
}

#pragma GCC diagnostic pop
/* Init clock, some function for MCU module */
static void vMCU_Init_Hardware( void )
{
	/* Init system clock */
//	SystemInit();
	/* Set the Vector Table base address at 0x08000000 */
	//NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x0 );
	//NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
	/* Configure HCLK clock as SysTick clock source. */
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	environment_init_v();
}
