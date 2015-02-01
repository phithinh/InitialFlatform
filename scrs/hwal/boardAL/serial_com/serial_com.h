/*
 * serial_com.h
 *
 *  Created on: Apr 28, 2014
 *      Author: TV
 *  Description:
 *  		declaration of API function of serial communacation
 */

#ifndef SERIAL_COM_H_
#define SERIAL_COM_H_
#include "RS485/RS485.h"

void transporter_tx_v(UBYTE* p_package_pst);
void receiver_monitor_v(void);
BOOL serial_read_receiveData_pub(UBYTE ** p_data_ppub);

#endif /* SERIAL_COM_H_ */
