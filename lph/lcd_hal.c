#include "lcd_hal.h"

unsigned char lcd_spi_send (unsigned char data)
{          
	SPI_I2S_SendData(SPI1, data);
		while (!(SPI1->SR & SPI_SR_TXE));

	return SPI1->DR;
}

void lcd_spi_init ()
{
SPI_InitTypeDef			SPI_InitStructure;
GPIO_InitTypeDef		GPIO_InitStructure;

	//=== init clock spi gpio
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,  ENABLE);

	//=== init gpio for spi
	GPIO_PinRemapConfig(GPIO_Remap_SPI1, DISABLE);	  	

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5| GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//=== init spi
	SPI_InitStructure.SPI_Direction	= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode		= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize	= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL		= SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA		= SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS		= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit	= SPI_FirstBit_MSB;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd (SPI1, ENABLE);	

	cs_hi   
}
