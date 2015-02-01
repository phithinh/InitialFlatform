/*
 * relay_status.h
 *
 *  Created on: Apr 19, 2014
 *      Author: TV
 */

#ifndef RELAY_STATUS_H_
#define RELAY_STATUS_H_

typedef struct{
	unsigned relay_0:1;
	unsigned relay_1:1;
	unsigned relay_2:1;
	unsigned relay_3:1;
	unsigned relay_4:1;
	unsigned relay_5:1;
	unsigned relay_6:1;
	unsigned relay_7:1;
	unsigned relay_8:1;
	unsigned relay_9:1;
	unsigned relay_10:1;
	unsigned relay_11:1;
	unsigned relay_12:1;
	unsigned relay_13:1;
	unsigned relay_14:1;
	unsigned relay_15:1;
	unsigned relay_16:1;
	unsigned relay_17:1;
	unsigned relay_18:1;
	unsigned relay_19:1;
	unsigned relay_20:1;
	unsigned relay_21:1;
	unsigned relay_22:1;
	unsigned relay_23:1;
	unsigned reserver:8;
}RELAY_STATUS_ST;


#endif /* RELAY_STATUS_H_ */
