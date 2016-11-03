#include "wav_play.h"
#include "mcp42xxx.h"

static	bool	 send = true;
static	BYTE	 wav_buf[2048];
static	FATFS *wav_fs;
static	int 	 wav_size;
static	WORD 	 wav_br;

void wav_init_timer ()
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef 		NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 0xBB;   	  //bb
	TIM_TimeBaseStructure.TIM_Prescaler = 0x02;       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down; 
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);	  
	TIM_Cmd(TIM7, DISABLE);		 
}
void wav_init_pwm()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCConfig;
	GPIO_InitTypeDef GPIO_Config;

 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	 
	GPIO_Config.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Config);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3 , ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 255;	   // 93,750 kHz
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	 	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	// Отсчет от нуля до TIM_Period 

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
//===============================pwm config 
	// Конфигурируем выход таймера, режим - PWM1
	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	// Собственно - выход включен
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	// Полярность => пульс - это единица (+3.3V)
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCConfig);	 // PA6	   //PC6
	
	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2Init(TIM3, &TIM_OCConfig);	 // PA7	 //PC7
	
	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM3, &TIM_OCConfig);	 // PB0	  //PC8
	
	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM3, &TIM_OCConfig);	 // PB1	  //PC9

	// using timer preloading
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	// Включаем таймер
	TIM_Cmd(TIM3, ENABLE); // выпилить отсюдова
}

void wav_init_player ()
{
	wav_init_timer ();
	wav_init_pwm   ();
	mcp_init ();
}

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================

#ifdef __cplusplus 
extern "C"
{
#endif
void TIM7_IRQHandler(void)
{
static WORD buf_count = 0;

	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

	TIM3->CCR1 = wav_buf [buf_count++]; 
	TIM3->CCR2 = wav_buf [buf_count++]; 
	TIM3->CCR3 = wav_buf [buf_count++]; 
	TIM3->CCR4 = wav_buf [buf_count++]; 

	if (buf_count > WAV_BUF_REF)	  
			send = true;
	
	if (buf_count > 2047)
		buf_count = 0;
}
#ifdef __cplusplus 
}
#endif	  
//======================================================================================================================
//=======init player by file
void wav_load (FATFS *fs, char * file_name)
{
WAVHEADER wav;
		wav_fs = fs;
		pf_open (wav_fs, file_name);                     
		pf_read (wav_fs, &wav, sizeof(wav), &wav_br);

		wav_size  = wav.subchunk2Size / 2048;
}

//========stops play and null all params
void wav_stop ()
{
	TIM_Cmd(TIM7, DISABLE);	
	snd_off
}

//========plays wav file
int wav_play ()
{
	snd_on
	TIM_Cmd(TIM7, ENABLE);
		if (send)
		{
			pf_read (wav_fs, wav_buf, 2048, &wav_br);
			send  = false;
			wav_size--;
		}
		return wav_size;
}

//========set the volume for each channel====================================================
void wav_set_volume (unsigned char *mas)
{
	mcp_cs_lo
		mcp_set_val (MCP_CH_L, mas[0]);
		mcp_set_val (MCP_CH_R, mas[1]);
		mcp_set_val (MCP_CH_L, mas[2]);
		mcp_set_val (MCP_CH_R, mas[3]);
	mcp_cs_hi
}

