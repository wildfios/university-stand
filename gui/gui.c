#include "gui.h"

void	menu_about (hitachi *lcd, FATFS *fs)
{
unsigned char vol [] = {150, 150, 150, 150};	
		draw_bg (lcd, 5, fs);
		wav_load(fs, "bmn.wav");
		wav_set_volume(vol);
	
		while (kbd_scan (5) == KBD_NULL)
			if (wav_play() == 0)
					wav_load(fs, "bmn.wav");
		wav_stop();
}

void	menu_main (hitachi *lcd, FATFS *fs)
{
int  code = KBD_NULL; 
signed	char index = 0;
	
	kbd_init		();
	init_sub		(fs);
	draw_bg			(lcd, 4, fs);
	draw_fr_m		(lcd, index);	

	while (1)
	{
		while (code == KBD_NULL)
			code = kbd_scan ();
		
		switch (code)
		{
			case KBD_UP:
				--index = (index < 0) ? 3 : index;
				break;
			case KBD_DN:
				++index = (index > 3) ? 0 : index;
				break;
			case KBD_E:
					sub_menu	(lcd, index, fs);
					draw_bg		(lcd, 4, fs);					
				break;
			case KBD_X:
					menu_about (lcd, fs);
					draw_bg		(lcd, 4, fs);
				break;
			default:
				break;
		}	
		draw_fr_m (lcd, index);
		code = KBD_NULL;
	}
}
