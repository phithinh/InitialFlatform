/*
 * OS.h
 *
 *  Created on: Nov 5, 2014
 *      Author: Phi Thinh
 */

#ifndef OS_H_
#define OS_H_

/* Task priorities. */
#define USER_TASK_1MS_PRIORITY			( tskIDLE_PRIORITY + 3 )	//this is hard-realtime task
#define USER_TASK_10MS_PRIORITY			( tskIDLE_PRIORITY + 2 )
#define USER_TASK_10MSLOW_PRIORITY			( tskIDLE_PRIORITY + 1 )

// Task duration

#define USER_TASK_1MS_DURATION			( 1 )	//this is hard-realtime task
#define USER_TASK_10MS_DURATION			( 10 )
#define USER_TASK_10MSLOW_DURATION			( 10 )


/* The check task uses the sprintf function so requires a little more stack. */
#define USER_TASK_1MS_STACK_SIZE		( ( unsigned short ) 256 )
#define USER_TASK_10MS_STACK_SIZE		( ( unsigned short ) 256 )
#define USER_TASK_10MSLOW_STACK_SIZE		( ( unsigned short ) 1024 )

/* Extern prototype function */
void vUserTask1ms( void *pvParameters );
void vUserTask10ms( void *pvParameters );
void vUserTask10msLow( void *pvParameters );

void OS_Init(void);
void OS_Start(void);
#endif /* OS_H_ */
