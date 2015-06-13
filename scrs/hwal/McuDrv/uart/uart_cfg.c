/*
 * uart_cfg.c
 *
 *  Created on: Nov 10, 2014
 *      Author: Phi Thinh
 */
#include <general_define.h>
#include <serial_cbk.h>

#include "uart_pub.h"

UART_HW_CONFIG_ST_DEF uart_Hw_Cofig_st = {
	.RX_indication = &serial_com_isrq_hanlder
};
