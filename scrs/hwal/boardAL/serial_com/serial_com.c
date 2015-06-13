/*
 * serial_com.c
 *
 *  Created on: Apr 4, 2015
 *      Author: phi thinh
 */
#include "general_define.h"
#include "serial_com_adapt.h"
#include <uart_pub.h>
#include <uart_cfg.h>

#include <RS485.h>
#define _RS485

#define __SERIAL_COM
#include "serial_com.h"

void serial_com_init_v(void){
	USART_init_v();
	serial_com_receiving_context_st.sent_index_ub = 0;
	serial_com_receiving_context_st.done_flag_ub = 0;
	serial_com_receiving_context_st.error_flag_ub = 0;
	serial_com_sending_context_st.sent_index_ub = 0;
	serial_com_sending_context_st.error_flag_ub = 0;
}
//Todo:
//next version, it should be return to determine the buffer is busy or not
void serial_com_send_v(unsigned char * p_data_ub, unsigned char p_lenght_ub){
	unsigned char t_index_ub;
	if (!serial_com_sending_context_st.tx_trigger){
		for (t_index_ub= 0; t_index_ub<p_lenght_ub;t_index_ub++){
			serial_com_sending_context_st.data_ub[t_index_ub] = *(p_data_ub+t_index_ub);
		}
		serial_com_sending_context_st.sent_length_ub = p_lenght_ub;
		serial_com_sending_context_st.tx_trigger = TRUE;
	}
}
/*
 * @ serial communication state machine
 *
 * State:
 * 		+ uninit
 * 		+ idle
 * 		+ receiving
 * 		+ sending
 *
 * uninit -> idle:
 * 			Condition:
 * 				1. initial function is done
 * idle -> receiving:
 * 			Condition:
 * 				1. got starting char '<'
 * idle -> sending:
 * 			Condition:
 * 				1. got state request
 * 				2. there is a error
 * receiving -> idle:
 * 			Condition:
 * 				1. got end char '>'
 * 				2. rx time out
 * sending -> idle:
 * 			Condition:
 * 				1. completed sending
 * 				2. tx time out
 *
 *
 * */

void serial_com_main(void){

	tick_count += SERIAL_COM_CYCLE;
  
	switch(serial_com_state){
	case SERIAL_COM_STATE_IDLE:
		serial_com_process_idle_v();
		serial_com_condition_idle_v();
		break;
	case SERIAL_COM_STATE_RECEIVING:
		serial_com_process_rx_v();
		serial_com_condition_rx_v();
		break;
	case SERIAL_COM_STATE_SENDING:
		serial_com_process_tx_v();
		serial_com_condition_tx_v();
		break;
	default:
		serial_com_state = SERIAL_COM_STATE_IDLE;
		break;
	}
}

void serial_com_isrq_hanlder(unsigned char p_data_ub){
	switch(serial_com_state){
	case SERIAL_COM_STATE_IDLE:
		if (COM_SERIAL_SPEC_CHAR_START == p_data_ub){
			serial_com_sm_rx_entry_v();
		}
		break;
	case SERIAL_COM_STATE_RECEIVING:
		if (COM_SERIAL_SPEC_CHAR_END == p_data_ub){
			serial_com_receiving_context_st.done_flag_ub = 1;
		}else if ((tick_count - serial_com_receiving_context_st.timerstamp )>COM_SERIAL_RX_TIME_OUT){
			serial_com_receiving_context_st.error_flag_ub = 1; // time out
		} else {
			// buffer is overflow
			if (SERIAL_COM_MAX_RX_BF <= serial_com_receiving_context_st.sent_index_ub){
				serial_com_receiving_context_st.error_flag_ub = 1; // max buffer
			} else {
				serial_com_receiving_context_st.data_ub[serial_com_receiving_context_st.sent_index_ub] = p_data_ub;
                serial_com_receiving_context_st.sent_index_ub++;
			}
		}
		break;
	case SERIAL_COM_STATE_SENDING:
		//?? :D
		serial_com_state = SERIAL_COM_STATE_IDLE;
		break;
	default:
		serial_com_state = SERIAL_COM_STATE_IDLE;
		break;
	}

}

//===================PROCESSES=========================
void serial_com_process_idle_v(void){
	unsigned char *t_data_pub;
	unsigned short t_lenght_uw;
	if (serial_com_receiving_context_st.error_flag_ub){
//			serial_com_nok_reaction_v();
		serial_com_receiving_context_st.error_flag_ub = 0;
	} else if(serial_com_receiving_context_st.done_flag_ub){
//			serial_com_ok_reaction_v();
		t_data_pub = serial_com_receiving_context_st.data_ub;
		t_lenght_uw = serial_com_receiving_context_st.sent_index_ub;
		serial_com_input_process_v(t_data_pub, t_lenght_uw);
		serial_com_receiving_context_st.done_flag_ub = 0;
	} else if (serial_com_sending_context_st.error_flag_ub){
		serial_com_sending_context_st.error_flag_ub = 0;
	}
}
void serial_com_process_rx_v(void){
	if ((tick_count - serial_com_receiving_context_st.timerstamp )>COM_SERIAL_RX_TIME_OUT){
		serial_com_receiving_context_st.error_flag_ub = 1; // time out
	}
}
void serial_com_process_tx_v(void){
	unsigned char t_index_ub;
	unsigned char t_lenght_ub;
	unsigned char *t_data_ub;
	t_index_ub = serial_com_sending_context_st.sent_index_ub;
	t_lenght_ub = serial_com_sending_context_st.sent_length_ub;
	t_data_ub = serial_com_sending_context_st.data_ub;
	if(t_index_ub < t_lenght_ub){
		serial_drv_send(*(t_data_ub+t_index_ub));
		t_index_ub++;
	}

	//time-out monitoring
	if ((tick_count - serial_com_sending_context_st.timerstamp )>COM_SERIAL_TX_TIME_OUT){
		serial_com_sending_context_st.error_flag_ub = 1; // time out
	}
	serial_com_sending_context_st.sent_index_ub = t_index_ub;
}
//===================CONDITION=========================
void serial_com_condition_idle_v(void){
	if(serial_com_sending_context_st.tx_trigger){
		serial_com_sm_tx_entry_v();
	}
}
void serial_com_condition_rx_v(void){
	if (serial_com_receiving_context_st.done_flag_ub){
		serial_com_sm_idle_entry_v();
	} else if (serial_com_receiving_context_st.error_flag_ub){
		serial_com_sm_idle_entry_v();
	}
}
void serial_com_condition_tx_v(void){
	char t_index_ub;
	char t_lenght_ub;
	t_index_ub = serial_com_sending_context_st.sent_index_ub;
	t_lenght_ub = serial_com_sending_context_st.sent_length_ub;

	if(t_index_ub == t_lenght_ub){
		serial_com_sm_idle_entry_v();
	} else if (serial_com_sending_context_st.error_flag_ub){
		serial_com_sm_idle_entry_v();
	}
}
//==================TRANSITION==========================

void serial_com_sm_rx_entry_v(void){
	serial_com_state = SERIAL_COM_STATE_RECEIVING;
	serial_com_receiving_context_st.timerstamp = tick_count;
	serial_com_receiving_context_st.done_flag_ub = 0;
	serial_com_receiving_context_st.error_flag_ub = 0;
	serial_com_receiving_context_st.sent_index_ub = 0;
	serial_com_receiving_context_st.timerstamp = tick_count;

}
void serial_com_sm_tx_exit_v(void){
	serial_com_sending_context_st.tx_trigger = FALSE;
}
void serial_com_sm_tx_entry_v(void){
#ifdef _RS485
	RS485_SendEnable();
#endif
	serial_com_state = SERIAL_COM_STATE_SENDING;
	serial_com_sending_context_st.timerstamp = tick_count;
	serial_com_sending_context_st.sent_index_ub = 0;
	serial_com_sending_context_st.error_flag_ub = 0;

}
void serial_com_sm_idle_entry_v(void){
#ifdef _RS485
	RS485_ReadEnable();
#endif
	serial_com_state = SERIAL_COM_STATE_IDLE;
	serial_com_receiving_context_st.sent_index_ub = 0;
	//serial_com_receiving_context_st.done_flag_ub = 0;
	//serial_com_receiving_context_st.error_flag_ub = 0;
	serial_com_sending_context_st.sent_index_ub = 0;
	//serial_com_sending_context_st.error_flag_ub = 0;

}
#undef __SERIAL_COM
