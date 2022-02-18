//SHD0032lib
#ifndef SHD0032LIB_H_
#define SHD0032LIB_H_

#include <avr/io.h>
#include <util/delay.h>
void Soft_SPI_Write(unsigned char data);
void SHD0032_Write(unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4, unsigned char dot);
void SHD0032_Show(unsigned char _min, unsigned char hour, unsigned char dot);
void default_image(void);
#endif