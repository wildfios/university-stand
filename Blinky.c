#include "stm32f10x.h"
#include "src/stm32f10x_rcc.h"
#include "src/stm32f10x_gpio.h"
#include "src/misc.h"

#include "pff.h"
#include "wav_play.h"
#include "phase_ctr.h"
#include "lph8836.h"
#include "lcd_hal.h"
#include "heat.h"
#include "gui.h"

/*----------------------------------------------------------------------------
  MAIN function
*----------------------------------------------------------------------------*/

#include "kbd.h"

void heat_del_tst (char del_int)
{
int tmp = heat[del_int] * 1000000;
	while (tmp--)
		if (kbd_scan () == KBD_X)
			break;
}

int main (void) 
{
FATFS fs;
//==============INIT BLOCK
	pf_mount(&fs);

	SystemInit();
	SystemCoreClockUpdate();

	wav_init_player();

	light_init();
	heat_init ();
	
	lcd_spi_init();
	hitachi lcd(lcd_spi_send);
	lcd.init();

	light_off();
	heat_off ();
	
	menu_main (&lcd, &fs);
	while(1);
}
