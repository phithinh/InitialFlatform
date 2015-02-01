/*
 * common.c
 *
 *  Created on: Mar 8, 2014
 *      Author: TV
 */
#include <compiler.h>
#include <stm32f10x_gpio.h>
#include "gpio_common.h"

ULONG gpio_common_getRCC(GPIO_TypeDef * t_gpio_type_def){
	switch((UL)t_gpio_type_def){
	case (UL)GPIOA: return RCC_APB2Periph_GPIOA;
	case (UL)GPIOB: return RCC_APB2Periph_GPIOB;
	case (UL)GPIOC: return RCC_APB2Periph_GPIOC;
	case (UL)GPIOD: return RCC_APB2Periph_GPIOD;
	case (UL)GPIOE: return RCC_APB2Periph_GPIOE;
	case (UL)GPIOF: return RCC_APB2Periph_GPIOF;
	case (UL)GPIOG: return RCC_APB2Periph_GPIOG;
	default:
		return NULL_UL;
	}
}
UBYTE gpio_common_getPortSrc(GPIO_TypeDef * t_gpio_type_def){
	switch((UL)t_gpio_type_def){
	case (UL)GPIOA: return GPIO_PortSourceGPIOA;
	case (UL)GPIOB: return GPIO_PortSourceGPIOB;
	case (UL)GPIOC: return GPIO_PortSourceGPIOC;
	case (UL)GPIOD: return GPIO_PortSourceGPIOD;
	case (UL)GPIOE: return GPIO_PortSourceGPIOE;
	case (UL)GPIOF: return GPIO_PortSourceGPIOF;
	case (UL)GPIOG: return GPIO_PortSourceGPIOG;
	default:
		return NULL_UL;
	}
}
ULONG gpio_common_getLine(UWORD GPIO_pins_uw){
	switch(GPIO_pins_uw){
	case GPIO_Pin_0 : return EXTI_Line0 ;
	case GPIO_Pin_1 : return EXTI_Line1 ;
	case GPIO_Pin_2 : return EXTI_Line2 ;
	case GPIO_Pin_3 : return EXTI_Line3 ;
	case GPIO_Pin_4 : return EXTI_Line4 ;
	case GPIO_Pin_5 : return EXTI_Line5 ;
	case GPIO_Pin_6 : return EXTI_Line6 ;
	case GPIO_Pin_7 : return EXTI_Line7 ;
	case GPIO_Pin_8 : return EXTI_Line8 ;
	case GPIO_Pin_9 : return EXTI_Line9 ;
	case GPIO_Pin_10: return EXTI_Line10;
	case GPIO_Pin_11: return EXTI_Line11;
	case GPIO_Pin_12: return EXTI_Line12;
	case GPIO_Pin_13: return EXTI_Line13;
	case GPIO_Pin_14: return EXTI_Line14;
	case GPIO_Pin_15: return EXTI_Line15;
	default:
		return NULL_UL;
	}
}
UBYTE gpio_common_getLineIRQn(UWORD GPIO_pins_uw){
	switch(GPIO_pins_uw){
	case GPIO_Pin_0 : return EXTI0_IRQn;
	case GPIO_Pin_1 : return EXTI1_IRQn;
	case GPIO_Pin_2 : return EXTI2_IRQn;
	case GPIO_Pin_3 : return EXTI3_IRQn;
	case GPIO_Pin_4 : return EXTI4_IRQn;
	case GPIO_Pin_5 : return EXTI9_5_IRQn;
	case GPIO_Pin_6 : return EXTI9_5_IRQn;
	case GPIO_Pin_7 : return EXTI9_5_IRQn;
	case GPIO_Pin_8 : return EXTI9_5_IRQn;
	case GPIO_Pin_9 : return EXTI9_5_IRQn;
	case GPIO_Pin_10: return EXTI15_10_IRQn;
	case GPIO_Pin_11: return EXTI15_10_IRQn;
	case GPIO_Pin_12: return EXTI15_10_IRQn;
	case GPIO_Pin_13: return EXTI15_10_IRQn;
	case GPIO_Pin_14: return EXTI15_10_IRQn;
	case GPIO_Pin_15: return EXTI15_10_IRQn;
	default:
		return NULL_UL;
	}
}

UBYTE gpio_common_getPinSrc(UWORD GPIO_pins_uw){
	switch(GPIO_pins_uw){
	case GPIO_Pin_0 : return GPIO_PinSource0;
	case GPIO_Pin_1 : return GPIO_PinSource1;
	case GPIO_Pin_2 : return GPIO_PinSource2;
	case GPIO_Pin_3 : return GPIO_PinSource3;
	case GPIO_Pin_4 : return GPIO_PinSource4;
	case GPIO_Pin_5 : return GPIO_PinSource5;
	case GPIO_Pin_6 : return GPIO_PinSource6;
	case GPIO_Pin_7 : return GPIO_PinSource7;
	case GPIO_Pin_8 : return GPIO_PinSource8;
	case GPIO_Pin_9 : return GPIO_PinSource9;
	case GPIO_Pin_10: return GPIO_PinSource10;
	case GPIO_Pin_11: return GPIO_PinSource11;
	case GPIO_Pin_12: return GPIO_PinSource12;
	case GPIO_Pin_13: return GPIO_PinSource13;
	case GPIO_Pin_14: return GPIO_PinSource14;
	case GPIO_Pin_15: return GPIO_PinSource15;
	default:
		return NULL_UL;
	}
}

