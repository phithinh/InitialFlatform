/*
 * encoder_pub.h
 *
 *  Created on: Mar 9, 2014
 *      Author: TV
 */

#ifndef ENCODER_PUB_H_
#define ENCODER_PUB_H_

extern struct {
	BOOL pre_statusA_b;
	BOOL pre_statusB_b;
	BOOL dir_status_b;
	SLONG value_sl;
} encoder_data_st;

void encoder_IRQ_A_Handler(void);
void encoder_IRQ_A_Handler(void);
#endif /* ENCODER_PUB_H_ */
