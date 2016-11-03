#include "sd_hal.h"

unsigned char sd_spi_send (unsigned char data)
{          
	SPI_I2S_SendData(SPI2, data);
		while (!(SPI2->SR & SPI_SR_TXE));

	return SPI2->DR;
}

void sd_spi_init ()
{
SPI_InitTypeDef			SPI_InitStructure;
GPIO_InitTypeDef		GPIO_InitStructure;

	//=== init clock spi gpio
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);

	//=== init gpio for spi
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
 	//=== init spi
	SPI_InitStructure.SPI_Direction	= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit	= SPI_FirstBit_MSB;
	SPI_Init(SPI2, &SPI_InitStructure);
	SPI_Cmd (SPI2, ENABLE);	

	sd_cs_hi   
}

void spi_up_speed ()
{
SPI_InitTypeDef			SPI_InitStructure;

	SPI_InitStructure.SPI_Direction	= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit	= SPI_FirstBit_MSB;
	SPI_Init(SPI2, &SPI_InitStructure);
}
