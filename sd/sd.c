#include "sd.h"

void sd_del (int dl_vga)
{
	while (dl_vga--);
}

//==============================================================================

void sd_com(char sd_comand, int sd_arg, char sd_crc)
{

	sd_spi_send    (sd_comand);

	sd_spi_send    (sd_arg >> 24);
	sd_spi_send    (sd_arg >> 16);
	sd_spi_send    (sd_arg >> 8);
	sd_spi_send    (sd_arg);

	sd_spi_send    (sd_crc);

}
#if SD_READ_SECT
void sd_read_sector(unsigned char *sd_buf, int sd_sec)
{
	unsigned char resp = 0xFF;
	int i;

	while(resp != 0xfe)
	{
		resp = 255;
		sd_cs_lo 
		sd_com(CMD17, sd_sec * 512, 0xFF);
		while (resp == 255)
			resp = sd_spi_send (0xFF);
	}  

	for (i = 0; i < 512; i++)
		sd_buffer[i] = sd_spi_send (0xFF);

	resp = sd_spi_send (0xFF);
	resp = sd_spi_send (0xFF);

	sd_cs_hi 		
}
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void sd_init()
{
	//----APPLY 74 CLOCK PULSES
	unsigned char resp = 0xFF;  
	int i;

	sd_spi_init();

	for (i = 0; i < 74; i++)
		sd_spi_send(0xFF);

	//----reset card
	sd_cs_lo 
		sd_com(CMD0, 0x00, 0x95);	
		while(sd_spi_send (0xFF) != 1);
	sd_cs_hi 

//    while(resp != 1)
//	{
// 	    resp = 255;
//	    sd_cs_lo 
//		    sd_com(CMD8, 0x1AA, 0x87);
//		    while (resp == 255)
//				resp = sd_spi_send (0xFF);
//	}
//	    while (resp != 0xAA)
//			resp = sd_spi_send (0xFF);
//		sd_cs_lo
//
//    sd_com(CMD55, 0x00, 0x00);
  
    while(resp != 0)
	{
 	    resp = 255;
	    sd_cs_lo 
		    sd_com(CMD1, 0x00000000, 0x00);
		    while (resp == 255)
				resp = sd_spi_send (0xFF);
	    sd_cs_hi 
	}  
	spi_up_speed();	   
}

