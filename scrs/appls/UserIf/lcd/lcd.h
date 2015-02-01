/*
 * lcd.h
 *
 *  Created on: Jan 26, 2015
 *      Author: Phi Thinh
 */

#ifndef LCD_H_
#define LCD_H_

#include <OLED.h>
#define LCD_MAX_BUFF	64
#define LCD_CHAR_PER_LINE	16

#ifdef LCD_C
UBYTE lcd_readbuf_ub[LCD_MAX_BUFF] = {'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6'};
#endif


void lcd_init(void);

void lcd_main(void);

void lcd_write (UBYTE p_index_ub, UBYTE p_data_ub);

void lcd_write_str_v (UBYTE line, UBYTE* p_data_ub, UBYTE len);

#endif /* LCD_H_ */
