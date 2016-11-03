#ifndef __sd_h_
#define __sd_h_

#include "sd_hal.h"
#include "stm32f10x_tim.h"

#define SD_BLOCKSIZE 		512
#define SD_BLOCKSIZE_NBITS	9
#define SD_READ_SECT 		0

#define   CMD0	    0x40	
#define   CMD1      0x41	
#define   CMD8      0x48
#define   CMD9      0x49
#define   CMD10     0x4A
#define   CMD12     0x4C
#define   CMD16     0x50
#define   CMD17     0x51
#define   CMD18     0x52
#define   CMD23     0x57 
#define   CMD41     0x69 
#define   CMD55     0x57 

	void 			sd_spi_init		(void);
	void			sd_init			(void);
	unsigned char	sd_spi_send		(unsigned char data_byte);
	void sd_com(char sd_comand, int sd_arg, char sd_crc);
	void 			sd_read_sector	(unsigned char *sd_buf, int sd_sec);


#endif 
