#ifndef PLATFORMTYPE_H_
#define PLATFORMTYPE_H_
#define MAX_VALUE_32b           0xFFFFFFFF
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#define TIME_MS(x)	x
#define TIME_SEC(x)	(x*1000)
#define ACTIVE          0x55
#define DEACTIVE        0x00

typedef unsigned char           uint8;
typedef signed char             sint8;
typedef unsigned short          uint16;
typedef signed short            sint16;
typedef unsigned int            uint32;
typedef signed int              sint32;
typedef uint8 const             ucint8; 
typedef char const              ROM_Str;
typedef ROM_Str**               pp_ROM_Str;
typedef ROM_Str*                p_ROM_Str;
typedef enum _enumbool{eFALSE=0,eTRUE=!eFALSE} enumbool;
typedef enum _enumState{eENABLE=1,eDISABLE=!eENABLE} enumState;
typedef enum _enumBusStatus{eLOW_LEVEL = 0,eHIGH_LEVEL=!eLOW_LEVEL} enumBusStatus;
typedef enum _enumLogicState{OFF=0,ON=1}enumLogicState;
typedef enum _enumLogicYesNoState{NO=0,YES=1}enumLogicYesNoState;
typedef enum _enumValidStatus
{
    eVALID = 0xAA,
    eNONE_VALID = 0xFF,
    ePASS_CHECKSUM = 0x01,
    eERROR_CHECKSUM = 0x02
} enumValidStatus;

#pragma pack(1)
typedef struct _TIMEOUT
{
    uint32      iStart;
    uint32      iReach;
    enumbool    Over;
    enumbool    RUNNING;
    enumbool    ENABLE;
}TIMEOUT;
#pragma pack()
#pragma pack(1)
/**
* Date and time data
* @see nmea_time_now
*/
typedef struct _TIME
{
    uint16    year;       /**< Years since 2000 */
    uint8     mon;        /**< Months since January - [0,11] */
    uint8     day;        /**< Day of the month - [1,31] */
    uint8     hour;       /**< Hours since midnight - [0,23] */
    uint8     min;        /**< Minutes after the hour - [0,59] */
    uint8     sec;        /**< Seconds after the minute - [0,59] */
    uint16    hsec;       /**< Hundredth part of second - [0,99] */
    sint8     UTC;        /**< Greenwich Mean Time - [-4*12,+4*12] */
}TIME;
#pragma pack()
#pragma pack(1)
typedef struct _TIMETRAP
{
    uint32      Cycle;  /*Unit is milisecond*/
    uint32      NextCyc;
    enumbool    TRAP;
    enumbool    OVER;
}TIMETRAP;
#pragma pack()

#ifndef Null
#define Null                    0
#endif
#ifndef null
#define null                    0
#endif
#ifndef NULL
#define NULL                    0
#endif

#ifndef Rom_Req
typedef uint8 const Rom_Req ;
#endif
typedef void (*fFunction)(void);
#endif /*PLATFORMTYPE_H_*/
