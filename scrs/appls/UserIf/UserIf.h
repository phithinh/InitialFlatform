/*
 * UserIf.h
 *
 *  Created on: Jan 18, 2015
 *      Author: Phi Thinh
 */

#ifndef USERIF_H_
#define USERIF_H_
#include "button_scan/button_scan_pub.h"
#include "lcd/lcd.h"
#include "relay_controller/relay_controller.h"

void UserIf_Init(void);
void UserIf_Input_main(void);

void UserIf_Ouput_main(void);

void UserIf_Proc_main(void);

void UserIf_OuputLow_main(void);
#endif /* USERIF_H_ */
