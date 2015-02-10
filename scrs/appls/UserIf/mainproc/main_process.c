#define MAIN_PROCESS

#include <general_define.h>
#include <interfaces.h>
#include "main_process_pub.h"
#include "main_process_pri.h"
#include "main_process_typ.h"
#include "main_process_adapt.h"
#include <DataCollection_time.h>

#include <string.h>
#include <stdio.h>

/*
 * Function
 * 		main_init_v
 *
 * Description
 * 		- initialization function for main processing part
 * 		- reset the states machine of main processing to default value
 * 		- reset timer
 * Input	None
 * Output	None
 *
 */
void main_init_v()
{
	main_reset_stats_v();
	main_cur_hour = global_time_pst->hour;
	main_cur_min = global_time_pst->min;

	main_set_act_hour = (DataCollection_read_bk1_v() & 0xff00) >> 8;
	main_set_act_min = (DataCollection_read_bk1_v() & 0x00ff);

	main_set_dur_min = (DataCollection_read_bk2_v() & 0xff00) >> 8;
	main_set_dur_sec = (DataCollection_read_bk2_v() & 0x00ff);

	main_idle_tmr_cnt = IDLE_SUB_CYC;
}

/*
 * Function
 * 		main_process_v
 *
 * Description
 * 		- main processing
 * 		- simply calls the respective sub-functions due to current state
 * 		- handling invalid state
 * Input	None
 * Output	None
 *
 */

void main_process_v()
{
	main_cur_hour = global_time_pst->hour;
	main_cur_min = global_time_pst->min;
	main_cur_sec = global_time_pst->sec;

	switch (t_main_stat)
	{
	case M_IDLE:
		main_proc_idle_v();
		break;
	case M_SET_ACT_TIME:
		main_set_activation_time_v();
		break;
	case M_SET_CUR_TIME:
		main_set_current_time_v();
		break;
	case M_SET_DUR_TIME:
		main_set_duration_v();
		break;
	case M_SET_TST_ACT:
		main_test_active_v();
		break;
	case M_SET_TST_DEACT:
		main_test_deactive_v();
		break;
	default:
		main_reset_stats_v();
		break;
	}
}

/*
 * Function
 * 		main_proc_idle_v
 *
 * Description
 * 		- idle state processing
 * 		- depends on input from key event
 * 			+ can switch to another state
 * 			+ or count down timer to activate the relay
 * 			also display current time --> set up time --> duration --> welcome screen
 * 			each display takes 2 seconds
 * Input	None
 * Output	None
 *
 */
void main_proc_idle_v()
{
	ULONG t_start_ul, t_end_ul, t_cur_ul;

	t_start_ul = main_set_act_hour * 24 * 60 * 60 + main_set_act_min * 60;
	t_end_ul = t_start_ul + main_set_dur_min * 60 + main_set_dur_sec;
	t_cur_ul = main_cur_hour * 24 * 60 * 60 + main_cur_min * 60 + main_cur_sec;


	if(t_event_e == KEY_MOD)
	{
		main_chg_to_set_act_hour_v();

	}
	else
	{

		if((t_cur_ul >= t_start_ul) && (t_cur_ul <= t_end_ul))
		{
			main_is_activating_done = 0;
			t_idle_stat = M_SUB_IDLE_ACT;
		}
		else
		{
			main_is_activating_done = 1;
		}



		/*
		 * For displaying purpose: set string to the output process
		 */
		switch (t_idle_stat)
		{
			case M_SUB_IDLE_CUR:
				strcpy(main_cmd_top, main_cmd_idle_cur_top);

				sprintf(main_cmd_bot, "%d : %d : %d", main_cur_hour, main_cur_min, main_cur_sec);

				break;
			case M_SUB_IDLE_SET:
				strcpy(main_cmd_top, main_cmd_idle_set_top);

				sprintf(main_cmd_bot, "%d : %d", main_set_act_hour, main_set_act_min);

				break;
			case M_SUB_IDLE_DUR:
				strcpy(main_cmd_top, main_cmd_idle_dur_top);

				sprintf(main_cmd_bot, "%d : %d", main_set_dur_min, main_set_dur_sec);

				break;
			case M_SUB_IDLE_ACT:
				if(main_is_activating_done == 1)
				{
					main_chg_to_idle_v();
				}
				else
				{
					strcpy(main_cmd_top, main_cmd_idle_act_top);
					strcpy(main_cmd_bot, main_cmd_idle_act_bot);
					motor_activate_v();
				}

				break;
			default:
				main_reset_stats_v();
				break;
		}
		main_idle_tmr_cnt -= CORE_CYC_TMR;
		if(main_idle_tmr_cnt <= 0)
		{
			main_idle_tmr_cnt = IDLE_SUB_CYC;
			t_idle_stat = main_idle_get_next_sub_stat(t_idle_stat);
		}
		else
		{
			/* do nothing, keep going on */
		}
	}
}


/*
 * Function
 * 		main_set_activation_time_v
 *
 * Description
 * 		- setup activation time
 * 		- has 2 sub-states: set hour - set minute: process accordingly
 * Input	None
 * Output	None
 *
 */
void main_set_activation_time_v()
{
	switch (t_set_act_stat)
	{
		case M_SUB_SET_HOUR:
			main_set_activation_hour_v();
			break;
		case M_SUB_SET_MIN:
			main_set_activation_min_v();
			break;
		default:
			main_reset_stats_v();
			break;
	}

}

void main_set_activation_hour_v()
{
	UWORD t_acttime_uw;
	if(t_event_e == KEY_MOD)
	{
		main_chg_to_set_cur_hour_v();
	}
	else if(t_event_e == KEY_INC)
	{
		main_set_act_hour ++;
		if(main_set_act_hour >= 24)
		{
			main_set_act_hour = 0;
		}
		t_acttime_uw = DataCollection_read_bk1_v()&0x00FF;
		t_acttime_uw |= (main_set_act_hour << 8);
		DataCollection_set_bk1_v(t_acttime_uw);
		sprintf(main_cmd_bot, "%d : %d", main_set_act_hour, main_set_act_min);

	}
	else if(t_event_e == KEY_OK)
	{
		main_chg_to_set_act_min_v();
	}
	else
	{
		main_chg_to_invalid_v();
	}

}

void main_set_activation_min_v()
{
	UWORD t_acttime_uw;
	if(t_event_e == KEY_MOD)
	{
		main_chg_to_idle_v();
	}
	else if(t_event_e == KEY_INC)
	{
		main_set_act_min ++;
		if(main_set_act_min >= 60)
		{
			main_set_act_min = 0;
		}
		t_acttime_uw = DataCollection_read_bk1_v()&0xFF00;
		t_acttime_uw |= main_set_act_min;
		DataCollection_set_bk1_v(t_acttime_uw);
		sprintf(main_cmd_bot, "%d : %d", main_set_act_hour, main_set_act_min);

	}
	else if(t_event_e == KEY_OK)
	{
		main_chg_to_set_act_hour_v();
	}
	else
	{
		main_chg_to_invalid_v();
	}
}

void main_set_current_time_v()
{
	switch (t_set_cur_stat)
	{
		case M_SUB_SET_HOUR:
			main_set_current_hour_v();
			break;
		case M_SUB_SET_MIN:
			main_set_current_min_v();
			break;
		default:
			main_reset_stats_v();
			break;
	}

}

void main_set_current_hour_v()
{
	if(t_event_e == KEY_MOD)
	{
		main_chg_to_set_dur_min_v();
	}
	else if(t_event_e == KEY_INC)
	{
		main_cur_hour++;
		if(main_cur_hour >= 24)
		{
			main_cur_hour = 0;
		}
		DataCollection_set_time_v(main_cur_hour, main_cur_min);
		sprintf(main_cmd_bot, "%d : %d", main_cur_hour, main_cur_min);
	}
	else if(t_event_e == KEY_OK)
	{
		main_chg_to_set_cur_min_v();
	}
	else
	{
		main_chg_to_invalid_v();
	}
}

void main_set_current_min_v()
{
	if(t_event_e == KEY_MOD)
	{
		main_chg_to_idle_v();
	}
	else if(t_event_e == KEY_INC)
	{
		main_cur_min++;
		if(main_cur_min >= 60)
		{
			main_cur_min = 0;
		}
		DataCollection_set_time_v(main_cur_hour, main_cur_min);
		sprintf(main_cmd_bot, "%d : %d", main_cur_hour, main_cur_min);
	}
	else if(t_event_e == KEY_OK)
	{
		main_chg_to_set_cur_hour_v();
	}
	else
	{
		main_chg_to_invalid_v();
	}
}

void main_set_duration_v()
{
	switch (t_set_dur_stat)
	{
		case M_SUB_SET_MIN:
			main_set_duration_min_v();
			break;
		case M_SUB_SET_SEC:
			main_set_duration_sec_v();
			break;
		default:
			main_reset_stats_v();
			break;
	}

}

void main_set_duration_min_v()
{
	UWORD t_durtime_uw;
	if(t_event_e == KEY_MOD)
	{
		main_chg_to_test_act_v();
	}
	else if(t_event_e == KEY_INC)
	{
		main_set_dur_min ++;
		if(main_set_dur_min >= 60)
		{
			main_set_dur_min = 0;
		}
		t_durtime_uw = DataCollection_read_bk2_v()&0x00FF;
		t_durtime_uw |= (main_set_dur_min << 8);
		DataCollection_set_bk2_v(t_durtime_uw);
		sprintf(main_cmd_bot, "%d : %d", main_set_dur_min, main_set_dur_sec);

	}
	else if(t_event_e == KEY_OK)
	{
		main_chg_to_set_dur_sec_v();
	}
	else
	{
		main_chg_to_invalid_v();
	}
}

void main_set_duration_sec_v()
{
	UWORD t_durtime_uw;
	if(t_event_e == KEY_MOD)
	{
		main_chg_to_idle_v();
	}
	else if(t_event_e == KEY_INC)
	{
		main_set_dur_sec ++;
		if(main_set_dur_sec >= 60)
		{
			main_set_dur_sec = 0;
		}
		t_durtime_uw = DataCollection_read_bk2_v()&0xFF00;
		t_durtime_uw |= main_set_dur_sec;
		DataCollection_set_bk2_v(t_durtime_uw);
		sprintf(main_cmd_bot, "%d : %d", main_set_dur_min, main_set_dur_sec);

	}
	else if(t_event_e == KEY_OK)
	{
		main_chg_to_set_dur_min_v();
	}
	else
	{
		main_chg_to_invalid_v();
	}

}


void main_test_active_v()
{
	if(t_event_e == KEY_INC)
	{
		main_chg_to_test_deact_v();
	}
	else if (t_event_e == KEY_MOD)
	{
		main_chg_to_idle_v();
	}
	else
	{
		/* do nothing */
	}

}

void main_test_deactive_v()
{
	if(t_event_e == KEY_INC)
	{
		main_chg_to_test_act_v();
	}
	else if (t_event_e == KEY_MOD)
	{
		main_chg_to_idle_v();
	}
	else
	{
		/* do nothing */
	}
}

void main_reset_stats_v()
{
	t_main_stat = M_IDLE;
	t_set_act_stat = M_SUB_SET_HOUR;
	t_set_cur_stat = M_SUB_SET_HOUR;
	t_set_dur_stat = M_SUB_SET_MIN;
	t_idle_stat = M_SUB_IDLE_CUR;

}



main_sub_proc_stat main_idle_get_next_sub_stat(main_sub_proc_stat cur_stat)
{
	main_sub_proc_stat ret_stat;
	if (cur_stat == M_SUB_IDLE_CUR)
		ret_stat = M_SUB_IDLE_SET;
	else if(cur_stat == M_SUB_IDLE_SET)
		ret_stat = M_SUB_IDLE_DUR;
	else if(cur_stat == M_SUB_IDLE_DUR)
		ret_stat = M_SUB_IDLE_ACT;
	else if(cur_stat == M_SUB_IDLE_ACT )
	{
		ret_stat = cur_stat;
	}
	else
		ret_stat = M_SUB_IDLE_CUR;
	return ret_stat;
}


void main_chg_to_idle_v()
{
	t_main_stat = M_IDLE;
	t_idle_stat = M_SUB_IDLE_CUR;

	strcpy(main_cmd_top, main_cmd_idle_cur_top);

	sprintf(main_cmd_bot, "%d : %d", main_cur_hour, main_cur_min);

	motor_deactivate_v();

}

void main_chg_to_set_act_hour_v()
{
	t_main_stat = M_SET_ACT_TIME;
	t_set_act_stat = M_SUB_SET_HOUR;

	strcpy(main_cmd_top, main_cmd_set_act_hour_top);
	sprintf(main_cmd_bot, "%d : %d", main_set_act_hour, main_set_act_min);


}

void main_chg_to_set_act_min_v()
{
	t_main_stat = M_SET_ACT_TIME;
	t_set_act_stat = M_SUB_SET_MIN;

	strcpy(main_cmd_top, main_cmd_set_act_min_top);

	sprintf(main_cmd_bot, "%d : %d", main_set_act_hour, main_set_act_min);

}

void main_chg_to_set_cur_hour_v()
{
	t_main_stat = M_SET_CUR_TIME;
	t_set_cur_stat = M_SUB_SET_HOUR;

	strcpy(main_cmd_top, main_cmd_set_cur_hour_top);

	sprintf(main_cmd_bot, "%d : %d", main_cur_hour, main_cur_min);
}

void main_chg_to_set_cur_min_v()
{
	t_main_stat = M_SET_CUR_TIME;
	t_set_cur_stat = M_SUB_SET_MIN;

	strcpy(main_cmd_top, main_cmd_set_cur_min_top);

	sprintf(main_cmd_bot, "%d : %d", main_cur_hour, main_cur_min);
}

void main_chg_to_set_dur_min_v()
{
	t_main_stat = M_SET_DUR_TIME;
	t_set_dur_stat = M_SUB_SET_MIN;

	strcpy(main_cmd_top, main_cmd_set_dur_min_top);

	sprintf(main_cmd_bot, "%d : %d", main_set_dur_min, main_set_dur_sec);
}

void main_chg_to_set_dur_sec_v()
{
	t_main_stat = M_SET_DUR_TIME;
	t_set_dur_stat = M_SUB_SET_SEC;

	strcpy(main_cmd_top, main_cmd_set_dur_sec_top);

	sprintf(main_cmd_bot, "%d : %d", main_set_dur_min, main_set_dur_sec);
}

void main_chg_to_test_act_v()
{
	t_main_stat = M_SET_TST_ACT;
	motor_activate_v();

	strcpy(main_cmd_top, main_cmd_tst_act_top);

	strcpy(main_cmd_bot, main_cmd_tst_act_bot);

}

void main_chg_to_test_deact_v()
{
	t_main_stat = M_SET_TST_DEACT;
	motor_deactivate_v();
	strcpy(main_cmd_top, main_cmd_tst_deact_top);

	strcpy(main_cmd_bot, main_cmd_tst_deact_bot);
}

void main_chg_to_invalid_v()
{

}
