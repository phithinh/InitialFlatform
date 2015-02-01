/*----------------------------------------------------------------------------

*----------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOGGER_H_
#define __LOGGER_H_
#include "compiler.h"

#define LOGGER_RAM_SECTOR_SIZE	1024
typedef enum {
	LOGGER_RAM_SECTOR_0 = 0,
	LOGGER_RAM_SECTOR_1,
	LOGGER_RAM_SECTOR_2,
	LOGGER_RAM_SECTOR_3,
	LOGGER_NUM_RAM_SECTOR
}LOGGER_RAMSECTOR_IDX_DEF;


typedef enum {
	LOGGER_RAM_SECTOR_FREE =0,
	LOGGER_RAM_SECTOR_OCCUPIED,
	LOGGER_RAM_SECTOR_DONE,
}LOGGER_RAM_SECTOR_STA_DEF;
typedef struct
{
    char*       pBUF;
    uint16      Cnt;
    LOGGER_RAM_SECTOR_STA_DEF      Status;
    uint8 	Resevered;
}LOGGER_RAM_SECTOR_CONFIG;


int FAT_SD_Write_Log(char *pBuf, uint16 lenght);
void Logger_PutStringDataToRam_v(char* p_data_pc, unsigned short p_lenght_us);
void Logger_PutDecDataToRam_v(long p_data_l);
uint8 Logger_RamSector_SizeChecking(uint8 p_NumberReqByte);

void Logger_Main_v(void);
UBYTE Logger_RamSector_NoFreeBytes_ub(void);
UBYTE Logger_RamSector_getNew_ub(void);
#endif /* __LOGGER_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
