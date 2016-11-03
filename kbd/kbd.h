#ifndef __KBD__
#define __KBD__

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "sub_menu.h"

#define		KBD_UP		0x03D0
#define		KBD_DN		0x01F0
#define		KBD_L			0x03E0
#define		KBD_R			0x02F0
#define		KBD_X			0x0370
#define		KBD_E			0x03B0
#define		KBD_NULL	0x03F0

#define		KBD_DL_F		10000
#define		KBD_DL_S		200000

void	kbd_init			(void);
int		kbd_scan			(char div = 1);


#endif
