/*
 * inv_com.c
 *
 *  Created on: May 17, 2015
 *      Author: Thinh
 */
#include <math.h>
#include <string.h>
#include <compiler.h>
#include "../inverter_adpts.h"
#include "../inv_ctr/inverter_controller_pri.h"

#include "inv_com.h"

void inverter_com_send_threshold_v(void){
	float t_val_f;
	char t_data_aub[5];

	inverter_send_string_v ("\r\nlowU:",7);
	t_val_f = ((float) StrFeedbackThreshold.LowVoltageDCThreshold * 3.3) / 4096;
	ftoa(t_val_f,t_data_aub,3);
	inverter_send_string_v(t_data_aub,5);

	inverter_send_string_v (" highU:",7);
	t_val_f = ((float) StrFeedbackThreshold.HighVoltageDCThreshold * 3.3) / 4096;
	ftoa(t_val_f,t_data_aub,3);
	inverter_send_string_v(t_data_aub,5);

	inverter_send_string_v (" lowI:",6);
	t_val_f = ((float) StrFeedbackThreshold.LowCurrentThreshold * 3.3) / 4096;
	ftoa(t_val_f,t_data_aub,3);
	inverter_send_string_v(t_data_aub,5);
	
	inverter_send_string_v (" highI:",7);
	t_val_f = ((float) StrFeedbackThreshold.HighCurrentThreshold * 3.3) / 4096;
	ftoa(t_val_f,t_data_aub,3);
	inverter_send_string_v(t_data_aub,5);
}
void inverter_com_send_cur_data_v(void){
	float t_val_f;
	char t_data_aub[5];

	inverter_send_string_v ("\r\nIdc:",6);
	t_val_f = ((float) u16AvgCurrent * 3.3) / 4096;
	ftoa(t_val_f,t_data_aub,3);
	inverter_send_string_v(t_data_aub,5);

	inverter_send_string_v (" Vdc:",5);
	t_val_f = ((float) u16AvgVol * 3.3) / 4096;
	ftoa(t_val_f,t_data_aub,3);
	inverter_send_string_v(t_data_aub,5);

	inverter_send_string_v (" Temp:",6);;
	t_val_f = ((float) u16AvgTemp * 3.3) / 4096;
	ftoa(t_val_f,t_data_aub,3);
	inverter_send_string_v(t_data_aub,5);
}

void inverter_send_string_v(char * p_data_pub, unsigned char p_lenght_ub){
	for (;p_lenght_ub-->0;){
		l_inv_sent_char_v(*p_data_pub);
		p_data_pub++;
	}
}
// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
int ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        i += intToStr((int)fpart, res + i + 1, afterpoint);
    }
    return i;
}
