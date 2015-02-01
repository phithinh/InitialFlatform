/*
 * RS485.h
 *
 *  Created on: Apr 28, 2014
 *      Author: TV
 */

#ifndef RS485_H_
#define RS485_H_

void RS485_ReadEnable(void);
void RS485_SendEnable(void);
void RS485_init_v(void);
void RS485_send_v(UBYTE* p_ch_ub,UBYTE lenght);

#endif /* RS485_H_ */
