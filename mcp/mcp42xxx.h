#ifndef __MCP42xxx__
#define __MCP42xxx__

#include "mcp_spi.h"

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define snd_on  GPIOC->BSRR = 1 << 12;	
#define snd_off GPIOC->BRR  = 1 << 12;	

#define MCP_CH_L		0x1100
#define MCP_CH_R		0x1200

void mcp_init ();
void mcp_set_val (short mcp_chan, char mcp_val);

#endif
