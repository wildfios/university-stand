#ifndef __mcp_spi__
#define __mcp_spi__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define mcp_cs_lo		GPIOC->BRR  = 1 << 11;	  
#define mcp_cs_hi		GPIOC->BSRR = 1 << 11;	

#define mcp_clk_lo	GPIOC->BRR  = 1 << 10;	  
#define mcp_clk_hi	GPIOC->BSRR = 1 << 10;	

#define mcp_dat_lo	GPIOA->BRR  = 1 << 15;	  
#define mcp_dat_hi	GPIOA->BSRR = 1 << 15;	

void mcp_spi_init();
void mcp_spi_send (short data);

#endif
