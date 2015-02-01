/* Martin Thomas 4/2009 */

#include "integer.h"
#include "fattime.h"
#include "stm32f10x.h"

DWORD get_fattime (void)
{
	#if 0
    RTC_TIME t;
    DWORD date;
    
    RTC_GetTime(&t);
    t.year-=1980;
    
    date = 0;
    date = (t.year<< 25) | (t.mon<<21) | (t.day<<16)|\
            (t.hour<<11) | (t.min<<5) | (t.sec>>1);

    return date;
#else
	return 0;
#endif  
}

