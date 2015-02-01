/*
 * adc_reading.c
 *
 *  Created on: Apr 19, 2014
 *      Author: TV
 */

#include <interfaces.h>
#include <adc.h>

#include "../DataCollection_adapts.h"
#include "adc_reading.h"

void adc_reading_init_v(void){
	DataCollection_global_adc_values_pst->channel_0 = 0;
	DataCollection_global_adc_values_pst->channel_1 = 0;
	DataCollection_global_adc_values_pst->channel_2 = 0;
	DataCollection_global_adc_values_pst->channel_3 = 0;
	DataCollection_global_adc_values_pst->channel_4 = 0;
	DataCollection_global_adc_values_pst->channel_5 = 0;
	DataCollection_global_adc_values_pst->channel_6 = 0;
	DataCollection_global_adc_values_pst->channel_7 = 0;
//	DataCollection_global_adc_values_pst->channel_8 = 0;
//	DataCollection_global_adc_values_pst->channel_9 = 0;
//	DataCollection_global_adc_values_pst->channel_10 = 0;
//	DataCollection_global_adc_values_pst->channel_11 = 0;
	ADC_init_v();
}

void adc_reading_main_T1_v(void){
	DataCollection_global_adc_values_pst->channel_0 = ADC_RegularConvertedValueTab_puw[0] & 0x0FFF;
	DataCollection_global_adc_values_pst->channel_1 = ADC_RegularConvertedValueTab_puw[1] & 0x0FFF;
	DataCollection_global_adc_values_pst->channel_2 = ADC_RegularConvertedValueTab_puw[2] & 0x0FFF;
	DataCollection_global_adc_values_pst->channel_3 = ADC_RegularConvertedValueTab_puw[3] & 0x0FFF;
	DataCollection_global_adc_values_pst->channel_4 = ADC_RegularConvertedValueTab_puw[4] & 0x0FFF;
	DataCollection_global_adc_values_pst->channel_5 = ADC_RegularConvertedValueTab_puw[5] & 0x0FFF;
	DataCollection_global_adc_values_pst->channel_6 = ADC_RegularConvertedValueTab_puw[6] & 0x0FFF;
	DataCollection_global_adc_values_pst->channel_7 = ADC_RegularConvertedValueTab_puw[7] & 0x0FFF;
//	DataCollection_global_adc_values_pst->channel_8 = ADC_RegularConvertedValueTab_puw[8] & 0x0FFF;
//	DataCollection_global_adc_values_pst->channel_9 = ADC_RegularConvertedValueTab_puw[9] & 0x0FFF;
//	DataCollection_global_adc_values_pst->channel_10 = ADC_RegularConvertedValueTab_puw[10] & 0x0FFF;
//	DataCollection_global_adc_values_pst->channel_11 = ADC_RegularConvertedValueTab_puw[11] & 0x0FFF;
}
