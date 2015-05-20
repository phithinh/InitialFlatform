/*
 * OS.c
 *
 *  Created on: Nov 5, 2014
 *      Author: Phi Thinh
 */

/* Include header file */
//#include <misc.h>
#include <environment.h>
#include <OS_Layer.h>

#include <stm32f10x_wwdg.h>
#include "OS.h"

//void vUserTask1ms( void *pvParameters ){
//	portTickType xLastWakeTime;
//	xLastWakeTime = xTaskGetTickCount();
//
//	while(1){
//		WWDG_ClearFlag();
//		//environment_T1_process_v();
//		/* Task delay */
//		vTaskDelayUntil(&xLastWakeTime,USER_TASK_1MS_DURATION); /* 1ms Process Task */
//	};
//}
void vUserTask10ms( void *pvParameters ){
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1){
		environment_T10_v();
		/* Task delay */
		vTaskDelayUntil(&xLastWakeTime,USER_TASK_10MS_DURATION); /* 10ms Process Task */
	};
}
void vUserTask10msLow( void *pvParameters ){
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while(1){
		environment_background_v();
		/* Task delay */
		//vTaskDelayUntil(&xLastWakeTime,USER_TASK_10MSLOW_DURATION); /* 10ms Process Task */
	};
}

void OS_Init(void)
{
//	#warning: [BUILD_WARNING]: configCPU_CLOCK_HZ base on the clock when Init CPU, configTICK_RATE_HZ base on the clock in the file FreeRTOSCongig.h
	/* Create Task */
//	OS_xTaskCreate(vUserTask1ms, "USER_TASK_1ms", USER_TASK_1MS_STACK_SIZE, NULL, USER_TASK_1MS_PRIORITY, NULL );
	OS_xTaskCreate(vUserTask10ms, "USER_TASK_10ms", USER_TASK_10MS_STACK_SIZE, NULL, USER_TASK_10MS_PRIORITY, NULL );
	OS_xTaskCreate(vUserTask10msLow, "USER_TASK_10msLow", USER_TASK_10MSLOW_STACK_SIZE, NULL, USER_TASK_10MSLOW_PRIORITY, NULL );

}

void OS_Start(void){
	/* Start the scheduler. */
	OS_vTaskScheduler();
}
