/*
 * Logger_sdw.c
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 *
 *  Description:
 *  	- Read data from Data Collection
 *  	- Store it to pre-buffer
 *  	- Interval Reaching, the data will be put to SD controller buffer (this is implemented in module _lib/Logger.c
 *  	- The SD controller buffer reach the number which larger than 50% total size of the buffer, the SD writing will be proceed
 */
#include <compiler.h>
#include <ff.h>
#include "SD_Logger/Logger.h"

#include "Logger_adapts.h"

#include "Logger_sdw.h"
#include "diskio.h"


#include "DataPacking/DataPacking.h"

void Logger_sdw_Init_v(void);
FATFS fs;
DATA_SOURCE_DEF Logger_DataSource = LOGGER_ADC;

LOGGER_ADC_CHANNEL_SEL_DEF Logger_ADC_Channel_Sel;
void Logger_sdw_Init_v(void){
	disk_initialize(0);
//	while(f_mount(&fs,"",1));
	f_mount(&fs,"",1);
	Logger_ADC_Channel_Sel.val = 0;
	Logger_ADC_Channel_Sel.Channel._Channel_0_b = 1;
	Logger_ADC_Channel_Sel.Channel._Channel_1_b = 1;
	if (Logger_DataSource == LOGGER_ADC){
		Logger_ADCPacking_FileInit_ub();
		Logger_SerialPacking_FileInit_ub();
	}
}

/*
 * Description:
 *  	- Read data from Data Collection
 *  	- Store data to ram
 */
void Logger_sdw_Main_T1_v(void) {
	if (Logger_DataSource == LOGGER_ADC){
		Logger_ADCPacking_v();
		Logger_SerialPacking_v();
	}
}
/*
 * Description:
 *  	- Determine there are any ram sector which is available to store to SD
 *  	- If ram sector is ready, call the SD control API to write to relevant file
 */
void Logger_sdw_Main_T10Low_v(void){
	Logger_Main_v();
}

void Logger_sdw_Main_T10_v(void){
	disk_timerproc();
}

