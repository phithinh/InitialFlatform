/**
******************************************************************************
* @file    mass_mal.c
* @author  MCD Application Team
* @version V4.0.0
* @date    21-January-2013
* @brief   Medium Access Layer interface
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        http://www.st.com/software_license_agreement_liberty_v2
*
* Unless required by applicable law or agreed to in writing, software 
* distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include <compiler.h>
#include <stm32f10x.h>
#include "mass_mal.h"
#include "../SDCardSPI/sd_spi_stm32.h"
#include "../SDCardSPI/diskio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{
    
    switch (lun)
    {
    case 0:
//                Status = SD_WriteMultiBlocks((uint8_t*)Writebuff, Memory_Offset, Transfer_Length,1);
        Status = ff_memory_write(0,(uint8_t*)Writebuff,Memory_Offset,1);
        break;
        
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
    switch (lun)
    {
    case 0:
//                SD_ReadMultiBlocks((uint8_t*)Readbuff, Memory_Offset, Transfer_Length, 1);
        ff_memory_read(lun,(uint8_t*)Readbuff, Memory_Offset,1);
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_GetStatus (uint8_t lun)
{
    uint8_t CSD_Tab[17];
    SD_CSD SD_csd;
    uint32_t DeviceSizeMul = 0;
    
    if (lun == 0)
    {
        uint32_t temp_block_mul = 0;
//        SD_GetCSDRegister(&SD_csd);
        disk_ioctl(lun,MMC_GET_CSD,CSD_Tab);
        /*Convert to CSD Structure*/
        /*!< Byte 0 */
        SD_csd.CSDStruct = (CSD_Tab[0] & 0xC0) >> 6;
        SD_csd.SysSpecVersion = (CSD_Tab[0] & 0x3C) >> 2;
        SD_csd.Reserved1 = CSD_Tab[0] & 0x03;
        
        /*!< Byte 1 */
        SD_csd.TAAC = CSD_Tab[1];
        
        /*!< Byte 2 */
        SD_csd.NSAC = CSD_Tab[2];
        
        /*!< Byte 3 */
        SD_csd.MaxBusClkFrec = CSD_Tab[3];
        
        /*!< Byte 4 */
        SD_csd.CardComdClasses = CSD_Tab[4] << 4;
        
        /*!< Byte 5 */
        SD_csd.CardComdClasses |= (CSD_Tab[5] & 0xF0) >> 4;
        SD_csd.RdBlockLen = CSD_Tab[5] & 0x0F;
        
        /*!< Byte 6 */
        SD_csd.PartBlockRead = (CSD_Tab[6] & 0x80) >> 7;
        SD_csd.WrBlockMisalign = (CSD_Tab[6] & 0x40) >> 6;
        SD_csd.RdBlockMisalign = (CSD_Tab[6] & 0x20) >> 5;
        SD_csd.DSRImpl = (CSD_Tab[6] & 0x10) >> 4;
        SD_csd.Reserved2 = 0; /*!< Reserved */
        
        SD_csd.DeviceSize = (CSD_Tab[6] & 0x03) << 10;
        
        /*!< Byte 7 */
        SD_csd.DeviceSize |= (CSD_Tab[7]) << 2;
        
        /*!< Byte 8 */
        SD_csd.DeviceSize |= (CSD_Tab[8] & 0xC0) >> 6;
        
        SD_csd.MaxRdCurrentVDDMin = (CSD_Tab[8] & 0x38) >> 3;
        SD_csd.MaxRdCurrentVDDMax = (CSD_Tab[8] & 0x07);
        
        /*!< Byte 9 */
        SD_csd.MaxWrCurrentVDDMin = (CSD_Tab[9] & 0xE0) >> 5;
        SD_csd.MaxWrCurrentVDDMax = (CSD_Tab[9] & 0x1C) >> 2;
        SD_csd.DeviceSizeMul = (CSD_Tab[9] & 0x03) << 1;
        /*!< Byte 10 */
        SD_csd.DeviceSizeMul |= (CSD_Tab[10] & 0x80) >> 7;
        
        SD_csd.EraseGrSize = (CSD_Tab[10] & 0x40) >> 6;
        SD_csd.EraseGrMul = (CSD_Tab[10] & 0x3F) << 1;
        
        /*!< Byte 11 */
        SD_csd.EraseGrMul |= (CSD_Tab[11] & 0x80) >> 7;
        SD_csd.WrProtectGrSize = (CSD_Tab[11] & 0x7F);
        
        /*!< Byte 12 */
        SD_csd.WrProtectGrEnable = (CSD_Tab[12] & 0x80) >> 7;
        SD_csd.ManDeflECC = (CSD_Tab[12] & 0x60) >> 5;
        SD_csd.WrSpeedFact = (CSD_Tab[12] & 0x1C) >> 2;
        SD_csd.MaxWrBlockLen = (CSD_Tab[12] & 0x03) << 2;
        
        /*!< Byte 13 */
        SD_csd.MaxWrBlockLen |= (CSD_Tab[13] & 0xC0) >> 6;
        SD_csd.WriteBlockPaPartial = (CSD_Tab[13] & 0x20) >> 5;
        SD_csd.Reserved3 = 0;
        SD_csd.ContentProtectAppli = (CSD_Tab[13] & 0x01);
        
        /*!< Byte 14 */
        SD_csd.FileFormatGrouop = (CSD_Tab[14] & 0x80) >> 7;
        SD_csd.CopyFlag = (CSD_Tab[14] & 0x40) >> 6;
        SD_csd.PermWrProtect = (CSD_Tab[14] & 0x20) >> 5;
        SD_csd.TempWrProtect = (CSD_Tab[14] & 0x10) >> 4;
        SD_csd.FileFormat = (CSD_Tab[14] & 0x0C) >> 2;
        SD_csd.ECC = (CSD_Tab[14] & 0x03);
        
        /*!< Byte 15 */
        SD_csd.CSD_CRC = (CSD_Tab[15] & 0xFE) >> 1;
        SD_csd.Reserved4 = 1;
        
        DeviceSizeMul = SD_csd.DeviceSizeMul + 2;
        temp_block_mul = (1 << SD_csd.RdBlockLen)/ 512;
        Mass_Block_Count[0] = ((SD_csd.DeviceSize + 1) * (1 << (DeviceSizeMul))) * temp_block_mul;
        Mass_Block_Size[0] = 512;
        Mass_Memory_Size[0] = (Mass_Block_Count[0] * Mass_Block_Size[0]);
        Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
        
        return MAL_OK;
        
    }
    
    return MAL_FAIL;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

