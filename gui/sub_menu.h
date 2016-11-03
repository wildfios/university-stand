#ifndef __SUB_MENU__
#define __SUB_MENU__

#include "lph8836.h"
#include "kbd.h"
#include "draw.h"

#include "heat.h"
#include "phase_ctr.h"
#include "wav_play.h"

void sub_menu (hitachi *lcd, char index, FATFS *fs);
void init_sub (FATFS *fs);

#endif
