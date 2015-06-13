/*
 * RS485.c
 *
 *  Created on: Apr 20, 2014
 *      Author: TV
 */
#include <general_define.h>
#include <digital_out_pub.h>
#include <uart_pub.h>

#include "RS485.h"

void RS485_ReadEnable(void)
{
	digital_out_set_v(RS485_DIR, FALSE);
}
void RS485_SendEnable(void)
{
	digital_out_set_v(RS485_DIR, TRUE);
}
