#include "diskio.h"


DSTATUS disk_initialize (void)
{
//	DSTATUS stat = 0;
	sd_init();

	return RES_OK;//stat;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* dest,			/* Pointer to the destination object */
	DWORD sector,		/* Sector number (LBA) */
	WORD sofs,			/* Offset in the sector */
	WORD count			/* Byte count (bit15:destination) */
)
{
	int i, k = 0;
	unsigned char resp = 0xFF;

	DRESULT res = RES_OK;
	if ((sofs < 512) && (sofs + count <= 512))
	{
//=================================================

	while(resp != 0xfe)
	{
		resp = 255;
		sd_cs_lo 
		sd_com(CMD17, sector * 512, 0xFF);
		while (resp == 255)
			resp = sd_spi_send (0xFF);
	}  

//==================================================
  
   for (i = 0; i < sofs; i++)
		resp = sd_spi_send (0xFF);

	for (; i < sofs + count; i++)
			*(dest + k++) = sd_spi_send (0xFF);

	 for (; i < 512; i++)
		 resp = sd_spi_send (0xFF);

	resp = sd_spi_send (0xFF);
	resp = sd_spi_send (0xFF);

	sd_cs_hi 	
		
//=================================================
	}
	else
		res	= RES_PARERR;	

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
	const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	DWORD sc		/* Sector number (LBA) or Number of bytes to send */
)
{
	//DRESULT res;


	if (!buff) {
		if (sc) {

			// Initiate write process

		} else {

			// Finalize write process

		}
	} else {

		// Send data to the disk

	}

	return RES_OK;
}
