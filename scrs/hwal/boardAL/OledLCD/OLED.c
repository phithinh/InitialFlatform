/******************** (C) COPYRIGHT 2013 H3ElTeam ********************
* File Name          : OLED.c
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
#include "OLED.h"
#ifndef	_OLED__C
#define _OLED__C
//#include "codetab.h"

/* Global variable */
//extern IO_Struct pOLED_LCD_IO_CS, pOLED_LCD_IO_DC, pOLED_LCD_IO_POWER;
#ifdef HC74595 
extern HC74595_Output HC74595Control; 
#endif

/* Test Use wiht HC74595 */
#ifdef HC74595 
extern void HC74595_OUTPUT(uint16_t ByteVal);
extern HC74595_Output HC74595Control;
#endif

#ifdef OLED_LCD_MODULE

void OLED_CS_Clr(void)
{
#ifdef USE_IO_MCU_CONTROL
  pOLED_LCD_IO_CS_write(0);
#endif
#ifdef HC74595 
  if(HC74595Control.bits.LCD_CS==1)
  {
    HC74595Control.bits.LCD_CS=0; 
    HC74595_OUTPUT(HC74595Control.byte);
  }
#endif
}
void OLED_CS_Set(void)
{
#ifdef USE_IO_MCU_CONTROL
  pOLED_LCD_IO_CS_write(1);
#endif	
#ifdef HC74595	
  if(HC74595Control.bits.LCD_CS==0)
  {
    HC74595Control.bits.LCD_CS=1; 
    HC74595_OUTPUT(HC74595Control.byte);
  }
#endif
}
void OLED_DC_Clr(void) 	
{
#ifdef USE_IO_MCU_CONTROL
  pOLED_LCD_IO_DC_write(0);
#endif
#ifdef USE_HC74595_MODULE
  if(HC74595Control.bits.LCD_DC==1)
  {
    /* Clear DC & Deactive CS LCD */
    HC74595Control.bits.LCD_CS=1; 
    HC74595Control.bits.LCD_DC=0; 
    HC74595_OUTPUT(HC74595Control.byte);
    /* Active LCD */
    HC74595Control.bits.LCD_CS=0; 
    HC74595_OUTPUT(HC74595Control.byte);
  }
#endif
}
void OLED_DC_Set(void) 
{
#ifdef USE_IO_MCU_CONTROL
  pOLED_LCD_IO_DC_write(1);
#endif
#ifdef USE_HC74595_MODULE
  if(HC74595Control.bits.LCD_DC==0)
  {
    /* Set DC & Deactive CS LCD */
    HC74595Control.bits.LCD_CS=1; 
    HC74595Control.bits.LCD_DC=1; 
    HC74595_OUTPUT(HC74595Control.byte);
    /* Active LCD */
    HC74595Control.bits.LCD_CS=0; 
    HC74595_OUTPUT(HC74595Control.byte);
  }
#endif
}

void OLED_WrDat(unsigned char dat)
{
  OLED_DC_Set();
  /* Active CS, use with shift resister */
  //	OLED_CS_Clr();
  OLED_SPI_ReadWrite(dat);
  /* Dective CS, use with shift resister */
  //	OLED_CS_Set();
}

void OLED_WrCmd(unsigned char cmd)
{
  OLED_DC_Clr();
  /* Active CS, use with shift resister */
  //	OLED_CS_Clr();
  OLED_SPI_ReadWrite(cmd);
  /* Dective CS, use with shift resister */
  //	OLED_CS_Set();
}

void OLED_SetPos(unsigned char x, unsigned char y)
{
  OLED_WrCmd(0xb0 + y);
  OLED_WrCmd(((x&0xf0)>>4)|0x10);
  OLED_WrCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char bmp_dat)
{
  unsigned char y,x;
  for(y=0;y<8;y++)
  {
    OLED_WrCmd(0xb0+y);
    OLED_WrCmd(0x01);//0x01 is the SSD1306, SH1106 is 0x00
    OLED_WrCmd(0x10);
    for(x=0;x<X_WIDTH;x++)
    {
      OLED_WrDat(bmp_dat);
    }
  }
}

void OLED_CLS(void)
{
  OLED_Fill(0x00);
}

void OLED_Init(void)
{
  /* Init IO */
#ifdef USE_IO_MCU_CONTROL
  OLED_IO_Control_Init();
#endif	
  
  /* Delay before start */
//  vTimerBase_DelayMS(20);
  OLED_CS_Clr();


	OLED_WrCmd(0xae);//--turn off oled panel
//	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(0xcf); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0,0xa1
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0,0xc8
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
	OLED_WrCmd(0xaf);//--turn on oled panel

	OLED_Fill(0x00);
	OLED_SetPos(0,0);
}
//
//void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[])
//{
//  unsigned char c=0,i=0,j=0;
//  while (ch[j]!='\0')
//  {
//    c = ch[j]-32;
//    if(x>126)
//    {
//      x=0;y++;
//    }
//    OLED_SetPos(x,y);
//    for(i=0;i<6;i++)
//    {
//      OLED_WrDat(F6x8[c][i]);
//    }
//    x+=6;
//    j++;
//  }
//}
//
//void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[])
//{
//  unsigned char c=0,i=0,j=0;
//  while (ch[j]!='\0')
//  {
//    c =ch[j]-32;
//    if(x>120)
//    {
//      x=0;y++;
//    }
//    OLED_SetPos(x,y);
//    for(i=0;i<8;i++)
//    {
//      OLED_WrDat(F8X16[c*16+i]);
//    }
//    OLED_SetPos(x,y+1);
//    for(i=0;i<8;i++)
//    {
//      OLED_WrDat(F8X16[c*16+i+8]);
//    }
//    x+=8;
//    j++;
//  }
//}
//
//void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N)
//{
//  unsigned char wm=0;
//  unsigned int adder=32*N;
//  OLED_SetPos(x , y);
//  for(wm = 0;wm < 16;wm++)
//  {
//    OLED_WrDat(F16x16[adder]);
//    adder += 1;
//  }
//  OLED_SetPos(x,y + 1);
//  for(wm = 0;wm < 16;wm++)
//  {
//    OLED_WrDat(F16x16[adder]);
//    adder += 1;
//  }
//}
//
//void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
//{
//  unsigned int j=0;
//  unsigned char x,y;
//
//  if(y1%8==0)
//  {
//    y=y1/8;
//  }
//  else
//    y=y1/8+1;
//  for(y=y0;y<y1;y++)
//  {
//    OLED_SetPos(x0,y);
//    for(x=x0;x<x1;x++)
//    {
//      OLED_WrDat(BMP[j++]);
//    }
//  }
//}
//
//void OLED_DeInit(void)
//{
//  OLED_WrCmd(0xae);//--turn off oled panel
//  OLED_Fill(0x00);
//  OLED_SetPos(0,0);
//  OLED_CS_Clr();
//  pOLED_LCD_IO_POWER.write(1);
//  vTimerBase_DelayMS(50);
//  SPI_I2S_DeInit(SPI2);
//}
#endif /* OLED_LCD_MODULE*/
#endif /* _OLED__C */
