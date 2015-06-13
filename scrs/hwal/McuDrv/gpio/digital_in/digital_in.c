/*
 * button.c
 *
 *  Created on: Mar 8, 2014
 *      Author: TV
 */
#include <general_define.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define __GPIO_DIGITAL_IN_DRV

#include "../gpio_common.h"
#include "../gpio_hardware_config.h"

#include "digital_in_pub.h"

void digital_in_init_v(void) {
	UWORD t_digital_in_index_uw;
	ULONG t_gpio_rcc_ul;
	GPIO_InitTypeDef GPIO_InitStructure;
	for (t_digital_in_index_uw = NULL_UW ; t_digital_in_index_uw < NUMBER_DIGITAL_IN;
			t_digital_in_index_uw++) {
		/* Periph clock enable */
		t_gpio_rcc_ul = gpio_common_getRCC(
				digital_in_config_st[t_digital_in_index_uw].gpio_type_def);
		RCC_APB2PeriphClockCmd(t_gpio_rcc_ul, ENABLE);

		/* Configure pin in mode */
		GPIO_InitStructure.GPIO_Pin =
				digital_in_config_st[t_digital_in_index_uw].GPIO_pins_ul;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef DIGITAL_IN_PULL_UP
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
#elif DIGITAL_IN_PULL_DOWN
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
#else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#endif
		GPIO_Init(digital_in_config_st[t_digital_in_index_uw].gpio_type_def,
				&GPIO_InitStructure);
	}
}
BOOL digital_in_read(UBYTE t_buttonNo_ub) {
	return (BOOL) GPIO_ReadInputDataBit(
			digital_in_config_st[t_buttonNo_ub].gpio_type_def,
			digital_in_config_st[t_buttonNo_ub].GPIO_pins_ul);
}

