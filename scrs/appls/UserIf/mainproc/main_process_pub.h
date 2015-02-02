#ifndef _MAIN_PROCESS_PUB_H_
#define _MAIN_PROCESS_PUB_H_

/*********************************************************
* provided variables
*
*********************************************************/
#ifdef MAIN_PROCESS
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN char main_cmd_top[16];
EXTERN char main_cmd_bot[16];


/*********************************************************
* provided run-able
*
*********************************************************/
void main_init_v();
void main_process_v();


#undef EXTERN
#endif
