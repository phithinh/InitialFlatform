#ifndef _MAIN_PROCESS_PRI_H_
#define _MAIN_PROCESS_PRI_H_

#include "main_process_typ.h"

/*********************************************************
* private variables
*
*********************************************************/
main_proc_stat t_main_stat;
main_sub_proc_stat t_idle_stat;
main_sub_proc_stat t_set_act_stat;
main_sub_proc_stat t_set_cur_stat;
main_sub_proc_stat t_set_dur_stat;

/*
 * for command displaying
 */
const char main_cmd_idle_cur_top[16] = "Current time";

const char main_cmd_idle_set_top[16] = "Set time";

const char main_cmd_idle_dur_top[16] = "Set duration";

const char main_cmd_idle_act_top[16] = "I'm doing job";
const char main_cmd_idle_act_bot[16] = "Dont disturb 8)";

const char main_cmd_set_act_hour_top[16] = "Set act hour";
const char main_cmd_set_act_min_top[16] = "Set act min";

const char main_cmd_set_cur_hour_top[16] = "Set cur hour";
const char main_cmd_set_cur_min_top[16] = "Set cur min";

const char main_cmd_set_dur_min_top[16] = "Set dur min";
const char main_cmd_set_dur_sec_top[16] = "Set dur sec";

const char main_cmd_tst_act_top[16] = "Testing";
const char main_cmd_tst_act_bot[16] = "Activating";

const char main_cmd_tst_deact_top[16] = "Testing";
const char main_cmd_tst_deact_bot[16] = "Deactivating";

/*
 * For real time clock
 *
 */
char main_cur_hour;
char main_cur_min;
char main_cur_sec;

/*
 * For interface variables with BKP registers
 *
 */
char main_set_act_hour;
char main_set_act_min;

char main_set_dur_min;
char main_set_dur_sec;


/*
 * for idling counter
 */
int main_idle_tmr_cnt;

/*
 * For activation flag
 */
char main_is_activating_done;

/*********************************************************
* private macros
*
*********************************************************/
#define CORE_CYC_TMR	10 								/* milliseconds */

#define CORE_CYC_CNT	(1000 / CORE_CYC_TMR)			/* counter to reach 1 second */

#define DEFAULT_SET_CNT (12 * 60 * 60 * CORE_CYC_CNT)	/* 12 hours after reset */
#define DEFAULT_DUR_CNT	(30 * CORE_CYC_CNT) 			/* 30 seconds*/

#define IDLE_SUB_CYC	(20 * CORE_CYC_CNT) 				/* 2 seconds */


/********************************************************
* private functions
*********************************************************/

void main_proc_idle_v();

void main_set_activation_time_v();

void main_set_activation_hour_v();

void main_set_activation_min_v();

void main_set_current_time_v();

void main_set_current_hour_v();

void main_set_current_min_v();

void main_set_duration_v();

void main_set_duration_min_v();

void main_set_duration_sec_v();

void main_test_active_v();

void main_test_deactive_v();

void main_reset_stats_v();

void main_chg_to_idle_v();

void main_chg_to_set_act_hour_v();

void main_chg_to_set_act_min_v();

void main_chg_to_set_cur_hour_v();

void main_chg_to_set_cur_min_v();

void main_chg_to_set_dur_min_v();

void main_chg_to_set_dur_sec_v();

void main_chg_to_test_act_v();

void main_chg_to_test_deact_v();

void main_chg_to_invalid_v();

main_sub_proc_stat main_idle_get_next_sub_stat(main_sub_proc_stat cur_stat);

#endif
