/*
 * inverter_controller_adapts.h
 *
 *  Created on: May 16, 2015
 *      Author: Thinh
 */

#ifndef INVERTER_CONTROLLER_ADAPTS_H_
#define INVERTER_CONTROLLER_ADAPTS_H_

#include <gpio_pub.h>

#define LED1_ON    digital_out_set_v(LED1,1)
#define LED1_OFF   digital_out_set_v(LED1,0)
#define LED1_TOG   digital_out_toggle_v(LED1)

#define LED2_ON    digital_out_set_v(LED2,1)
#define LED2_OFF   digital_out_set_v(LED2,0)
#define LED2_TOG   digital_out_toggle_v(LED2)

#define LED3_ON    digital_out_set_v(LED3,1)
#define LED3_OFF   digital_out_set_v(LED3,0)
#define LED3_TOG   digital_out_toggle_v(LED3)

#define RELAY_ON   digital_out_set_v(RELAY,1)
#define RELAY_OFF  digital_out_set_v(RELAY,0)

#define DipSw1     digital_in_read(DIPSW1)
#define DipSw2     digital_in_read(DIPSW2)
#define Btn1       digital_in_read(BTN1)
#define Btn2       digital_in_read(BTN2)
#define SDIn       digital_in_read(IGBT_SD_IN)

#define SD_OFF     digital_out_set_v(IGBT_SD_OUT,1)
#define SD_ON      digital_out_set_v(IGBT_SD_OUT,0)

#endif /* INVERTER_CONTROLLER_ADAPTS_H_ */
