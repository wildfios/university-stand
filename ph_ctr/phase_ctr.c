#include "phase_ctr.h"

void light_timer_init ()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCConfig;
	NVIC_InitTypeDef 		NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_Config;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_Config.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Config);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 0xFF;
	TIM_TimeBaseStructure.TIM_Prescaler = 900;  // f = 100 Hz   //936 orig	  //900 is good
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

//===pwm config 
	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0xCC;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;	
	TIM_OC1Init(TIM2, &TIM_OCConfig);			//PA0
	
	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM2, &TIM_OCConfig);	 		//PA1

	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC3Init(TIM2, &TIM_OCConfig);		  //PA2

	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC4Init(TIM2, &TIM_OCConfig);	 	  //PA3

    // using timer preloading
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	  
	TIM_Cmd(TIM2, DISABLE);
}

void light_ext_int (bool cmd)
{
NVIC_InitTypeDef   NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;

	if (cmd)
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	else
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
		
	NVIC_Init(&NVIC_InitStructure);
}

void light_exti_init ()
{
GPIO_InitTypeDef   GPIO_Config;   
EXTI_InitTypeDef   EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   /* Enable AFIO clock */
	 
	GPIO_Config.GPIO_Pin = GPIO_Pin_0;
	GPIO_Config.GPIO_Mode = GPIO_Mode_IPU; //GPIO_Mode_IN_FLOATING;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Config);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
 
/* Enable and set EXTI0 Interrupt to the lowest priority */
	light_ext_int (true);
	TIM2->CCR1 = 255;
	TIM2->CCR2 = 255;
	TIM2->CCR3 = 255;
	TIM2->CCR4 = 255;	
}

void light_set (unsigned char * mas)
{
	TIM2->CCR1 = mas[0];
	TIM2->CCR2 = mas[1];
	TIM2->CCR3 = mas[2];
	TIM2->CCR4 = mas[3];
}

void light_on ()
{
	light_ext_int (true);
}

void light_off ()
{
	TIM2->CCR1 = 255;
	TIM2->CCR2 = 255;
	TIM2->CCR3 = 255;
	TIM2->CCR4 = 255;	
	light_ext_int (false);
}

void light_init (void)
{
	light_timer_init();
	light_exti_init ();		   
}

//========================================================================================================================

#ifdef __cplusplus 
extern "C"
{
#endif
void TIM2_IRQHandler(void)
{
	/* Disable the TIM2 Counter */
	TIM2->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
	TIM2->CNT = 0;

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				
}

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);	
 	TIM_Cmd(TIM2, ENABLE);
}	

#ifdef __cplusplus 
}
#endif	
