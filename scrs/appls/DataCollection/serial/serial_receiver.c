/*
 * serial_receiver.c
 *
 *  Created on: Nov 9, 2014
 *      Author: Phi Thinh
 */
#include <compiler.h>
#include "../DataCollection_adapts.h"
#include <serial_com.h>

#include <digital_out_pub.h>
#define RX_INT_SERIAL_MAX_RINGBUFF	30
UBYTE l_DataCollection_rxRingBuff_aub[RX_INT_SERIAL_MAX_RINGBUFF];
UBYTE l_DataCollection_rxRingBuff_front_ub, l_DataCollection_rxRingBuff_rear_ub;
enum {
	DATA_COLLECTION_RX_IDLE = 0,
	DATA_COLLECTION_RX_HANDLING
}l_DataCollection_rxStateMachine_ub;

UBYTE DataCollection_serial_rx_ReadingRingBuff_ub(UBYTE* p_data_pub);

void DataCollection_serial_init_v(void){
	VDB_DataCollection_rx_serial_status = RX_SERIAL_INVALID;

	l_DataCollection_rxRingBuff_front_ub = 0;
	l_DataCollection_rxRingBuff_rear_ub = 0;

	l_DataCollection_rxStateMachine_ub = DATA_COLLECTION_RX_IDLE;
	RS485_init_v();
}
/*
 * @brief: will be invoked by bsw when a rx interrupt is occurred
 * */
void DataCollection_serial_receiver_v(UBYTE p_data_ub){
	UBYTE t_front_index;

			digital_out_toggle_v(LED_OUT2);
	t_front_index = l_DataCollection_rxRingBuff_front_ub;
	l_DataCollection_rxRingBuff_aub[t_front_index] = p_data_ub;
	t_front_index = (UBYTE)((t_front_index+1)%RX_INT_SERIAL_MAX_RINGBUFF); //rolling
	l_DataCollection_rxRingBuff_front_ub = t_front_index;
}

void DataCollection_serial_receiver_mainT1_v(void){
	RX_SERIAL_STA_DEF t_data_status;
	UBYTE t_data_ub;
	//clear status to invalid
	t_data_status = RX_SERIAL_INVALID;
	/*
	 * serial receiving state machine:
	 * 	- idle:
	 *		reading all the valid data the ring buffer
	 *		waiting for starting char '\n'
	 * 			if got starting char, changing state to state handling
	 * 	- handling:
	 *			- reading all the valid data the ring buffer
	 * 			- determining whether data in ring-buffer is end char ('\r') or not.
	 * 			if the end char, changing the VDB status to valid, state to idle and exiting.
	 * 			otherwise, storing the data in ring buffer to VDB packing
	 */
	switch(l_DataCollection_rxStateMachine_ub){
	case DATA_COLLECTION_RX_IDLE:
		while(DataCollection_serial_rx_ReadingRingBuff_ub(&t_data_ub)){
			if(t_data_ub == '\n'){
				l_DataCollection_rxStateMachine_ub = DATA_COLLECTION_RX_HANDLING;
				VDB_DataCollection_rx_serial_idx_ub = 0;
				break;
			}
		}
		break;
	case DATA_COLLECTION_RX_HANDLING:
		while(DataCollection_serial_rx_ReadingRingBuff_ub(&t_data_ub)){
			if(t_data_ub == '\r'){
				l_DataCollection_rxStateMachine_ub = DATA_COLLECTION_RX_IDLE;
				t_data_status = RX_SERIAL_VALID;
				break;
			}else{
				if (VDB_DataCollection_rx_serial_idx_ub>RX_SERIAL_MAX_BUFF){//buffer is full
					break;
				}
				VDB_DataCollection_rx_serial_data_aub[VDB_DataCollection_rx_serial_idx_ub++] = t_data_ub;
			}
		}
		break;
	default:
		break;
	}
	VDB_DataCollection_rx_serial_status = t_data_status;
}

UBYTE DataCollection_serial_rx_ReadingRingBuff_ub(UBYTE* p_data_pub)
{
	if (l_DataCollection_rxRingBuff_front_ub == l_DataCollection_rxRingBuff_rear_ub){
		return 0;
	}else{
		*p_data_pub = l_DataCollection_rxRingBuff_aub[l_DataCollection_rxRingBuff_rear_ub];
		l_DataCollection_rxRingBuff_rear_ub = (UBYTE)((l_DataCollection_rxRingBuff_rear_ub+1)%RX_INT_SERIAL_MAX_RINGBUFF); //rolling
		return 1;
	}
}
