/*
 * net.c
 *
 *  Created on: Apr 22, 2014
 *      Author: TV
 */
/*
 *
 * */
#include <general_define.h>
#include <serial_com.h>


UBYTE net_sending_data_pub[30];

#define NET_RX_TIME_OUT		30		//30 ms
#define NET_RX_STABLE_TIME	2000		//2000 ms
UWORD g_net_RxEncnt_ms_uw = 0;
UWORD g_net_RxDiscnt_ms_uw = 0;

void net_T1_process_v(button_status_tst*	p_button_status_st,
						adc_values_tst* 	p_adc_values_st)
{
//#ifdef _BOARD_RELAY
	UBYTE t_iloop_ub;
	UBYTE* t_interface_pointer_pub;
	UBYTE* t_data_pub;
	BOOL t_data_valid_b;
	UBYTE t_ComError_ub;

	receiver_monitor_v();
	t_data_valid_b = serial_read_receiveData_pub(&t_data_pub);
	EM_ReadFault_v(EM_DIS_COM_FAULT,&t_ComError_ub);
	if(t_data_valid_b){
		if(t_ComError_ub){	//if the fault is set, checking stable state is done
			g_net_RxEncnt_ms_uw++;
			if(g_net_RxEncnt_ms_uw>NET_RX_STABLE_TIME){	//>5s -> data is stable
				EM_SetFault_v(EM_DIS_COM_FAULT,0);	//clear fault
			} else{
				return;
			}
		}
		g_net_RxDiscnt_ms_uw = 0;

		//data is ok, it is read from serial_com and store to interfaces
		t_interface_pointer_pub = (UBYTE*)p_button_status_st;
		for(t_iloop_ub = 0; t_iloop_ub<4;t_iloop_ub++){
			*(t_interface_pointer_pub + t_iloop_ub) = *(t_data_pub + 1 + t_iloop_ub);
		}
		t_interface_pointer_pub = (UBYTE*)p_adc_values_st;
		for(t_iloop_ub = 0; t_iloop_ub<16;t_iloop_ub++){
			*(t_interface_pointer_pub + t_iloop_ub) = *(t_data_pub + 1 + 4 + t_iloop_ub);
		}
		//storing is done
	} else {
		if(t_ComError_ub==0){
			g_net_RxDiscnt_ms_uw++;
			if(g_net_RxDiscnt_ms_uw>NET_RX_TIME_OUT){	//>100s -> data timeout
//				EM_SetFault_v(EM_DIS_COM_FAULT,1);	//set fault
				g_net_RxEncnt_ms_uw = 0;
			}
		}
	}

//#endif
}
void net_T10_process_v(button_status_tst*	p_button_status_st,
						adc_values_tst* 	p_adc_values_st)
{
//#ifdef _BOARD_CONTROLLER
	UBYTE t_iloop_ub;
	UBYTE* t_interface_pointer_pub;
	t_interface_pointer_pub = (UBYTE*)p_button_status_st;
	for(t_iloop_ub = 0; t_iloop_ub<4;t_iloop_ub++){
		net_sending_data_pub[t_iloop_ub+1] = *(t_interface_pointer_pub + t_iloop_ub);
	}
	t_interface_pointer_pub = (UBYTE*)p_adc_values_st;
	for(t_iloop_ub = 0; t_iloop_ub<16;t_iloop_ub++){
		net_sending_data_pub[t_iloop_ub+4+1] = *(t_interface_pointer_pub + t_iloop_ub);
	}
	net_sending_data_pub[0]=20;	//data lenght is 16 bytes
	transporter_tx_v((UBYTE*)&net_sending_data_pub[0]);
//#endif
}
