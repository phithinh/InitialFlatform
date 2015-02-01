/******************** (C) COPYRIGHT 2013 H3ElTeam ********************
* File Name          : OLED.h
* Author             : OS Team
* Date First Issued  : 27/09/2014
* Description        : 

********************************************************************************
* History: DD/MM/YY
* 27/09/2014: V0.1
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Include global header file */
//#include "Common.h"
#ifndef	_OLED__H
#define _OLED__H
#include <digital_out_pub.h>
#include "SPI2_Function.h"

//////////////////////////////////////////////////////////////////////////////////	 
//imodule	
//////////////////////////////////////////////////////////////////////////////////	

#define XLevelL			0x00
#define XLevelH			0x10
#define XLevel	    	((XLevelH&0x0F)*16+XLevelL)
#define Max_Column		132
#define Max_Row			64
#define	Brightness		0xCF 
#define X_WIDTH 		132
#define Y_WIDTH 		64

#define OLED_LCD_MODULE
#define USE_IO_MCU_CONTROL
//#define USE_HC74595_MODULE
/* DC & CS IO control */
#ifdef USE_IO_MCU_CONTROL
//#define OLED_CS_Clr() 	pOLED_LCD_IO_CS.write(0)
//#define OLED_CS_Set() 	pOLED_LCD_IO_CS.write(1)
#endif
//#define OLED_CS_Clr()	{HC74595Control.bits.LCD_CS=0; HC74595Control.bits.RF_CS=0; HC74595_OUTPUT(HC74595Control.byte);}
//#define OLED_CS_Set() 	{HC74595Control.bits.LCD_CS=1; HC74595_OUTPUT(HC74595Control.byte);}

//#define OLED_DC_Clr() 	pOLED_LCD_IO_DC.write(0)
//#define OLED_DC_Set() 	pOLED_LCD_IO_DC.write(1)
//#define OLED_DC_Clr() 	{HC74595Control.bits.LCD_DC=0; HC74595_OUTPUT(HC74595Control.byte);}
//#define OLED_DC_Set() 	{HC74595Control.bits.LCD_DC=1; HC74595_OUTPUT(HC74595Control.byte);}

/* SPI Control define */
#define OLED_SPI_ReadWrite(data) User_SPI2_write(data)
#define pOLED_LCD_IO_CS_write(sta)	digital_out_set_v(OLED_CS,sta)
#define pOLED_LCD_IO_DC_write(sta)	digital_out_set_v(OLED_DC,sta)
#define OLED_IO_Control_Init()

/* Prototype Function */
void OLED_WrDat(unsigned char dat);
void OLED_WrCmd(unsigned char cmd);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char bmp_dat);
void OLED_CLS(void);
void OLED_Init(void);
//void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
//void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
//void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N);
//void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
void OLED_CS_Clr(void);
void OLED_CS_Set(void);
void OLED_DC_Clr(void);
void OLED_DC_Set(void);
//void OLED_DeInit(void);
#endif /* _OLED__H */
