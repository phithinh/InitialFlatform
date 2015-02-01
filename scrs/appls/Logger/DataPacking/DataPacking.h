/*
 * DataPacking.h
 *
 *  Created on: Nov 1, 2014
 *      Author: Phi Thinh
 */

#ifndef DATAPACKING_H_
#define DATAPACKING_H_

typedef union{
	struct{
	UWORD _Channel_0_b: 	1;
	UWORD _Channel_1_b: 	1;
	UWORD _Channel_2_b: 	1;
	UWORD _Channel_3_b: 	1;
	UWORD _Channel_4_b: 	1;
	UWORD _Channel_5_b: 	1;
	UWORD _Channel_6_b: 	1;
	UWORD _Channel_7_b: 	1;
	UWORD _Channel_8_b: 	1;
	UWORD _Channel_9_b: 	1;
	UWORD _Channel_10_b: 	1;
	UWORD _Channel_11_b: 	1;
	UWORD _Channel_12_b: 	1;
	UWORD _Channel_13_b: 	1;
	UWORD _Channel_14_b: 	1;
	UWORD _Channel_15_b: 	1;
	}Channel;
	UWORD val;
}LOGGER_ADC_CHANNEL_SEL_DEF;

typedef enum {
	LOGGER_ADC = 0,
	LOGGER_RS485,
	LOGGER_IN_D,
	LOGGER_FREQ
}DATA_SOURCE_DEF;
void Logger_ADCPacking_v(void);
void Logger_SerialPacking_v(void);
UBYTE Logger_ADCPacking_FileInit_ub(void);
UBYTE Logger_SerialPacking_FileInit_ub(void);

void Logger_ADC_FileNamePreparing_v(void);
void Logger_ADC_PutTimeHeading_v(void);
void Logger_ADC_ADCchannelDetection_v(void);
#endif /* DATAPACKING_H_ */
