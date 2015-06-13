/*
 * serial_com_adapt.h
 *
 *  Created on: Apr 4, 2015
 *      Author: phi thinh
 */

#ifndef SERIAL_COM_ADAPT_H_
#define SERIAL_COM_ADAPT_H_
#include <uart_pub.h>

#define serial_drv_send(data) USART_drv_send_ub(data)

#include <net_reaction.h>
#define serial_com_input_process_v(p_data, p_lenght) net_input_reaction_v(p_data, p_lenght)

#endif /* SERIAL_COM_ADAPT_H_ */
