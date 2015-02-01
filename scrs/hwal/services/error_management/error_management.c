/*
 * error_management.c
 *
 *  Created on: Apr 29, 2014
 *      Author: TV
 */
#include <general_define.h>
#include "error_management.h"

UBYTE EM_ErrorData_st[EM_FAULT_NUM];
void EM_SetFault_v(UBYTE p_fault_id_ub, UBYTE p_fault_state_ub){
	EM_ErrorData_st[p_fault_id_ub] = p_fault_state_ub;
}

void EM_ReadFault_v(UBYTE p_fault_id_ub, UBYTE* p_fault_state_pub){
	*p_fault_state_pub = EM_ErrorData_st[p_fault_id_ub];
}


