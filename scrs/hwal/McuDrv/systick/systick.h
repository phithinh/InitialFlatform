/*
 * systick.h
 *
 *  Created on: Mar 16, 2014
 *      Author: TV
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include <general_define.h>

#ifdef __SYSTICK
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN SLONG g_systick_sl;

void systick_init(void);

#undef __SYSTICK

#endif /* SYSTICK_H_ */
