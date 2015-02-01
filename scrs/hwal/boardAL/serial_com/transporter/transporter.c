/*
 * transporter.c
 *
 *  Created on: Apr 20, 2014
 *      Author: TV
 */

#include <compiler.h>
#include <crc8_cal.h>
#include "transporter.h"
#include "../RS485/RS485.h"

//void transporter_tx_v(UBYTE* p_package_pst){
//	UBYTE t_data_lenght_ub;
//	//update lenght value to package (the first byte)
//	t_data_lenght_ub = *p_package_pst;
//	//update crc value
//	*(p_package_pst+t_data_lenght_ub+1) = crc8_cal_ub(p_package_pst+1, t_data_lenght_ub);
//	//preparing package is done
//
//	//sending throught RS485
//	RS485_send_v(p_package_pst,t_data_lenght_ub+2); //1byte lenght+ data +  +1byte crc8
//}

