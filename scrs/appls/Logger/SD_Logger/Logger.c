/* Includes ========================================;==========================*/
/*
 * History:
 * 		- 9 Oct 14: Initial version: Map's source
 * 		- 9 Oct 14: Modify
 * 				+ Remove feature RF and UART
 * 				+ Adding include ff.h
 */

#define __LOGGER_C_

#include "../Logger_adapts.h"

#include "Logger.h"
#include <ff.h>
#include <general_define.h>

UWORD t_WrittenSDErrCnt_uw = 0;
char Log_RamBuffer[LOGGER_RAM_SECTOR_SIZE * LOGGER_NUM_RAM_SECTOR];

LOGGER_RAM_SECTOR_CONFIG Logger_RamSector_st[] = {
		{ .pBUF =
		&Log_RamBuffer[LOGGER_RAM_SECTOR_0 * LOGGER_RAM_SECTOR_SIZE], .Cnt = 0,
		.Status = LOGGER_RAM_SECTOR_FREE, },
		{ .pBUF =
		&Log_RamBuffer[LOGGER_RAM_SECTOR_1 * LOGGER_RAM_SECTOR_SIZE], .Cnt = 0,
		.Status = LOGGER_RAM_SECTOR_FREE, },
		{ .pBUF =
		&Log_RamBuffer[LOGGER_RAM_SECTOR_2 * LOGGER_RAM_SECTOR_SIZE], .Cnt = 0,
		.Status = LOGGER_RAM_SECTOR_FREE, },
		{ .pBUF =
		&Log_RamBuffer[LOGGER_RAM_SECTOR_3 * LOGGER_RAM_SECTOR_SIZE], .Cnt = 0,
		.Status = LOGGER_RAM_SECTOR_FREE, },
};
#define Logger_CurCnt Logger_RamSector_st[Logger_RamSector_CurIndex].Cnt
#define Logger_Cur_pBUF Logger_RamSector_st[Logger_RamSector_CurIndex].pBUF

uint8 Logger_RamSector_CurIndex = LOGGER_RAM_SECTOR_0; //Current index
uint8 Logger_WrittenRamSector_Idx_ub = LOGGER_RAM_SECTOR_0;

void Logger_PutStringDataToRam_v(char* p_data_pc, unsigned short p_lenght_us);
void Logger_PutDecDataToRam_v(long p_data_l);
int FAT_SD_Open_Log(FIL * fdst, char namefile[]);
//int FAT_SD_Read_Log(char namefile[], char* pRead);

/*Global variables -----------------------------------------------------------*/
char LogFileNme[20];
FIL logfileobj; /* file objects */
//FIL fsrc, fdst;      // file objects
UINT br, bw;         // File R/W count
//


int FAT_SD_Open_Log(FIL * fdst, char namefile[]) {
	char t;
	FRESULT res; /* FatFs function common result code */

	/* Create destination file on the drive 0 */
	res = f_open(fdst, namefile, FA_WRITE);
	t = 1;
	if (res != FR_OK) {
		res = f_open(fdst, namefile, FA_CREATE_ALWAYS);
		if (res != FR_OK) {
			t = 0;
		}
	}
	// Move to end of the file to append data
	res = f_lseek(fdst, fdst->fsize);
	return t;
}

/**
 * @brief  Write text to logfile in SD Card
 - Preconditional : HSTM32_FAT_SD_Init_Log must be call before to init Disk on SD Card
 * @param
 - char text[]: Write this string to log file
 * @retval int Status
 - 0 : Failed
 - 1 : OK
 */
int FAT_SD_Write_Log(char *pBuf, uint16 lenght) {
	uint16 t_datalenght_ui16;
	//Write to log
	if (FAT_SD_Open_Log(&logfileobj, LogFileNme)) {
		//f_printf(&logfileobj,text);
		t_datalenght_ui16 = lenght;
		if(f_write(&logfileobj, pBuf, lenght, &t_datalenght_ui16)){
			return 1;//err
		}
		if (f_close(&logfileobj) != FR_OK) {/*Error State*/
			return 1;
		}
		return 0;
	}
	return 1;

}
/**
 * @brief  Read logfile in SD Card
 - Preconditional : HSTM32_FAT_SD_Init_Log must be call before to init Disk on SD Card
 * @param
 - char namefile[] : file name string
 * @retval int Status
 - 0 : Failed
 - 1 : OK
 */
//FIL fdst; /* file objects */
//int FAT_SD_Read_Log(char namefile[], char* pRead) {
//	FRESULT res; /* FatFs function common result code */
//
//	/* Create destination file on the drive 0 */
//	res = f_open(&fdst, "0:logfile.txt", FA_OPEN_ALWAYS | FA_READ);
//	/* Write data to file */
//	bw = 0;
//	br = 28;
//	/* Write data to file */
//	for (;;) {
//		res = f_read(&fdst, pRead, br, &bw); //Doc br byte tu file .txt luu vao mang buffer2
//		if (res || bw == 0)
//			break; /* error or eof */
//
//		/* Close open files */
//		f_close(&fdst);
//
//		/* Unregister work area prior to discard it */
//		f_mount(NULL, 0, 1);
//	}
//	return 0;
//}

//Updating to replace the system lib method
void Logger_PutStringDataToRam_v(char* p_data_pc, unsigned short p_lenght_us) {
	unsigned short t_loop_idx_us;
	for (t_loop_idx_us = 0; t_loop_idx_us < p_lenght_us; t_loop_idx_us++) {
		if (p_data_pc[t_loop_idx_us] == 0) {	//only character type
			break;
		}
		Logger_Cur_pBUF[Logger_CurCnt] = p_data_pc[t_loop_idx_us];
		Logger_CurCnt= (uint16)(Logger_CurCnt+1)%LOGGER_RAM_SECTOR_SIZE;
	}
}
void Logger_PutDecDataToRam_v(long p_data_l) {
	unsigned long t_radix_ul = 10;
	unsigned long t_data_ul;
	if (p_data_l < 0) { //sign detecting
		Logger_Cur_pBUF[Logger_CurCnt++] = '-';
		p_data_l = -p_data_l;
	}
	t_data_ul = (unsigned long) p_data_l;
	while (t_data_ul / t_radix_ul > 0) {	//radix computing
		t_radix_ul *= 10;
	}
	t_radix_ul /= 10;
	while (t_radix_ul > 0) {
		Logger_Cur_pBUF[Logger_CurCnt++] = (char)(t_data_ul/t_radix_ul+ '0');
		t_data_ul %=t_radix_ul;
		t_radix_ul/=10;
	}
}
uint8 Logger_RamSector_SizeChecking(uint8 p_NumberReqByte) {
	uint8 t_Logger_RamSector_NextIndex;
	if (p_NumberReqByte<= Logger_RamSector_NoFreeBytes_ub()) {
		return 0;
	}
	return (Logger_RamSector_getNew_ub());
}
UBYTE open=0;
/*
 * brief:	checking if there are any sector which is available to write to SD Card
 * */
void Logger_Main_v(void) {
	UBYTE t_FileOpeningStatus_ub;
	UBYTE t_WrittenRamSectorCnt_ub = 0;
	UWORD t_WrittenByteCnt_uw = 0;
	t_FileOpeningStatus_ub = (Logger_RamSector_st[Logger_WrittenRamSector_Idx_ub].Status
			== LOGGER_RAM_SECTOR_DONE);
	if ((t_FileOpeningStatus_ub)&&(open==0)){
		open = 1;
		if (!FAT_SD_Open_Log(&logfileobj, LogFileNme)){
			open=0;
			return;
		}

				if (f_close(&logfileobj) != FR_OK) {/*Error State*/
					return;
				}
				if (!FAT_SD_Open_Log(&logfileobj, LogFileNme)){
					return;
				}
	}
//	if (t_FileOpeningStatus_ub){
//		if (!FAT_SD_Open_Log(&logfileobj, LogFileNme)){
//			return;
//		}
//	}
	while (Logger_RamSector_st[Logger_WrittenRamSector_Idx_ub].Status
			== LOGGER_RAM_SECTOR_DONE) {
		if(f_write(&logfileobj,Logger_RamSector_st[Logger_WrittenRamSector_Idx_ub].pBUF,
				Logger_RamSector_st[Logger_WrittenRamSector_Idx_ub].Cnt,
				&t_WrittenByteCnt_uw)) {
			t_WrittenSDErrCnt_uw++;
			//err
			return;
		}
		Logger_RamSector_st[Logger_WrittenRamSector_Idx_ub].Status =
				LOGGER_RAM_SECTOR_FREE;
		Logger_RamSector_st[Logger_WrittenRamSector_Idx_ub].Cnt = 0;
		Logger_WrittenRamSector_Idx_ub = (uint8) (Logger_WrittenRamSector_Idx_ub + 1)
					% LOGGER_NUM_RAM_SECTOR;

//		t_WrittenRamSectorCnt_ub++;
//		if(t_WrittenRamSectorCnt_ub>100){
//			break;
//		}
	}
//	if(t_FileOpeningStatus_ub){
//		if (f_close(&logfileobj) != FR_OK) {/*Error State*/
//			return;
//		}
//	}
}

UBYTE Logger_RamSector_NoFreeBytes_ub(void){
	return(LOGGER_RAM_SECTOR_SIZE - Logger_CurCnt);
}
UBYTE Logger_RamSector_getNew_ub(void){
	uint8 t_Logger_RamSector_NextIndex;
	t_Logger_RamSector_NextIndex = (uint8) (Logger_RamSector_CurIndex + 1)
			% LOGGER_NUM_RAM_SECTOR;
	Logger_RamSector_st[Logger_RamSector_CurIndex].Status =
			LOGGER_RAM_SECTOR_DONE;

	//Check the available next sector
	if (Logger_RamSector_st[t_Logger_RamSector_NextIndex].Status
			!= LOGGER_RAM_SECTOR_FREE) {
		return 1; //there is no free sector
	}

	Logger_RamSector_CurIndex = t_Logger_RamSector_NextIndex;
	Logger_RamSector_st[Logger_RamSector_CurIndex].Cnt = 0;
	Logger_RamSector_st[Logger_RamSector_CurIndex].Status = LOGGER_RAM_SECTOR_OCCUPIED;
	return 0;
}
