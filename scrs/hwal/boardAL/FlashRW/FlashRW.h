#ifndef __FLASHRW__
#define __FLASHRW__

typedef struct
{
uint8 SysParameter[2048];
//uint32 crc;
}SYS_PARAMETER;
void SaveSysParameter(SYS_PARAMETER* SYS,uint8 Page);
//Example for read data: memcpy(&analRec,(uint32*)FW_DECRIP_START_ADDR,sizeof(StrAnalog));
//SaveSysParameter((SYS_PARAMETER*)&StrAnalogBuffer);
#endif
