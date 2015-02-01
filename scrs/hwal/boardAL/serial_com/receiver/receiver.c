/*
 * receiver.c
 *
 *  Created on: Apr 20, 2014
 *      Author: TV
 */

#include <compiler.h>
#include <serial_receiver.h>
void serial_RX_IRQHandler(UBYTE p_data_ub);

void DataCollection_serial_receiver_v(UBYTE p_data_ub);
void serial_RX_IRQHandler(UBYTE p_data_ub)
{
	DataCollection_serial_receiver_v(p_data_ub);
}


