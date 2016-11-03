#include "draw.h"

void	draw_heat_icon (FATFS *fs, hitachi *lcd, char index, char pic_ind)
{
BYTE buf[512];	
WORD pic_br;	

	if (pic_ind)
		pf_open (fs, "clock.bin");
	else
		pf_open (fs, "term.bin");
		
	pf_read (fs, buf, 3, &pic_br);
	lcd->get_rect(151, 27 + index * 0x1A, 171, 51 + index * 0x1A, lph_or_90);

	for (int i = 0; i < 2; i++)
	{
			pf_read (fs, buf, 512, &pic_br);
			lcd->fill_bitmap(buf, 512);
	}
	
}

void draw_bg (hitachi *lcd, char index, FATFS *fs)
{
char file_name[6][13] = {"menu_n~1.bin", "menu_l~1.bin", "menu_r~1.bin", "menu_h~1.bin", "main_m~1.bin", "about.bin"};

	
BYTE buf[512];	
WORD pic_br;	

	pf_open (fs, &file_name[index][0]);
	pf_read (fs, buf, 3, &pic_br);
	
	lcd->get_rect(0, 0, 175, 131, lph_or_90);
	for (int i = 0; i < 90; i++)
	{
			pf_read (fs, buf, 512, &pic_br);
			lcd->fill_bitmap(buf, 512);
	}
			pf_read (fs, buf, 512, &pic_br);
			lcd->fill_bitmap(buf, 386);
}
//=========================main menu
void	draw_mn(hitachi *lcd, char col_h, char offset)
{
	lcd->get_rect(2, 28 + offset, 140, 29 + offset, lph_or_90);// -
	lcd->fill_rect_(col_h, 0x7F, 300);

	lcd->get_rect(2, 50 + offset, 140, 51 + offset, lph_or_90);// _
	lcd->fill_rect_(col_h, 0x7F, 300);

	lcd->get_rect(2, 28 + offset, 3, 51 + offset, lph_or_90); //|
	lcd->fill_rect_(col_h, 0x7F, 50);

	lcd->get_rect(139, 28 + offset, 140, 51 + offset, lph_or_90);
	lcd->fill_rect_(col_h, 0x7F, 50 );
}

void	draw_fr_m (hitachi *lph, char index)
{
	for (int i = 0; i < 4; i++)
		if (i == index)
			draw_mn (lph, 0x00, 0x1A * i);
		else
			draw_mn (lph, 0x77, 0x1A * i);
}

//====================sub menu================================================================================

void draw_mn_sub(hitachi *lcd, char col_h, char offset, char col_l = 0x9F)
{
	lcd->get_rect(15, 27 + offset, 150, 28 + offset, lph_or_90);// -
	lcd->fill_rect_(col_l, col_h, 280);

	lcd->get_rect(15, 51 + offset, 150, 52 + offset, lph_or_90);// _
	lcd->fill_rect_(col_l, col_h, 280);

	lcd->get_rect(15, 27 + offset, 16, 52 + offset, lph_or_90); //|
	lcd->fill_rect_(col_l, col_h, 50);

	lcd->get_rect(149, 27 + offset, 150, 52 + offset, lph_or_90);
	lcd->fill_rect_(col_l, col_h, 50);
}

void draw_fr_sub	(hitachi *lcd, char index)
{
	for (int i = 0; i < 4; i++)
		if (i == index)
			draw_mn_sub (lcd, 0x00, 0x1A * i, 0x7F);
		else
			draw_mn_sub (lcd, 0xF7, 0x1A * i);
}

void draw_bar_sub (hitachi *lcd, int offset,int cnt)
{
	for (int i = 0; i < 5; i++)
	{
		lcd->get_rect(19 + i * 26, 31 + offset, 42 + i * 26, 48 + offset, lph_or_90);
		if (i < cnt)
			lcd->fill_rect_(0xF1, 0x00, 506);
		else
			lcd->fill_rect_(0xF7, 0xF9, 506);
	}
}
