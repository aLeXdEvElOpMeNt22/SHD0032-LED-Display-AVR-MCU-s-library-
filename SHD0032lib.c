#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SPI_EN PB1
#define SPI_LATCH PB2
#define SPI_SCK PB3
#define SPI_MOSI PB4

unsigned char SHD0032_charTable[15] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0x6E, 0x9E, 0x6C, 0xFD, 0x02};

void Soft_SPI_Write(unsigned char data)
{
	unsigned char i;
	
	for(i = 0; i < 8; i++)
	{
		if(data & 0x01)
		{
			PORTB |=(1 << SPI_MOSI);
		}
		else
		{
			PORTB &=~(1 << SPI_MOSI);
		}
		PORTB |=(1 << SPI_SCK);
		PORTB &=~(1 << SPI_SCK);
		data = data >> 1;		
	}
}

void SHD0032_Write(unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4, unsigned char dot)
{
	PORTB &=~(1 << SPI_LATCH);
	PORTB |=(1 << SPI_EN);
	Soft_SPI_Write(d4);
	Soft_SPI_Write(d3);
	if(dot == 0x01)
	{
		Soft_SPI_Write(d2 |= 0x01);
	}
	else
	{
		Soft_SPI_Write(d2 &=~ 0x01);
	}
	Soft_SPI_Write(d1);
	PORTB |=(1 << SPI_LATCH);
	PORTB &=~(1 << SPI_LATCH);
	PORTB &=~(1 << SPI_EN);
	
}

void SHD0032_Show(unsigned char hour, unsigned char _min, unsigned char dot)
{
	SHD0032_Write(SHD0032_charTable[(_min % 100) / 10], SHD0032_charTable[_min % 10], SHD0032_charTable[(hour % 100) / 10], SHD0032_charTable[hour % 10], dot);
}

void default_image(void)
{
	PORTB &=~(1 << SPI_LATCH);
	PORTB |=(1 << SPI_EN);
	for (unsigned char i = 0; i <= 4; i++)
	{
		Soft_SPI_Write(SHD0032_charTable[14]);
	}
	PORTB |=(1 << SPI_LATCH);
	PORTB &=~(1 << SPI_LATCH);
	PORTB &=~(1 << SPI_EN);
}
