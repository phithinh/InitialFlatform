#ifndef  __SVPWM_H
#define __SVPWM_H
#define ScaleFrequency     1

//void SVPWM(uint16 Vref,uint16 Vdc,uint8 Phase);


#define FORWARD                         1
#define REVERSE                         0
#define RUN                             1
#define STOP                            1
#define STOPEMER                        1

#define MAX_DUTY                        98
#define PERIOD                          1000//10KHZ
#define DEADTIME                        10
#define Pi                              314
#define MOTORMAXSPEED                   2680
#define MOTORMINSPEED                   64000

#define V_DC_IN               310
#define V_F_Coff        (V_DC_IN/(5*1.414))//310/(50*sqrt(2))
#define V_RMS_OUT       (V_DC_IN/1.732)//310/(sqrt(3))

#define PMW1H_PIN                    GPIO_Pin_6
#define PMW1H_PORT                   GPIOC
#define PMW1H_CLK                    RCC_APB2Periph_GPIOC

#define PMW1L_PIN                    GPIO_Pin_7
#define PMW1L_PORT                   GPIOA
#define PMW1L_CLK                    RCC_APB2Periph_GPIOA

#define PMW2H_PIN                    GPIO_Pin_7
#define PMW2H_PORT                   GPIOC
#define PMW2H_CLK                    RCC_APB2Periph_GPIOC

#define PMW2L_PIN                    GPIO_Pin_0
#define PMW2L_PORT                   GPIOB
#define PMW2L_CLK                    RCC_APB2Periph_GPIOB

#define PMW3H_PIN                    GPIO_Pin_8
#define PMW3H_PORT                   GPIOC
#define PMW3H_CLK                    RCC_APB2Periph_GPIOC

#define PMW3L_PIN                    GPIO_Pin_1
#define PMW3L_PORT                   GPIOB
#define PMW3L_CLK                    RCC_APB2Periph_GPIOB

#define TIMER_PWM                  TIM1
#define TIMER_PWM_CLK              RCC_APB2Periph_TIM1
#define TIMER_PWM_IRQ              TIM1_UP_IRQn
#define TimerPWMIrqHandler         TIM1_UP_IRQHandler

#define REMAP_ENABLE               GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE)

#define TIMER_FRE_OUTPUT            TIM2
#define TIMER_FRE_OUTPUT_CLK        RCC_APB1Periph_TIM2    
#define TIMER_FRE_OUTPUT_IRQ        TIM2_IRQn
#define TIMER_FRE_OUTPUT_PERIOD     TIM2->ARR
#define TimerFreOutIrqHandler       TIM2_IRQHandler
//==========================================================

typedef struct
{
uint16  FreOutputMotor;
uint16  Hvdc;
uint16  Vref;
uint8   ModulIndex;
uint8   Run;
uint8   Dir;
uint8   StopEmer;
uint8   SoftStartTime;
uint8   Rate;
} _SVPWM;
//==========================================================
#ifdef _SVPWM_M
_SVPWM SVPWM;
#else
extern _SVPWM SVPWM;
#endif


//==========================================================
void TimerPWMIrqHandler(void);
void TimerFreOutIrqHandler(void);
void PWMConfig(void);
void UpdateDutyPWM(uint16 DUTY1,uint16 DUTY2,uint16 DUTY3);
void SVPWMInit(void);
void TimerFreOutConfig(void);
uint8 SectorInd (uint16 Angel);
///////////////////////////////////////////////////////////
void UpdateSpeedMotor(uint16 Speed);

#endif
