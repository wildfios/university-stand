#include "mcp42xxx.h"

void mcp_init ()
{
	GPIO_InitTypeDef GPIO_Config;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_Config.GPIO_Pin 		= GPIO_Pin_12;
  GPIO_Config.GPIO_Mode 	= GPIO_Mode_Out_PP;
  GPIO_Config.GPIO_Speed 	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_Config);
	
	mcp_spi_init();	
}

void mcp_set_val (short mcp_chan, char mcp_val)
{
	mcp_spi_send (mcp_chan | mcp_val);
}
