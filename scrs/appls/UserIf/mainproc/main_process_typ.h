#ifndef _MAIN_PROCESS_TYP_H_
#define _MAIN_PROCESS_TYP_H_


typedef enum  {
	M_IDLE,
	M_SET_ACT_TIME,
	M_SET_CUR_TIME,
	M_SET_DUR_TIME,
	M_SET_TST_ACT,
	M_SET_TST_DEACT,
	M_INVALID
}main_proc_stat;

typedef enum  {
	M_SUB_IDLE_CUR,
	M_SUB_IDLE_SET,
	M_SUB_IDLE_DUR,
	M_SUB_IDLE_ACT,
	M_SUB_SET_HOUR,
	M_SUB_SET_MIN,
	M_SUB_SET_SEC,
	M_SUB_INVALID
}main_sub_proc_stat;


#endif
