#ifndef __lighting_my__
#define __lighting_my__

#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"	 

void light_set	(unsigned char * mas);
void light_off	(void);
void light_on		(void);
void light_init	(void);

#endif
