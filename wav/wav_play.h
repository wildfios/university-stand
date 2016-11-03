#ifndef __play_wav__
#define __play_wav__

#include "stm32f10x_dac.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "pff.h"


#define WAV_BUF_REF 1800

typedef struct 
{
    char chunkId[4];
    unsigned long chunkSize;
    char format[4];
    char subchunk1Id[4];
    unsigned long subchunk1Size;
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned long sampleRate;
    unsigned long byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    char subchunk2Id[4];
    unsigned long subchunk2Size;
}WAVHEADER;
//======================================================================================================================
//======================================================================================================================
//======================================================================================================================

void	wav_init_player(void);

void	wav_load (FATFS *fs, char * file_name);
int		wav_play (void); 						//FATFS *fs, const int size, const WORD br);
void	wav_stop (void);

void	wav_set_volume (unsigned char *mas);

//======================================================================================================================
//======================================================================================================================
//======================================================================================================================


#endif
