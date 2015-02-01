/*
 * pwm.c
 *
 *  Created on: Mar 14, 2014
 *      Author: TV
*/
/* -----------------------------------------------------------------------
	TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
	The TIM3CLK frequency is set to SystemCoreClock (Hz), to get TIM3 counter
	clock at 24 MHz the Prescaler is computed as following:
	 - Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
	and Connectivity line devices and to 24 MHz for Low-Density Value line and
	Medium-Density Value line devices

	The TIM3 is running at 36 KHz: TIM3 Frequency = TIM3 counter clock/(ARR + 1)
												  = 24 MHz / 666 = 36 KHz
	TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 
	TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100
	TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100
	TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100
----------------------------------------------------------------------- */
#include <stm32f10x_tim.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x.h>

#include "pwm_pri.h"
#include "pwm_conf.h"
#include "general_define.h"
 void PWM_init_v(void){  
	/* System Clocks Configuration */
	PWM_RCC_Configuration_v();
	/* GPIO Configuration */
	PWM_GPIO_Configuration_v();
	/*initialize 4 OC channel*/
	PWM_Channel_1_Init();
	PWM_Channel_2_Init();
	PWM_Channel_3_Init();
	PWM_Channel_4_Init();
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}
/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void PWM_RCC_Configuration_v(void)
{
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* GPIOA and GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
#if (defined PWM_USE_CHANNEL_1)|(defined PWM_USE_CHANNEL_2)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#endif
#if (defined PWM_USE_CHANNEL_3)|(defined PWM_USE_CHANNEL_4)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
#endif
}
 /**
  * @brief  Configure the TIM3 Ouput Channels.
  * @param  None
  * @retval None
  */
void PWM_GPIO_Configuration_v(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* GPIOA Configuration:TIM3 Channel1, 2, 3 and 4 as alternate function push-pull */
#if	(defined PWM_USE_CHANNEL_1)|(defined PWM_USE_CHANNEL_2)
  GPIO_InitStructure.GPIO_Pin = NULL_UW;
#ifdef PWM_USE_CHANNEL_1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
#endif
#ifdef PWM_USE_CHANNEL_2
  GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_7;
#endif
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#if (defined PWM_USE_CHANNEL_3)|(defined PWM_USE_CHANNEL_4)
  GPIO_InitStructure.GPIO_Pin = NULL_UW;
#ifdef PWM_USE_CHANNEL_3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
#endif
#ifdef PWM_USE_CHANNEL_4
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
#endif
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
}
void PWM_TIM_Base_init_v(void)
{
	UWORD t_PrescalerValue_uw;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	/* Compute the prescaler value */
	t_PrescalerValue_uw = (uint16_t) (SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 665;
	TIM_TimeBaseStructure.TIM_Prescaler = t_PrescalerValue_uw;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}
void PWM_Channel_1_Init(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = NULL_UW;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
void PWM_Channel_2_Init(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = NULL_UW;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
void PWM_Channel_3_Init(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = NULL_UW;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
void PWM_Channel_4_Init(void)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = NULL_UW;

	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
void PWM_Channel_1_Update(UWORD p_Duty_uw)
{
	TIM_SetCompare1(TIM3, p_Duty_uw);
}
void PWM_Channel_2_Update(UWORD p_Duty_uw)
{
	TIM_SetCompare2(TIM3, p_Duty_uw);
}
void PWM_Channel_3_Update(UWORD p_Duty_uw)
{
	TIM_SetCompare3(TIM3, p_Duty_uw);
}
void PWM_Channel_4_Update(UWORD p_Duty_uw)
{
	TIM_SetCompare4(TIM3, p_Duty_uw);
}

