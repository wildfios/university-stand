#include "kbd.h"

void	kbd_init ()
{
	GPIO_InitTypeDef GPIO_Config;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_Config.GPIO_Pin		= GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Config.GPIO_Mode		= GPIO_Mode_IN_FLOATING;
  GPIO_Config.GPIO_Speed	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Config);
}
inline int	kbd_get ()
{
	return GPIOB->IDR & KBD_NULL;
}

int kbd_scan (char div)
{
	static int key_int, kbd = 0;

	if(kbd_get () != KBD_NULL)
		kbd++;
	else                                                                    
	{
		kbd = 0;
		key_int = KBD_DL_F / div;
	}    

	if (kbd == key_int)
	{
		key_int = KBD_DL_S / div;
		kbd = 0; 
		return kbd_get(); 
	}
	
	return KBD_NULL;
}
