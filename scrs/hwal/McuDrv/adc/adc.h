/*
 * adc.h
 *
 *  Created on: Mar 21, 2014
 *      Author: TV
 */

#ifndef ADC_H_
#define ADC_H_
#include <general_define.h>

#define _HW_ADC_REGULAR_FEATURE

#ifdef _HW_ADC_REGULAR_FEATURE
extern UWORD ADC_RegularConvertedValueTab_puw[8];
#endif

/*
 * adc.c
 *
 *  Created on: Mar 15, 2014
 *      Author: TV
 */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
typedef struct{
	UWORD adc_channel1_value_uw;
	UWORD adc_channel2_value_uw;
	UWORD adc_channel3_value_uw;
	UWORD adc_channel4_value_uw;
	UWORD adc_channel5_value_uw;
	UWORD adc_channel6_value_uw;
	UWORD adc_channel7_value_uw;
	UWORD adc_channel8_value_uw;
}ADC_DATA_ST;
#ifdef __ADC_HAL
ADC_DATA_ST adc_data_pst;
#endif

void ADC_init_v(void);
//void ADC_start_v(void);
#ifdef __ADC_HAL
void ADC_RCC_Configuration_v(void);
void ADC_GPIO_Configuration_v(void);
void ADC_DMA_Configuration(void);
void ADC_Configuration_v(void);
void ADC_NVIC_Configuration_v(void);
#endif



#endif /* ADC_H_ */
