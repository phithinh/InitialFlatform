/*-----------------------------------------------------------------------*/
/* MMC/SDSC/SDHC (in SPI mode) control module for STM32 Version 1.1.6    */
/* (C) Martin Thomas, 2010 - based on the AVR MMC module (C)ChaN, 2007   */
/*-----------------------------------------------------------------------*/

/* Copyright (c) 2010, Martin Thomas, ChaN
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.
* Neither the name of the copyright holders nor the names of
contributors may be used to endorse or promote products derived
from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE. */


#ifndef SD_SPI_STM32
#define SD_SPI_STM32
#include "diskio.h"

typedef enum
{
/**
  * @brief  SD reponses and error flags
  */
  SD_RESPONSE_NO_ERROR      = (0x00),
  SD_IN_IDLE_STATE          = (0x01),
  SD_ERASE_RESET            = (0x02),
  SD_ILLEGAL_COMMAND        = (0x04),
  SD_COM_CRC_ERROR          = (0x08),
  SD_ERASE_SEQUENCE_ERROR   = (0x10),
  SD_ADDRESS_ERROR          = (0x20),
  SD_PARAMETER_ERROR        = (0x40),
  SD_RESPONSE_FAILURE       = (0xFF),

/**
  * @brief  Data response error
  */
  SD_DATA_OK                = (0x05),
  SD_DATA_CRC_ERROR         = (0x0B),
  SD_DATA_WRITE_ERROR       = (0x0D),
  SD_DATA_OTHER_ERROR       = (0xFF)
} SD_Error;

/** 
  * @brief  Card Specific Data: CSD Register   
  */ 
typedef struct
{
  __IO uint8_t  CSDStruct;            /*!< CSD structure */
  __IO uint8_t  SysSpecVersion;       /*!< System specification version */
  __IO uint8_t  Reserved1;            /*!< Reserved */
  __IO uint8_t  TAAC;                 /*!< Data read access-time 1 */
  __IO uint8_t  NSAC;                 /*!< Data read access-time 2 in CLK cycles */
  __IO uint8_t  MaxBusClkFrec;        /*!< Max. bus clock frequency */
  __IO uint16_t CardComdClasses;      /*!< Card command classes */
  __IO uint8_t  RdBlockLen;           /*!< Max. read data block length */
  __IO uint8_t  PartBlockRead;        /*!< Partial blocks for read allowed */
  __IO uint8_t  WrBlockMisalign;      /*!< Write block misalignment */
  __IO uint8_t  RdBlockMisalign;      /*!< Read block misalignment */
  __IO uint8_t  DSRImpl;              /*!< DSR implemented */
  __IO uint8_t  Reserved2;            /*!< Reserved */
  __IO uint32_t DeviceSize;           /*!< Device Size */
  __IO uint8_t  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min */
  __IO uint8_t  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max */
  __IO uint8_t  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min */
  __IO uint8_t  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max */
  __IO uint8_t  DeviceSizeMul;        /*!< Device size multiplier */
  __IO uint8_t  EraseGrSize;          /*!< Erase group size */
  __IO uint8_t  EraseGrMul;           /*!< Erase group size multiplier */
  __IO uint8_t  WrProtectGrSize;      /*!< Write protect group size */
  __IO uint8_t  WrProtectGrEnable;    /*!< Write protect group enable */
  __IO uint8_t  ManDeflECC;           /*!< Manufacturer default ECC */
  __IO uint8_t  WrSpeedFact;          /*!< Write speed factor */
  __IO uint8_t  MaxWrBlockLen;        /*!< Max. write data block length */
  __IO uint8_t  WriteBlockPaPartial;  /*!< Partial blocks for write allowed */
  __IO uint8_t  Reserved3;            /*!< Reserded */
  __IO uint8_t  ContentProtectAppli;  /*!< Content protection application */
  __IO uint8_t  FileFormatGrouop;     /*!< File format group */
  __IO uint8_t  CopyFlag;             /*!< Copy flag (OTP) */
  __IO uint8_t  PermWrProtect;        /*!< Permanent write protection */
  __IO uint8_t  TempWrProtect;        /*!< Temporary write protection */
  __IO uint8_t  FileFormat;           /*!< File Format */
  __IO uint8_t  ECC;                  /*!< ECC code */
  __IO uint8_t  CSD_CRC;              /*!< CSD CRC */
  __IO uint8_t  Reserved4;            /*!< always 1*/
} SD_CSD;

/** 
  * @brief  Card Identification Data: CID Register   
  */
typedef struct
{
  __IO uint8_t  ManufacturerID;       /*!< ManufacturerID */
  __IO uint16_t OEM_AppliID;          /*!< OEM/Application ID */
  __IO uint32_t ProdName1;            /*!< Product Name part1 */
  __IO uint8_t  ProdName2;            /*!< Product Name part2*/
  __IO uint8_t  ProdRev;              /*!< Product Revision */
  __IO uint32_t ProdSN;               /*!< Product Serial Number */
  __IO uint8_t  Reserved1;            /*!< Reserved1 */
  __IO uint16_t ManufactDate;         /*!< Manufacturing Date */
  __IO uint8_t  CID_CRC;              /*!< CID CRC */
  __IO uint8_t  Reserved2;            /*!< always 1 */
} SD_CID;

/** 
  * @brief SD Card information 
  */
typedef struct
{
  SD_CSD SD_csd;
  SD_CID SD_cid;
  uint32_t CardCapacity;  /*!< Card Capacity */
  uint32_t CardBlockSize; /*!< Card Block Size */
} SD_CardInfo;

/* set to 1 to provide a disk_ioctrl function even if not needed by the FatFs */
#define STM32_SD_DISK_IOCTRL_FORCE      0
//------------Old lib-------------------
//
//#define CARD_SUPPLY_SWITCHABLE   0
//#define SOCKET_WP_CONNECTED      1 /* write-protect socket-switch */
//#define SOCKET_CP_CONNECTED      0 /* card-present socket-switch */
//#define GPIO_WP                  GPIOB
//#define GPIO_CP                  GPIOB
//#define RCC_APBxPeriph_GPIO_WP   RCC_APB2Periph_GPIOB
//#define RCC_APBxPeriph_GPIO_CP   RCC_APB2Periph_GPIOB
//#define GPIO_Pin_WP              GPIO_Pin_7
//#define GPIO_Pin_CP              GPIO_Pin_6
//#define GPIO_Mode_WP             GPIO_Mode_IN_FLOATING /* external resistor */
//#define GPIO_Mode_CP             GPIO_Mode_IN_FLOATING /* external resistor */
//#define GPIO_SD_PWR                  GPIOB
//#define RCC_APB2Periph_GPIO_SD_PWR   RCC_APB2Periph_GPIOB
//#define GPIO_Pin_SD_PWR              GPIO_Pin_7
//#define SPI_SD                   SPI1
//#define GPIO_CS                  GPIOA
//#define RCC_APB2Periph_GPIO_CS   RCC_APB2Periph_GPIOA
//#define GPIO_Pin_CS              GPIO_Pin_4
//#define DMA_Channel_SPI_SD_RX    DMA1_Channel4
//#define DMA_Channel_SPI_SD_TX    DMA1_Channel5
//#define DMA_FLAG_SPI_SD_TC_RX    DMA1_FLAG_TC4
//#define DMA_FLAG_SPI_SD_TC_TX    DMA1_FLAG_TC5
//#define GPIO_SPI_SD              GPIOA
//#define GPIO_Pin_SPI_SD_SCK      GPIO_Pin_5
//#define GPIO_Pin_SPI_SD_MISO     GPIO_Pin_6
//#define GPIO_Pin_SPI_SD_MOSI     GPIO_Pin_7
//#define RCC_APBPeriphClockCmd_SPI_SD  RCC_APB2PeriphClockCmd
//#define RCC_APBPeriph_SPI_SD     RCC_APB2Periph_SPI1
//................................................................
#define CARD_SUPPLY_SWITCHABLE   0
#define SOCKET_WP_CONNECTED      0 /* write-protect socket-switch */
#define SOCKET_CP_CONNECTED      0 /* card-present socket-switch */
#define GPIO_WP                  GPIOB
#define GPIO_CP                  GPIOB
#define RCC_APBxPeriph_GPIO_WP   RCC_APB2Periph_GPIOB
#define RCC_APBxPeriph_GPIO_CP   RCC_APB2Periph_GPIOB
#define GPIO_Pin_WP              GPIO_Pin_7
#define GPIO_Pin_CP              GPIO_Pin_6
#define GPIO_Mode_WP             GPIO_Mode_IN_FLOATING /* external resistor */
#define GPIO_Mode_CP             GPIO_Mode_IN_FLOATING /* external resistor */
#define GPIO_SD_PWR                  GPIOB
#define RCC_APB2Periph_GPIO_SD_PWR   RCC_APB2Periph_GPIOB
#define GPIO_Pin_SD_PWR              GPIO_Pin_7
#define SPI_SD                   SPI2
#define GPIO_CS                  GPIOC
#define RCC_APB2Periph_GPIO_CS   RCC_APB2Periph_GPIOC
#define GPIO_Pin_CS              GPIO_Pin_8
#define DMA_Channel_SPI_SD_RX    DMA1_Channel4
#define DMA_Channel_SPI_SD_TX    DMA1_Channel5
#define DMA_FLAG_SPI_SD_TC_RX    DMA1_FLAG_TC4
#define DMA_FLAG_SPI_SD_TC_TX    DMA1_FLAG_TC5
#define GPIO_SPI_SD              GPIOB
#define GPIO_Pin_SPI_SD_SCK      GPIO_Pin_13
#define GPIO_Pin_SPI_SD_MISO     GPIO_Pin_14
#define GPIO_Pin_SPI_SD_MOSI     GPIO_Pin_15
#define RCC_APBPeriphClockCmd_SPI_SD  RCC_APB1PeriphClockCmd
#define RCC_APBPeriph_SPI_SD     RCC_APB1Periph_SPI2


#define STM32_SD_USE_DMA

/* for SPI2 and full-speed APB1: 36MHz/2 */
/* !! PRESCALE 4 used here - 2 does not work, maybe because
of the poor wiring on the HELI_V1 prototype hardware */
#define SPI_BaudRatePrescaler_SPI_SD  SPI_BaudRatePrescaler_2

/* Definitions for MMC/SDC command */
#define CMD0	(0x40+0)	/* GO_IDLE_STATE */
#define CMD1	(0x40+1)	/* SEND_OP_COND (MMC) */
#define CMD8	(0x40+8)	/* SEND_IF_COND */
#define CMD9	(0x40+9)	/* SEND_CSD */
#define CMD10	(0x40+10)	/* SEND_CID */
#define CMD12	(0x40+12)	/* STOP_TRANSMISSION */
#define CMD13	(0x40+13)       /*SD_CMD_SEND_STATUS */
#define CMD16	(0x40+16)	/* SET_BLOCKLEN */
#define CMD17	(0x40+17)	/* READ_SINGLE_BLOCK */
#define CMD18	(0x40+18)	/* READ_MULTIPLE_BLOCK */
#define CMD23	(0x40+23)	/* SET_BLOCK_COUNT (MMC) */
#define CMD24	(0x40+24)	/* WRITE_BLOCK */
#define CMD25	(0x40+25)	/* WRITE_MULTIPLE_BLOCK */
#define CMD27	(0x40+27)	/* SD_CMD_PROG_CSD */
#define CMD28	(0x40+28)	/* SD_CMD_SET_WRITE_PROT */
#define CMD29	(0x40+29)	/* SD_CMD_CLR_WRITE_PROT */
#define CMD30	(0x40+30)	/* SD_CMD_SEND_WRITE_PROT */
#define CMD32	(0x40+32)	/* SD_CMD_SD_ERASE_GRP_START*/
#define CMD33	(0x40+33)	/* SD_CMD_SD_ERASE_GRP_END*/
#define CMD34	(0x40+34)	/* SD_CMD_UNTAG_SECTOR */
#define CMD35	(0x40+35)	/* SD_CMD_ERASE_GRP_START */
#define CMD36	(0x40+36)	/* SD_CMD_ERASE_GRP_END  */
#define CMD37	(0x40+37)	/* SD_CMD_UNTAG_ERASE_GROUP */
#define CMD38	(0x40+38)	/* SD_CMD_ERASE */
#define CMD55	(0x40+55)	/* APP_CMD */
#define CMD58	(0x40+58)	/* READ_OCR */

#define ACMD13	(0xC0+13)	/* SD_STATUS (SDC) */
#define ACMD23	(0xC0+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define ACMD41	(0xC0+41)	/* SEND_OP_COND (SDC) */

/* Card-Select Controls  (Platform dependent) */
#define SELECT()        GPIO_ResetBits(GPIO_CS, GPIO_Pin_CS)    /* MMC CS = L */
#define DESELECT()      GPIO_SetBits(GPIO_CS, GPIO_Pin_CS)      /* MMC CS = H */
/* Power Controls  (Platform dependent) */
#define _sd_on()        GPIO_ResetBits(GPIO_SD_PWR, GPIO_Pin_CS)    /* MMC CS = L */
#define _sd_off()       GPIO_SetBits(GPIO_SD_PWR, GPIO_Pin_CS)      /* MMC CS = H */

/* Manley EK-STM32F board does not offer socket contacts -> dummy values: */
#define SOCKPORT	1			/* Socket contact port */
#define SOCKWP		0			/* Write protect switch (PB5) */
#define SOCKINS		0			/* Card detect switch (PB4) */

#if (_MAX_SS != 512) || (_FS_READONLY == 0) || (STM32_SD_DISK_IOCTRL_FORCE == 1)
#define STM32_SD_DISK_IOCTRL   1
#else
#define STM32_SD_DISK_IOCTRL   0
#endif

DRESULT ff_memory_read (
                   BYTE drv,			/* Physical drive number (0) */
                   BYTE *buff,			/* Pointer to the data buffer to store read data */
                   DWORD addr,		/* Start addr number (LBA) */
                   BYTE count			/* Sector count (1..255) */
                       );
DRESULT ff_memory_write (
                    BYTE drv,			/* Physical drive number (0) */
                    const BYTE *buff,	/* Pointer to the data to be written */
                    DWORD addr,		/* Start sector number (LBA) */
                    BYTE count			/* Sector count (1..255) */
                        );

#endif /*SD_SPI_STM32*/
