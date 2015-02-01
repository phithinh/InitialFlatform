/*
 * exti.c
 *
 *  Created on: Mar 7, 2014
 *      Author: TV
 */
#include <stdio.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_gpio.h>
#include <general_define.h>
#include <misc.h>
#define __GPIO_EXTI_DRV
#include "../gpio_hardware_config.h"
#include "../gpio_common.h"

void exti_init_v(void) {
	UWORD t_exti_index_uw;
	ULONG t_gpio_rcc_ul;
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	for (t_exti_index_uw = NULL_UW ; t_exti_index_uw < NUMBER_EXTI;
			t_exti_index_uw++) {
		/* Enable clock */
		t_gpio_rcc_ul = gpio_common_getRCC(
				exti_config_st[t_exti_index_uw].gpio_st.gpio_type_def);
		RCC_APB2PeriphClockCmd(t_gpio_rcc_ul, ENABLE);

		/* Configure pin as input floating */
		GPIO_InitStructure.GPIO_Pin =
				exti_config_st[t_exti_index_uw].gpio_st.GPIO_pins_ul;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(exti_config_st[t_exti_index_uw].gpio_st.gpio_type_def,
				&GPIO_InitStructure);

		/* Enable AFIO clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		/* Connect Line to pin */
		GPIO_EXTILineConfig(
				gpio_common_getPortSrc(
						exti_config_st[t_exti_index_uw].gpio_st.gpio_type_def),
				gpio_common_getPinSrc(
						exti_config_st[t_exti_index_uw].gpio_st.GPIO_pins_ul));

		/* Configure line */
		EXTI_InitStructure.EXTI_Line = gpio_common_getLine(
				exti_config_st[t_exti_index_uw].gpio_st.GPIO_pins_ul);
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger =
				exti_config_st[t_exti_index_uw].EXTI_Trigger_ub;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);

		/* Enable and set Interrupt to the lowest priority */
		NVIC_InitStructure.NVIC_IRQChannel = gpio_common_getLineIRQn(
				exti_config_st[t_exti_index_uw].gpio_st.GPIO_pins_ul);
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
}
void EXTI9_5_IRQHandler(void) {
	printf("HI\r\n");
	if (EXTI_GetITStatus(
			gpio_common_getLine(
					exti_config_st[EXTI_NUM_0].gpio_st.GPIO_pins_ul))
			!= RESET) {
		printf("extern interrupt5\n\r");
		/* Clear the  EXTI line pending bit */
		EXTI_ClearITPendingBit(
				gpio_common_getLine(
						exti_config_st[EXTI_NUM_0].gpio_st.GPIO_pins_ul));
	}
	if (EXTI_GetITStatus(
			gpio_common_getLine(
					exti_config_st[EXTI_NUM_1].gpio_st.GPIO_pins_ul))
			!= RESET) {
		printf("extern interrupt6\n\r");
		/* Clear the  EXTI line pending bit */
		EXTI_ClearITPendingBit(
				gpio_common_getLine(
						exti_config_st[EXTI_NUM_1].gpio_st.GPIO_pins_ul));
	}
	if (EXTI_GetITStatus(
			gpio_common_getLine(
					exti_config_st[EXTI_NUM_2].gpio_st.GPIO_pins_ul))
			!= RESET) {
		printf("extern interrupt7\n\r");
		/* Clear the  EXTI line pending bit */
		EXTI_ClearITPendingBit(
				gpio_common_getLine(
						exti_config_st[EXTI_NUM_2].gpio_st.GPIO_pins_ul));
	}
}

