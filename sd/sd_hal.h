#ifndef __sd_hal__
#define	__sd_hal__

#include "STM32F10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

#define   SD_CS     GPIO_Pin_4
#define   SD_SI	    GPIO_Pin_7
#define   SD_SO     GPIO_Pin_6
#define   SD_CL     GPIO_Pin_5

#define	  sd_cs_hi	GPIOB->BSRR = 1 << 12;
#define   sd_cs_lo	GPIOB->BRR  = 1 << 12;

unsigned char	sd_spi_send		(unsigned char data);
void			sd_spi_init		(void);
void			spi_up_speed	(void);

#endif
