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

#ifdef __SERIAL_COM
#define EXTERN
#else
#define EXTERN extern
#endif

#define COM_SERIAL_SPEC_CHAR_START	('<')
#define COM_SERIAL_SPEC_CHAR_END	('>')

#define SERIAL_COM_CYCLE	10	//10ms

#define COM_SERIAL_RX_TIME_OUT	1000 //100ms
#define COM_SERIAL_TX_TIME_OUT	1000

#define SERIAL_COM_MAX_RX_BF		50
#define SERIAL_COM_MAX_TX_BF		50

EXTERN struct {
	signed long timerstamp;
	unsigned char data_ub[SERIAL_COM_MAX_RX_BF];
	unsigned char sent_index_ub;
	unsigned char error_flag_ub;
	unsigned char done_flag_ub;
}serial_com_receiving_context_st;
EXTERN struct {
	signed long timerstamp;
	unsigned char data_ub[SERIAL_COM_MAX_TX_BF];
	unsigned char sent_index_ub;
	unsigned char sent_length_ub;
	unsigned char error_flag_ub;
	unsigned char tx_trigger;
}serial_com_sending_context_st;

EXTERN unsigned short l_serial_com_requested_relay_uw;
EXTERN unsigned char l_serial_com_requested_relay_flag_b;

#ifdef __SERIAL_COM
enum{
	SERIAL_COM_STATE_UNINIT = 0,
	SERIAL_COM_STATE_IDLE,
	SERIAL_COM_STATE_RECEIVING,
	SERIAL_COM_STATE_SENDING,
}serial_com_state;
//local function

long tick_count;

void serial_com_process_idle_v(void);
void serial_com_process_rx_v(void);
void serial_com_process_tx_v(void);
void serial_com_condition_idle_v(void);
void serial_com_condition_rx_v(void);
void serial_com_condition_tx_v(void);
void serial_com_sm_rx_entry_v(void);
void serial_com_sm_tx_exit_v(void);
void serial_com_sm_tx_entry_v(void);
void serial_com_sm_idle_entry_v(void);
#endif


void serial_com_init_v(void);
void serial_com_main(void);
void serial_com_send_v(unsigned char * p_data_ub, unsigned char p_lenght_ub);
void serial_com_isrq_hanlder(unsigned char p_data_ub);

#undef EXTERN
#endif /* SERIAL_COM_APPL_H_ */

