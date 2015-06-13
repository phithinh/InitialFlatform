/*
 * net.c
 *
 *  Created on: Apr 22, 2014
 *      Author: TV
 */
#include <general_define.h>
#include <serial_com.h>
#include "net.h"

#include "net_adpts.h"

void net_init_v(void){
  serial_com_init_v();
}
void net_T10_v(void){
	serial_com_main();
}

void net_background_v(void)
{
}

