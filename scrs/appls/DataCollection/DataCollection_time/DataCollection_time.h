/*
 * DataCollection_time.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */

#ifndef DATACOLLECTION_TIME_H_
#define DATACOLLECTION_TIME_H_

void DataCollection_time_init_v(void);
void DataCollection_time_update_v(void);

void DataCollection_set_time_v(UBYTE hour, UBYTE min);
void DataCollection_set_bk1_v(UWORD p_data_uw);
void DataCollection_set_bk2_v(UWORD p_data_uw);
UWORD DataCollection_read_bk1_v(void);
UWORD DataCollection_read_bk2_v(void);
#endif /* DATACOLLECTION_TIME_H_ */
