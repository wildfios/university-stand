#include "sub_menu.h"

unsigned char volume[6];
unsigned char light [6];
unsigned char rad		[6];
unsigned char heat	[6];
			
char noize_file[]	= "ssf2.wav";

void heat_del (char del_int)
{
int tmp = heat[del_int] * 1000000;
	while (tmp--)
		if (kbd_scan () == KBD_X)
			break;
}

void init_sub (FATFS *fs)
{
WORD br = 0;
	pf_open (fs, "init.bin");                     
	pf_read (fs, &volume, sizeof(volume), &br);	
	pf_read (fs, &light, sizeof(light), &br);	
	pf_read (fs, &rad, sizeof(rad), &br);	
	pf_read (fs, &heat, sizeof(heat), &br);	
}

void heat_hand (FATFS *fs, hitachi *lcd, signed char index, char *var_ind)
{
	heat_set (index, true);
	draw_heat_icon (fs, lcd, index, 1);
	heat_del (var_ind[index]);
	draw_heat_icon (fs, lcd, index, 0);
	heat_off ();
}

void heandler (hitachi *lcd, char sub_index, signed char index, char *var_ind)
{
unsigned char tmp[4];
	
	switch (sub_index)
	{
		case 0:
				for (int i = 0; i < 4; i++)
					tmp[i] = volume[var_ind[i]];
				wav_set_volume(tmp);
			break;
		case 1:
			for (int i = 0; i < 4; i++)
				tmp[i] = light[var_ind[i]];
			light_set	(tmp);
			break;
		case 2:
			for (int i = 0; i < 4; i++)
				tmp[i] = rad[var_ind[i]];
			light_set (tmp);
			break;
		default:
		break;
	}
}

void sub_menu (hitachi *lcd, char sub_index, FATFS *fs)
{
signed char	index = 0;
char	var_ind[4] = {1,1,1,1};	
int		code	= KBD_NULL; 	
//---- render all
	draw_bg			(lcd, sub_index, fs);
	draw_fr_sub	(lcd, index);
	for (int i = 0; i < 4; i++)
		draw_bar_sub(lcd, 26 * i, var_ind[i]);
//----

	if (sub_index == 0)
		wav_load(fs, noize_file);
	else if ((sub_index == 1) || (sub_index == 2))
		light_on();
  	
	heandler (lcd, sub_index, index, var_ind);		
	
	while (1)
	{
		while (code == KBD_NULL)
		{
			if (sub_index == 0)
			{
				if (wav_play() == 0)
					wav_load(fs, noize_file);
				code = kbd_scan (10);
			}
			else
				code = kbd_scan ();
		}
		switch (code)
		{
			case KBD_UP:
				--index = (index < 0) ? 3 : index;
			break;
			case KBD_DN:
				++index = (index > 3) ? 0 : index;
			break;
			case KBD_L:
				--var_ind[index] = (var_ind[index] > 5) ? 0 : var_ind[index];
				draw_bar_sub(lcd, 26 * index, var_ind[index]);	
			break;
			case KBD_R:
				++var_ind[index] = (var_ind[index] > 5) ? 5 : var_ind[index];
				draw_bar_sub(lcd, 26 * index, var_ind[index]);
			break;
			case KBD_E:
				heat_hand (fs, lcd, index, var_ind);
			break;		
			case KBD_X:
					wav_stop	();
					light_off	();
					heat_off ();
				return;
			default:
			break;
		}
		heandler (lcd, sub_index, index, var_ind);		
		
		draw_fr_sub (lcd, index);
		code = KBD_NULL;
	}
//=====================================================================================
}
