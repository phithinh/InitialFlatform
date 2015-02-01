/*
 * lcd.c
 *
 *  Created on: Jan 26, 2015
 *      Author: Phi Thinh
 */

#include <general_define.h>
#include <SPI2_Function.h>
#include "codetab.h"

#define LCD_C
#include "lcd.h"

void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (j<16)
	{
		c =ch[j]-32;
		if(x>120)
		{
			x=0;y++;
		}
		OLED_SetPos(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8X16[c*16+i]);
		}
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8X16[c*16+i+8]);
		}
		x+=8;
		j++;
	}
}

void lcd_init(void){
	SPI2_Init();
	OLED_Init();
}

void lcd_main(void) {
//	UBYTE t_posx_ub = 0;
//	UBYTE t_posy_ub = 0;
//	UBYTE t_char_ub = 0, i = 0, t_col_ub = 0;
//	for (t_posy_ub = 0; t_posy_ub < 8;) {
//		for (t_col_ub = 0; t_col_ub < 16; t_col_ub++) {
//			t_char_ub = lcd_readbuf_ub[t_posy_ub*8+t_col_ub]-32;
//			OLED_SetPos(t_posx_ub, t_posy_ub);
//			for (i = 0; i < 8; i++) {
//				OLED_WrDat(F8X16[t_char_ub * 16 + i]);
//			}
//			OLED_SetPos(t_posx_ub, t_posy_ub + 1);
//			for (i = 0; i < 8; i++) {
//				OLED_WrDat(F8X16[t_char_ub * 16 + i + 8]);
//			}
//			t_posx_ub += 8;
//			t_posy_ub += 2;
//		}
//	}

	OLED_8x16Str(0,0,&lcd_readbuf_ub[0]);
	OLED_8x16Str(0,2,&lcd_readbuf_ub[16]);
	OLED_8x16Str(0,4,&lcd_readbuf_ub[32]);
	OLED_8x16Str(0,6,&lcd_readbuf_ub[48]);
}

void lcd_write (UBYTE p_index_ub, UBYTE p_data_ub){
	if (p_index_ub<	LCD_MAX_BUFF){
		if ((p_data_ub <='~')&&(p_data_ub>='!')){
			lcd_readbuf_ub[p_index_ub]= p_data_ub;
		}else{
			lcd_readbuf_ub[p_index_ub]= 32;
		}
	}
}
/*
 * Function: lcd_write_str_v
 * Input
 * 	- line: index of line user wants to display
 * 	- p_data_ub: buffer of string
 * 	- len: length of string - assume always valid
 * Description:
 * 	- Write a buffer to LCD, at specific line
 * 	- line starts from 0 to 3 *
 */

void lcd_write_str_v (UBYTE line, UBYTE* p_data_ub, UBYTE len)
{
	UBYTE t_lcd_offset_ub, t_index_ub;
	//assume app always passes the valid line
	t_lcd_offset_ub = line * LCD_CHAR_PER_LINE;
	for (t_index_ub = 0; t_index_ub < len; t_index_ub++)
	{
		lcd_write(t_index_ub + t_lcd_offset_ub, p_data_ub[t_index_ub]);
	}


}
