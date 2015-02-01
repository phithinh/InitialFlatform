/*
 * led_hardward_config.h
 *
 *  Created on: Mar 8, 2014
 *      Author: TV
 */

#ifndef LED_HARDWARD_CONFIG_H_
#define LED_HARDWARD_CONFIG_H_

#include <compiler.h>
#include <stm32f10x_gpio.h>

typedef struct {
	GPIO_TypeDef * gpio_type_def; //GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,
								  //GPIOF,GPIOG
	ULONG GPIO_pins_ul; //GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,
						//GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,
						//GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,
						//GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15,
						//GPIO_Pin_All
} GPIO_CONFIG_ST;
typedef struct {
	GPIO_CONFIG_ST gpio_st;
	EXTITrigger_TypeDef EXTI_Trigger_ub;	//EXTI_Trigger_Rising = 0x08,
							//EXTI_Trigger_Falling = 0x0C,  
							//EXTI_Trigger_Rising_Falling = 0x10
} EXTI_CONFIG_ST;

//------------------------------------------------------------------
//------------------------------------------------------------------
//User hardware definition for DIGITAL_OUT
//

//gpio_pinName

//output
typedef enum{
	RELAY1 =0     ,
	RELAY2      ,
	RELAY3      ,
	LED_OUT1    ,
	LED_OUT2    ,
	LED_OUT3    ,
	OLED_CS     ,
	OLED_DC     ,
//	OLED_MOSI   ,
//	OLED_CLK    ,
	NUMBER_DIGITAL_OUT
}GPIO_OUT_PINNAME;

//input
typedef enum{
	BUTTON1 = 0,
	BUTTON2,
	BUTTON3,
	NUMBER_DIGITAL_IN
}GPIO_IN_PINNAME;


#ifdef __GPIO_DIGITAL_OUT_DRV

/*
 * @Digital output pin configurations
 * */
const GPIO_CONFIG_ST digital_out_config_st[NUMBER_DIGITAL_OUT] = {

			{GPIOA,
					GPIO_Pin_15},
			{GPIOB,
					GPIO_Pin_3},
			{GPIOB,
					GPIO_Pin_4},
			{GPIOA,
					GPIO_Pin_0},
			{GPIOA,
					GPIO_Pin_1},
			{GPIOA,
					GPIO_Pin_2},
			{GPIOB,
					GPIO_Pin_10},
			{GPIOB,
					GPIO_Pin_11},
//			{GPIOB,
//					GPIO_Pin_14},
//			{GPIOB,
//					GPIO_Pin_12}
};
#endif
#undef __GPIO_DIGITAL_OUT_DRV
//------------------------------------------------------------------

//------------------------------------------------------------------
//------------------------------------------------------------------
//User harware defination for digital_in
//
#define DIGITAL_IN_PULL_UP
//#define DIGITAL_IN_PULL_DOWN

#ifdef __GPIO_DIGITAL_IN_DRV


/*
 * @Digital input pin configurations
 * */
const GPIO_CONFIG_ST digital_in_config_st[NUMBER_DIGITAL_IN] = {
	{GPIOA,
			GPIO_Pin_9},
	{GPIOA,
			GPIO_Pin_10},
	{GPIOA,
			GPIO_Pin_11},
};
#endif

#undef __GPIO_DIGITAL_IN_DRV
//------------------------------------------------------------------

//------------------------------------------------------------------
//------------------------------------------------------------------
//User harware defination for exti
//
#define EXTI_PULL_UP
//#define EXTI_PULL_DOWN

#define	NUMBER_EXTI	0
#define EXTI_NUM_0		0
#define EXTI_NUM_1		1
#define EXTI_NUM_2		2
#ifdef __GPIO_EXTI_DRV
const EXTI_CONFIG_ST exti_config_st[NUMBER_EXTI] = {
//	{{GPIOB, GPIO_Pin_5},
//			EXTI_Trigger_Rising_Falling},//PB5 //use for encoder phase A
//	{{GPIOB, GPIO_Pin_6},
//			EXTI_Trigger_Rising_Falling},//PB6 //use for encoder phase B
//	{{GPIOB, GPIO_Pin_7},
//			EXTI_Trigger_Rising_Falling}//PB7
};
#endif
#undef __GPIO_EXTI_DRV
#define ENCODER_phaseA	exti_config_st[0].gpio_st
#define ENCODER_phaseB	exti_config_st[1].gpio_st

#define GPIO_phaseA_status_b (BOOL) GPIO_ReadInputDataBit(\
		exti_config_st[0].gpio_st.gpio_type_def,\
		exti_config_st[0].gpio_st.GPIO_pins_ul);
#define GPIO_phaseB_status_b (BOOL) GPIO_ReadInputDataBit(\
		exti_config_st[1].gpio_st.gpio_type_def,\
		exti_config_st[1].gpio_st.GPIO_pins_ul);
//------------------------------------------------------------------

#endif /* LED_HARDWARD_CONFIG_H_ */
