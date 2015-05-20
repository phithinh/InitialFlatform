#ifndef ___ADCDMA_H
#define ___ADCDMA_H
//Prototype
#define NumOfChanel     3

#define ADC1_DR    		((uint32_t)0x4001244C)
//GPIO define
/*Analog input pin*/
#define ANA1_PIN                    GPIO_Pin_0
#define ANA1_PORT                   GPIOA
#define ANA1_CLK                    RCC_APB2Periph_GPIOA  

#define ANA2_PIN                         GPIO_Pin_5
#define ANA2_PORT                   GPIOA
#define ANA2_CLK                    RCC_APB2Periph_GPIOA  

#define ANA3_PIN                         GPIO_Pin_1
#define ANA3_PORT                   GPIOA
#define ANA3_CLK                    RCC_APB2Periph_GPIOA  
//==============================================================
typedef struct
{
uint16  u16Temp;
uint16  u16HVDC;
uint16  u16DcCurrent;

}_StrAnalog;
//==============================================================
#ifdef ___ADCDMA_C
_StrAnalog StrAnalog;
#else
extern _StrAnalog StrAnalog;
#endif
//==============================================================

void ADC_DMA_Init(void);
uint16* ReadAnalogInput(void);// Return data to buffer

#endif
