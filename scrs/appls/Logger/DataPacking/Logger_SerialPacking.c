/*
 * Logger_SerialPacking.c
 *
 *  Created on: Nov 15, 2014
 *      Author: Phi Thinh
 */


/*
 * Logger_SerialPacking.c
 *
 *  Created on: Nov 1, 2014
 *      Author: Phi Thinh
 */
#include <compiler.h>
#include "../Logger_adapts.h"
#include "../SD_Logger/Logger.h"

#include "DataPacking.h"

void Logger_SerialPacking_v(void){
	SWORD t_NoRemainingBytes_sw = 0;
	UBYTE t_FreeByteInRam_ub = 0;
	UBYTE t_StartIdx_ub = 0;
	if(VDB_DataCollection_rx_serial_status == RX_SERIAL_VALID){
		t_NoRemainingBytes_sw = (SWORD)(VDB_DataCollection_rx_serial_cnt_ub+1);
		while (1){
			t_FreeByteInRam_ub = Logger_RamSector_NoFreeBytes_ub();
			t_NoRemainingBytes_sw = (SWORD)(t_NoRemainingBytes_sw - (SWORD)t_FreeByteInRam_ub);
			if(t_NoRemainingBytes_sw<=0){
				Logger_PutStringDataToRam_v((char*)&VDB_DataCollection_rx_serial_data_aub[t_StartIdx_ub],(unsigned short)(VDB_DataCollection_rx_serial_cnt_ub - t_StartIdx_ub));
				Logger_PutStringDataToRam_v("\n",1);
				return;
			} else {
				Logger_PutStringDataToRam_v((char*)&VDB_DataCollection_rx_serial_data_aub[t_StartIdx_ub],(unsigned short)t_FreeByteInRam_ub);
				t_StartIdx_ub =(UBYTE) (t_StartIdx_ub + t_FreeByteInRam_ub);
				if(Logger_RamSector_getNew_ub()){
					return;
				}
			}
		}
	}
}

UBYTE Logger_SerialPacking_FileInit_ub(void){
	if(Logger_RamSector_SizeChecking(7)){
		return 1;
	}
	Logger_PutStringDataToRam_v("serial\n", 7);
	return 0;
}

