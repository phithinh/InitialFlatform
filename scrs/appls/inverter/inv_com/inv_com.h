/*
 * inv_com.h
 *
 *  Created on: May 17, 2015
 *      Author: Thinh
 */

#ifndef INV_COM_H_
#define INV_COM_H_

void inverter_com_send_threshold_v(void);
void inverter_com_send_cur_data_v(void);
void inverter_send_string_v(char * p_data_pub, unsigned char p_lenght_ub);
void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
int ftoa(float n, char *res, int afterpoint);

#endif /* INV_COM_H_ */
