/*
 * Logger_ADCPacking.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Phi Thinh
 */
#include <general_define.h>
#include "../Logger_adapts.h"
#include "../SD_Logger/Logger.h"

#include "DataPacking.h"

#define Logger_CurCnt	*Logger.pCnt

#define LOGGER_ADC_BIT0_MARK	0x00001
#define LOGGER_ADC_SIZE			5	//5 chars

extern char   LogFileNme[];
extern LOGGER_ADC_CHANNEL_SEL_DEF Logger_ADC_Channel_Sel;
ULONG Logger_UnseccessCnt = 0;
UBYTE Logger_NoADCchannel_ub = 0;
ULONG Logger_testCnt = 0;
void Logger_ADCPacking_v(void){
	UBYTE t_channel_ub;
	UBYTE t_NoWrittenChannel_ub;
	const UWORD *t_channel_value_puw = &logger_global_adc_values_pst->channel_0;
	t_NoWrittenChannel_ub = 0;
	for(t_channel_ub = 0; t_channel_ub<Logger_NoADCchannel_ub;t_channel_ub++){
		if((Logger_ADC_Channel_Sel.val>>t_channel_ub)&LOGGER_ADC_BIT0_MARK){
			t_NoWrittenChannel_ub++;
			//ram sector is full, need to get new sector
			if(Logger_RamSector_SizeChecking(LOGGER_ADC_SIZE+1)){	//adc chars + '\n'
				Logger_UnseccessCnt++;
				return;
			}
			Logger_PutDecDataToRam_v(t_channel_value_puw[t_channel_ub]);
			if (t_NoWrittenChannel_ub < Logger_NoADCchannel_ub)	{//not the last channel
				Logger_PutStringDataToRam_v("\t",1);
			}
		}
	}
	//ram sector is full, need to get new sector
	if(Logger_RamSector_SizeChecking(1)){
		Logger_UnseccessCnt++;
		return;
	}
	if(VDB_DataCollection_rx_serial_status == RX_SERIAL_VALID){
		Logger_PutStringDataToRam_v("\t",1);
	} else{
		Logger_PutStringDataToRam_v("\n",1);
	}
}

/*
 * brief:	initialization the file name (ADC_yyyy.mm.dd.txt)
 * 				Put the header Data: the current time: "\nCurrent Time	(\t)hh:mm:ss\n"
 * */
UBYTE Logger_ADCPacking_FileInit_ub(void){
	Logger_ADC_FileNamePreparing_v();
	Logger_ADC_PutTimeHeading_v();
	Logger_ADC_ADCchannelDetection_v();
	return 0;
}
void Logger_ADC_FileNamePreparing_v(void){
	UBYTE t_idx_ub = 0;
	//Name of file
	LogFileNme[t_idx_ub++] = 'A';
	LogFileNme[t_idx_ub++] = 'D';
	LogFileNme[t_idx_ub++] = 'C';
	LogFileNme[t_idx_ub++] = '_';
	LogFileNme[t_idx_ub++] = (char)((Now->year%10000)/1000 + '0');
	LogFileNme[t_idx_ub++] = (char)((Now->year%1000)/100 + '0');
	LogFileNme[t_idx_ub++] = (char)((Now->year%100)/10 + '0');
	LogFileNme[t_idx_ub++] = (char)(Now->year%10 + '0');
	LogFileNme[t_idx_ub++] = '.';
	LogFileNme[t_idx_ub++] = (char)(Now->mon/10 + '0');
	LogFileNme[t_idx_ub++] = (char)(Now->mon%10 + '0');
	LogFileNme[t_idx_ub++] = '.';
	LogFileNme[t_idx_ub++] = (char)(Now->day/10 + '0');
	LogFileNme[t_idx_ub++] = (char)(Now->day%10 + '0');
	LogFileNme[t_idx_ub++] = '.';
	LogFileNme[t_idx_ub++] = 't';
	LogFileNme[t_idx_ub++] = 'x';
	LogFileNme[t_idx_ub++] = 't';
	LogFileNme[t_idx_ub++] = 0;
}
void Logger_ADC_PutTimeHeading_v(void){
	//ram sector is full, need to get new sector
	if(Logger_RamSector_SizeChecking(23)){
		return;//err
	}
	Logger_PutStringDataToRam_v("\nCurrent Time\t",14);
	Logger_PutDecDataToRam_v(Now->hour);
	Logger_PutStringDataToRam_v(":",1);
	Logger_PutDecDataToRam_v(Now->min);
	Logger_PutStringDataToRam_v(":",1);
	Logger_PutDecDataToRam_v(Now->sec);
	Logger_PutStringDataToRam_v("\n",1);

}
void Logger_ADC_ADCchannelDetection_v(void){
	UBYTE t_channel_ub;
	for(t_channel_ub = 0; t_channel_ub<16;t_channel_ub++){
		if((Logger_ADC_Channel_Sel.val>>t_channel_ub)&LOGGER_ADC_BIT0_MARK){
			Logger_NoADCchannel_ub++;
			//ram sector is full, need to get new sector
			if(Logger_RamSector_SizeChecking(10)){
				Logger_UnseccessCnt++;
				return;
			}
			Logger_PutStringDataToRam_v("channel", 7);
			Logger_PutDecDataToRam_v(Logger_NoADCchannel_ub);
			Logger_PutStringDataToRam_v("\t", 1);
		}
	}
//	//ram sector is full, need to get new sector
//	if(Logger_RamSector_SizeChecking(1)){
//		Logger_UnseccessCnt++;
//		return;
//	}
//	Logger_PutStringDataToRam_v("\n",1);
}
