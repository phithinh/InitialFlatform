/*
 * RS485.c
 *
 *  Created on: Apr 20, 2014
 *      Author: TV
 */
#include <compiler.h>
#include <digital_out_pub.h>
#include <uart_pub.h>

#include "RS485.h"
//#ifndef	RS485_DIR
//#define RS485_DIR DIGITAL_OUT7
//#endif

void RS485_ReadEnable(void)
{
	digital_out_set_v(RS485_DIR, FALSE);
}
void RS485_SendEnable(void)
{
	digital_out_set_v(RS485_DIR, TRUE);
}

void RS485_init_v(void){
	RS485_ReadEnable();
	USART_init_v();
}

void RS485_send_v(UBYTE* p_ch_ub,UBYTE lenght){
//	UBYTE t_iloop_ub;
//	RS485_SendEnable();
//	for(t_iloop_ub = 0;t_iloop_ub<lenght;t_iloop_ub++){
//		USART_SendData(COM_SELECT_BASE, (uint8_t) *(p_ch_ub+t_iloop_ub));
//		/* Loop until the end of transmission */
//		while (USART_GetFlagStatus(COM_SELECT_BASE, USART_FLAG_TC ) == RESET)
//		{}
//	}
//	RS485_ReadEnable();
}
