#include "mcp_spi.h"

void mcp_del (int i)
{
	while (i--);
}

void mcp_spi_init()
{
	GPIO_InitTypeDef GPIO_Config;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_Config.GPIO_Pin 		= GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Config.GPIO_Mode 	= GPIO_Mode_Out_PP;
  GPIO_Config.GPIO_Speed 	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_Config);	

	GPIO_Config.GPIO_Pin 		= GPIO_Pin_15;
  GPIO_Config.GPIO_Mode 	= GPIO_Mode_Out_PP;
  GPIO_Config.GPIO_Speed 	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Config);	
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
	mcp_clk_lo
}

void mcp_spi_send (short data)
{
unsigned char i;
	for (i = 0; i < 16; i++)
	{
		if (data & 0x8000)
			mcp_dat_hi
		else
			mcp_dat_lo
		
		mcp_clk_hi
		mcp_del (2);
			data = data << 1;
 		mcp_clk_lo		
	}
}	
