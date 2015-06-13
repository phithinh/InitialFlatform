/*
 * adc.c
 *
 *  Created on: Mar 15, 2014
 *      Author: TV
 */
#include <general_define.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_dma.h>
#include <misc.h>

#include <stdio.h>

#define __ADC_HAL
#include "adc.h"

#define ADC_NUM_CHANNEL	8
#define ADC1_DR_Address    ((uint32_t)0x4001244C)

#ifdef _HW_ADC_REGULAR_FEATURE
UWORD ADC_RegularConvertedValueTab_puw[8];
#endif
void ADC_init_v(void)
{
	/* System clocks configuration ---------------------------------------------*/
	ADC_RCC_Configuration_v();
	/* NVIC configuration ------------------------------------------------------*/
//	ADC_NVIC_Configuration_v();
	/* GPIO configuration ------------------------------------------------------*/
	ADC_GPIO_Configuration_v();
#ifdef _HW_ADC_REGULAR_FEATURE
	/* DMA configuration (only for regular mode)--------------------------------*/
	ADC_DMA_Configuration();
#endif
	/* ADC configuration -------------------------------------------------------*/
	ADC_Configuration_v();
	/* Start ADC1 Software Conversion */
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void ADC_RCC_Configuration_v(void)
{
	/* ADCCLK = PCLK2/4 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 

	/* Enable peripheral clocks ------------------------------------------------*/
	/* Enable ADC1, ADC2, ADC3 and GPIOC clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void ADC_GPIO_Configuration_v(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure gpio pin as analog inputs */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC_DMA_Configuration(void){
	DMA_InitTypeDef DMA_InitStructure;
	/* Enable DMA1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(&ADC_RegularConvertedValueTab_puw);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 8;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
}
void ADC_Configuration_v(void)
{
	ADC_InitTypeDef   ADC_InitStructure;
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = ADC_NUM_CHANNEL;
	ADC_Init(ADC1, &ADC_InitStructure);
#ifdef _HW_ADC_INJECT_FEATURE
//	/* Set injected sequencer length */
//	ADC_InjectedSequencerLengthConfig(ADC1, 4);
//	/* ADC1 regular channels configuration */ 
//	ADC_InjectedChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_28Cycles5);
//	ADC_InjectedChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_28Cycles5);
//	ADC_InjectedChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_28Cycles5);
//	ADC_InjectedChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_28Cycles5);
//
//	/* Enable JEOC interrupt */
//	ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
#endif

#ifdef _HW_ADC_REGULAR_FEATURE
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_13Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_13Cycles5);
	
	/* Regular discontinuous mode channel number configuration */
	//ADC_DiscModeChannelCountConfig(ADC1, 4);
	/* Enable regular discontinuous mode */
	//ADC_DiscModeCmd(ADC1, ENABLE);

	/* Enable ADC1 DMA */
	//ADC_DMACmd(ADC1, ENABLE);
	
	//ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
#endif
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	/* Enable ADC1 reset calibration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));
	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));
}

/**
  * @brief  Configures Vector Table base location.
  * @param  None
  * @retval None
  */
//void ADC_NVIC_Configuration_v(void)
//{
//  NVIC_InitTypeDef NVIC_InitStructure;
//
//  /* Configure and enable ADC interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
//}
//void ADC_start_v(void){
//#ifdef _HW_ADC_INJECT_FEATURE
//	ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);
//#endif
//#ifdef _HW_ADC_REGULAR_FEATURE
//	/* Enable ADC1 */
//	//ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//#endif
//}
//void ADC1_2_IRQHandler(void)
//{
//	static UBYTE s_adc_data_idx_ub = 0;
//#ifdef _HW_ADC_INJECT_FEATURE
//	/* Clear ADC1 JEOC pending interrupt bit */
//	ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
//	/* Get injected channel11 and channel12 converted value */
//	adc_data_pst.adc_channel1_value_uw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
//	adc_data_pst.adc_channel2_value_uw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);
//	adc_data_pst.adc_channel3_value_uw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_3);
//	adc_data_pst.adc_channel4_value_uw = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_4);
//#endif
//}

