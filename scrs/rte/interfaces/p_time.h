/*
 * p_time.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Phi Thinh
 */

#ifndef P_TIME_H_
#define P_TIME_H_
#include <compiler.h>

typedef struct
{
    uint16    year;       /**< Years since 2000 */
    uint16    hsec;       /**< Hundredth part of second - [0,99] */
    uint8     mon;        /**< Months since January - [0,11] */
    uint8     day;        /**< Day of the month - [1,31] */
    uint8     hour;       /**< Hours since midnight - [0,23] */
    uint8     min;        /**< Minutes after the hour - [0,59] */
    uint8     sec;        /**< Seconds after the minute - [0,59] */
    sint8     UTC;        /**< Greenwich Mean Time - [-4*12,+4*12] */
}DEF_TIME_ST;


#endif /* P_TIME_H_ */
