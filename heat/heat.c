#include "heat.h"

void	heat_off ()
{
	fire_off_1	
	fire_off_2	
	fire_off_3
	fire_off_4
}

void	heat_init ()
{
	GPIO_InitTypeDef GPIO_Config;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_Config.GPIO_Pin 		= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Config.GPIO_Mode 	= GPIO_Mode_Out_PP;
  GPIO_Config.GPIO_Speed 	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Config);
	
	heat_off ();
}
// EXTRA FUNCTION FOR GOODBYE KTURE
inline void fire ()
{
	fire_on_1	
	fire_on_2	
	fire_on_3
	fire_on_4
}

void	heat_set  (unsigned char heat, unsigned char set)
{
	heat_off ();
	if (set)
	{
		switch (heat)
		{
			case HEAT_1: fire_on_1
				break;
			case HEAT_2: fire_on_2
				break;
			case HEAT_3: fire_on_3
				break;
			case HEAT_4: fire_on_4
				break;
			default:	break;
		}
	}
}
