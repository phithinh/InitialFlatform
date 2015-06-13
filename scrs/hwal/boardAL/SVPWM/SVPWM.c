#include "stm32f10x.h"
#include <general_define.h>
#define _SVPWM_M
#include "SVPWM.h"

uint16 TimerCount = 0;
uint16 Alpha = 0;
uint16 Alpha1 = 0;
uint16 Alpha2 = 0;
uint16 Ta = 0;
uint16 Tb = 0;
uint16 T0 = 0;
uint16 DutyPWM1[60] = { 895, 912, 923, 931, 933, 931, 923, 912, 895, 875, 805,
		732, 656, 579, 500, 422, 344, 269, 195, 125, 105, 89, 77, 70, 67, 70,
		77, 89, 105, 125, 105, 89, 77, 70, 67, 70, 77, 89, 105, 125, 195, 269,
		344, 422, 500, 579, 656, 732, 805, 875, 895, 912, 923, 931, 933, 931,
		923, 912, 895, 875 };
uint16 DutyPWM2[60] = { 195, 269, 344, 422, 500, 579, 656, 732, 805, 875, 895,
		912, 923, 931, 933, 931, 923, 912, 895, 875, 895, 912, 923, 931, 933,
		931, 923, 912, 895, 875, 805, 732, 656, 579, 500, 422, 344, 269, 195,
		125, 105, 89, 77, 70, 67, 70, 77, 89, 105, 125, 105, 89, 77, 70, 67, 70,
		77, 89, 105, 125 };
uint16 DutyPWM3[60] = { 105, 89, 77, 70, 67, 70, 77, 89, 105, 125, 105, 89, 77,
		70, 67, 70, 77, 89, 105, 125, 195, 269, 344, 422, 500, 579, 656, 732,
		805, 875, 895, 912, 923, 931, 933, 931, 923, 912, 895, 875, 895, 912,
		923, 931, 933, 931, 923, 912, 895, 875, 805, 732, 656, 579, 500, 422,
		344, 269, 195, 125 };
uint16 SinTable[314] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120,
		130, 140, 149, 159, 169, 179, 189, 199, 208, 218, 228, 238, 247, 257,
		267, 276, 286, 296, 305, 315, 324, 333, 343, 352, 362, 371, 380, 389,
		399, 408, 417, 426, 435, 444, 453, 462, 471, 479, 488, 497, 506, 514,
		523, 531, 540, 548, 556, 565, 573, 581, 589, 597, 605, 613, 621, 629,
		637, 644, 652, 659, 667, 674, 682, 689, 696, 703, 710, 717, 724, 731,
		738, 745, 751, 758, 764, 771, 777, 783, 790, 796, 802, 808, 813, 819,
		825, 830, 836, 841, 847, 852, 857, 862, 867, 872, 877, 882, 887, 891,
		896, 900, 904, 909, 913, 917, 921, 925, 928, 932, 936, 939, 942, 946,
		949, 952, 955, 958, 961, 964, 966, 969, 971, 973, 976, 978, 980, 982,
		984, 985, 987, 989, 990, 991, 993, 994, 995, 996, 997, 997, 998, 999,
		999, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 999, 999, 998, 998, 997,
		996, 995, 994, 993, 992, 990, 989, 987, 986, 984, 982, 980, 978, 976,
		974, 972, 969, 967, 964, 961, 958, 956, 953, 949, 946, 943, 940, 936,
		933, 929, 925, 921, 917, 913, 909, 905, 901, 896, 892, 887, 883, 878,
		873, 868, 863, 858, 853, 848, 842, 837, 831, 826, 820, 814, 808, 803,
		797, 790, 784, 778, 772, 765, 759, 752, 746, 739, 732, 725, 718, 711,
		704, 697, 690, 683, 675, 668, 661, 653, 645, 638, 630, 622, 614, 606,
		598, 590, 582, 574, 566, 558, 549, 541, 533, 524, 516, 507, 498, 490,
		481, 472, 463, 454, 445, 436, 427, 418, 409, 400, 391, 382, 372, 363,
		354, 344, 335, 326, 316, 307, 297, 287, 278, 268, 259, 249, 239, 230,
		220, 210, 200, 190, 181, 171, 161, 151, 141, 131, 121, 111, 101, 91, 82,
		72, 62, 52, 42, 32, 22, 12, };
void UpdateSpeedMotor(uint16 Speed) {
	if (Speed == 0)
		SVPWM.ModulIndex = 0;
	if (Speed >= 100)
		Speed = 100;
	SVPWM.ModulIndex = Speed;
	SVPWM.FreOutputMotor = Speed * (V_RMS_OUT / (10 * V_F_Coff));
}

void SVPWMInit(void) {
	REMAP_ENABLE;
	PWMConfig();
	TimerFreOutConfig();
	SVPWM.ModulIndex = 0;
	SVPWM.FreOutputMotor = 0;
	SVPWM.Dir = FORWARD;
	SVPWM.Run = 1;
	SVPWM.StopEmer = 0;
}
void TimerPWMIrqHandler(void) {

	if (SVPWM.StopEmer == STOPEMER) {
		TIMER_PWM->CCR1 = 0;
		TIMER_PWM->CCR2 = 0;
		TIMER_PWM->CCR3 = 0;
		TIM_CtrlPWMOutputs(TIMER_PWM, DISABLE);

	} else {
		TIM_CtrlPWMOutputs(TIMER_PWM, ENABLE);

	}
	if (SVPWM.FreOutputMotor >= 60)
		SVPWM.FreOutputMotor = 60;
	if (SVPWM.FreOutputMotor <= 3)
		SVPWM.FreOutputMotor = 3;
	TIMER_FRE_OUTPUT_PERIOD = 160920 / SVPWM.FreOutputMotor;
	TIMER_PWM->SR = ~TIM_IT_Update;
}

void TimerFreOutIrqHandler(void) {
//  static sint32 Time = 0;
////Time = TIMER_BASE_1US->CNT;
//static uint16 Test1;
//static uint16 Test2;
//
//
//static uint8 Sector;
//uint16 TSwap;
//LED1_USER_DEBUG_TOG;
	TIMER_PWM->CCR1 = (DutyPWM1[TimerCount] * SVPWM.ModulIndex) / 100;
	TIMER_PWM->CCR2 = (DutyPWM2[TimerCount] * SVPWM.ModulIndex) / 100;
	TIMER_PWM->CCR3 = (DutyPWM3[TimerCount] * SVPWM.ModulIndex) / 100;
///////////////////////
//Alpha = (TimerCount*2*Pi*PERIOD)/(10*SVPWM.FreOutputMotor);
//Sector=SectorInd(Alpha);//Sector
//////////////////////////////////////////////
//Alpha1 = Sector*Pi/3-Alpha;
//Alpha2 = Alpha-(Sector-1)*Pi/3;
///////Cal time
//Test1=SinTable[Alpha1];
//Test2=SinTable[Alpha2];
//Ta=(PERIOD/1000)*(SVPWM.ModulIndex)*866*SinTable[Alpha1]/100000;
//Tb=(PERIOD/1000)*(SVPWM.ModulIndex)*866*SinTable[Alpha2]/100000;
//T0 = PERIOD-Ta-Tb;
//if(SVPWM.Dir==REVERSE)  
//{
//  TSwap = Ta;
//  Ta = Tb;
//  Tb = TSwap;
//}
///////////////////////////
//switch (Sector)
//{
//case 1:  TIMER_PWM->CCR1 = Ta+Tb+T0/2;TIMER_PWM->CCR2=Tb+T0/2;TIMER_PWM->CCR3=T0/2;
//  break;
//case 2:  TIMER_PWM->CCR1 = Ta+T0/2;TIMER_PWM->CCR2=Ta+Tb+T0/2;TIMER_PWM->CCR3=T0/2;
//  break;
//case 3:  TIMER_PWM->CCR1 = T0/2;TIMER_PWM->CCR2=Ta+Tb+T0/2;TIMER_PWM->CCR3=Tb+T0/2;
//  break;
//case 4:  TIMER_PWM->CCR1 = T0/2;TIMER_PWM->CCR2=Ta+T0/2;TIMER_PWM->CCR3=Ta+Tb+T0/2;
//  break;
//case 5:  TIMER_PWM->CCR1 = Tb+T0/2;TIMER_PWM->CCR2=T0/2;TIMER_PWM->CCR3=Ta+Tb+T0/2;
//  break;
//case 6:  TIMER_PWM->CCR1 = Ta+Tb+T0/2;TIMER_PWM->CCR2=T0/2;TIMER_PWM->CCR3=Ta+T0/2;
//  break;
//}
//if(Alpha>=2*Pi) TimerCount = 0;//Quay het 1 vong

	TimerCount++;
	if (TimerCount == 60)
		TimerCount = 0;
//LED1_USER_DEBUG_OFF;
//Time = TIMER_BASE_1US->CNT;
	TIM_ClearFlag(TIMER_FRE_OUTPUT, TIM_IT_Update);
}
//////////////////////////////////////////////////////
uint8 SectorInd(uint16 Angle) {
	uint8 i;
	sint16 Angle1;
	sint16 Angle2;
	for (i = 1; i <= 6; i++) {
		Angle1 = i * Pi / 3;
		Angle1 = Angle1 - Angle;
		Angle2 = Angle - (i - 1) * Pi / 3;
		if ((Angle1 >= 0) && (Angle2 >= 0))
			return i;
	}
}
//////////////////////////////////////////////////////
void UpdateDutyPWM(uint16 DUTY1, uint16 DUTY2, uint16 DUTY3) {
	if (DUTY1 >= MAX_DUTY)
		DUTY1 = MAX_DUTY;
	if (DUTY2 >= MAX_DUTY)
		DUTY2 = MAX_DUTY;
	if (DUTY3 >= MAX_DUTY)
		DUTY3 = MAX_DUTY;
	DUTY1 = PERIOD * DUTY1 / 100;
	TIMER_PWM->CCR1 = DUTY1;
	DUTY2 = PERIOD * DUTY2 / 100;
	TIMER_PWM->CCR2 = DUTY2;
	DUTY3 = PERIOD * DUTY3 / 100;
	TIMER_PWM->CCR3 = DUTY3;
}

////////////////////////////////////////
void PWMConfig(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(
			PMW1H_CLK | PMW2H_CLK | PMW3H_CLK | PMW1L_CLK | PMW2L_CLK
					| PMW3L_CLK, ENABLE);
	/* Configure the SW_MODE_GPIO_CLK pin */
	GPIO_InitStructure.GPIO_Pin = PMW1H_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PMW1H_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PMW1L_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PMW1L_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PMW2H_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PMW2H_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PMW2L_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PMW2L_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PMW3H_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PMW3H_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PMW3L_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PMW3L_PORT, &GPIO_InitStructure);

	///////////////////////////////////////////////
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB2PeriphClockCmd(TIMER_PWM_CLK | RCC_APB2Periph_AFIO, ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned3;
	TIM_TimeBaseStructure.TIM_Period = PERIOD;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIMER_PWM, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIMER_PWM, &TIM_OCInitStructure);
	TIM_OC2Init(TIMER_PWM, &TIM_OCInitStructure);
	TIM_OC3Init(TIMER_PWM, &TIM_OCInitStructure);
	TIM_CtrlPWMOutputs(TIMER_PWM, ENABLE);

	//dead time
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	/* Automatic Output enable, Break, dead time and lock configuration*/
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	TIM_BDTRInitStructure.TIM_DeadTime = DEADTIME;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIMER_PWM, &TIM_BDTRInitStructure);
	/////////////////////////////////////////////
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIMER_PWM_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIMER_PWM, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIMER_PWM, ENABLE);
}

void TimerFreOutConfig(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(TIMER_FRE_OUTPUT_CLK, ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 10000000);
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
	TIM_TimeBaseInit(TIMER_FRE_OUTPUT, &TIM_TimeBaseStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIMER_FRE_OUTPUT_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ITConfig(TIMER_FRE_OUTPUT, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIMER_FRE_OUTPUT, ENABLE);
}

#undef _SVPWM_M
