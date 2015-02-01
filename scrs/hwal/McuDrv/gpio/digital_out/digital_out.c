/*
 * digital_out.c
 *
 *  Created on: Mar 8, 2014
 *      Author: TV
 */
#include <compiler.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define __GPIO_DIGITAL_OUT_DRV

#include "../gpio_common.h"
#include "../gpio_hardware_config.h"

#include "digital_out_pub.h"

void digital_out_init_v(void) {
	UWORD t_digital_out_index_uw;
	ULONG t_gpio_rcc_ul;
	GPIO_InitTypeDef GPIO_InitStructure;
	for (t_digital_out_index_uw = NULL_UW ; t_digital_out_index_uw < NUMBER_DIGITAL_OUT;
			t_digital_out_index_uw++) {
		/* Periph clock enable */
		t_gpio_rcc_ul = gpio_common_getRCC(
				digital_out_config_st[t_digital_out_index_uw].gpio_type_def);
		RCC_APB2PeriphClockCmd(t_gpio_rcc_ul, ENABLE);

		/* Configure pin in output pushpull mode */
		GPIO_InitStructure.GPIO_Pin =
				digital_out_config_st[t_digital_out_index_uw].GPIO_pins_ul;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(digital_out_config_st[t_digital_out_index_uw].gpio_type_def,
				&GPIO_InitStructure);
	}
}
void digital_out_set_v(UBYTE t_digital_outNo_ub, BOOL t_digital_outSta_b) {
	GPIO_WriteBit(digital_out_config_st[t_digital_outNo_ub].gpio_type_def,
			digital_out_config_st[t_digital_outNo_ub].GPIO_pins_ul, (BitAction) t_digital_outSta_b);
}
void digital_out_toggle_v(UBYTE t_digital_outNo_ub) {
	digital_out_set_v(t_digital_outNo_ub,
			!GPIO_ReadOutputDataBit(digital_out_config_st[t_digital_outNo_ub].gpio_type_def,
					digital_out_config_st[t_digital_outNo_ub].GPIO_pins_ul));
}

