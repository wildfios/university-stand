#ifndef __BG_DRAW__
#define __BG_DRAW__

#include "pff.h"
#include "lph8836.h"

void	draw_bg (hitachi *lcd, char index, FATFS *fs);
void	draw_mn_sub(hitachi *lcd, char col_h, char offset, char col_l);
void	draw_fr_sub	(hitachi *lcd, char index);
void	draw_bar_sub (hitachi *lcd, int offset,int cnt);
void	draw_mn(hitachi *lcd, char col_h, char offset);
void	draw_fr_m (hitachi *lph, char index);
void	draw_heat_icon (FATFS *fs, hitachi *lph, char index, char pic_ind);

#endif
