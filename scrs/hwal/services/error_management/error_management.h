/*
 * error_management.h
 *
 *  Created on: Apr 29, 2014
 *      Author: TV
 */

#ifndef ERROR_MANAGEMENT_H_
#define ERROR_MANAGEMENT_H_

#define EM_FAULT_NUM	1

typedef enum{
	EM_DIS_COM_FAULT = 0	//the error when the RS485 disconnects
}g_EM_Fault_list_en;

void EM_SetFault_v(UBYTE p_fault_id_ub, UBYTE p_fault_state_ub);
void EM_ReadFault_v(UBYTE p_fault_id_ub, UBYTE* p_fault_state_pub);

#endif /* ERROR_MANAGEMENT_H_ */
