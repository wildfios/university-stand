#ifndef __heat_h__
#define __heat_h__

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define fire_on_1		GPIOB->BSRR = 1 << 1;	  
#define fire_off_1	GPIOB->BRR = 1 << 1;	  
#define fire_on_2		GPIOB->BSRR = 1 << 2;	  
#define fire_off_2	GPIOB->BRR = 1 << 2;	  
#define fire_on_3		GPIOB->BSRR = 1 << 10;	  
#define fire_off_3	GPIOB->BRR = 1 << 10;	  
#define fire_on_4		GPIOB->BSRR = 1 << 11;	  
#define fire_off_4	GPIOB->BRR = 1 << 11;	  

#define HEAT_1 0
#define HEAT_2 1
#define HEAT_3 2
#define HEAT_4 3


void	heat_off	(void);
void	heat_init (void);
// EXTRA FUNCTION FOR GOODBYE KTURE
void	fire			(void);
void	heat_set  (unsigned char heat, unsigned char set);

#endif


