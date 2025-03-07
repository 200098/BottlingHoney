/*
 * SSD1306_OLED.c
 *  The MIT License.
 *  Created on: Oct 29, 2020
 *      Author: Mateusz Salamon
 */



#include "main.h"
#include "SSD1306_OLED.h"
#include "string.h"


I2C_HandleTypeDef *oled_i2c;
static uint8_t buffer[SSD1306_BUFFER_SIZE];

void SSD1306_Command(uint8_t Command)
{
	HAL_I2C_Mem_Write(oled_i2c, SSD1306_ADDRESS, 0x00, 1, &Command, 1, SSD1306_TIMEOUT);
}

void SSD1306_Data(uint8_t *Data, uint16_t Size)
{
	HAL_I2C_Mem_Write(oled_i2c, SSD1306_ADDRESS, 0x40, 1, Data, Size, SSD1306_TIMEOUT);
}

void SSD1306_DrawPixel(int16_t x, int16_t y, uint8_t Color)
{
	if((x < 0) || (x >= SSD1306_LCDWIDTH) || (y < 0) || (y >= SSD1306_LCDHEIGHT))
	  return;

    switch(Color)
    {
    case SSD1306_WHITE:
      buffer[x + (y / 8) * SSD1306_LCDWIDTH] |= (1 << (y & 7));
      break;
    case SSD1306_BLACK:
      buffer[x + (y / 8) * SSD1306_LCDWIDTH] &= ~(1 << (y & 7));
      break;
    case SSD1306_INVERSE:
      buffer[x + (y / 8) * SSD1306_LCDWIDTH] ^= (1 << (y & 7));
      break;
    }
}



void SSD1306_Clear(uint8_t Color)
{
	switch(Color)
	{
	case WHITE:
		memset(buffer, 0xFF, SSD1306_BUFFER_SIZE);
		break;

	case BLACK:
		memset(buffer, 0x00, SSD1306_BUFFER_SIZE);
		break;
	}
}


void SSD1306_Display(void)
{
	SSD1306_Command(SSD1306_PAGEADDR);
	SSD1306_Command(0);                      // Page start address
	SSD1306_Command(0xFF);                   // Page end (not really, but works here)
	SSD1306_Command(SSD1306_COLUMNADDR);
	SSD1306_Command(0); // Column start address
	SSD1306_Command(SSD1306_LCDWIDTH - 1); // Column end address

	SSD1306_Data(buffer, SSD1306_BUFFER_SIZE);

}


void SSD1306_Init(I2C_HandleTypeDef *i2c)
{
	oled_i2c = i2c;
	SSD1306_Command(SSD1306_DISPLAYOFF);
	SSD1306_Command(SSD1306_SETDISPLAYCLOCKDIV);
	SSD1306_Command(0x80);
	SSD1306_Command(SSD1306_SETMULTIPLEX);

	SSD1306_Command(SSD1306_LCDHEIGHT - 1);

	SSD1306_Command(SSD1306_SETDISPLAYOFFSET);
	SSD1306_Command(0x00);
	SSD1306_Command(SSD1306_SETSTARTLINE);

	SSD1306_Command(SSD1306_CHARGEPUMP);
	SSD1306_Command(0x14);

	SSD1306_Command(SSD1306_MEMORYMODE);
	SSD1306_Command(0x00);
	SSD1306_Command(SSD1306_SEGREMAP| 0x1);
	SSD1306_Command(SSD1306_COMSCANDEC);

	SSD1306_Command(SSD1306_SETCOMPINS);
	SSD1306_Command(0x12);
	SSD1306_Command(SSD1306_SETCONTRAST);
	SSD1306_Command(0xFF);

	SSD1306_Command(SSD1306_SETPRECHARGE);
	SSD1306_Command(0xF1);

	SSD1306_Command(SSD1306_SETVCOMDETECT); // 0xDB
	SSD1306_Command(0x40);
	SSD1306_Command(SSD1306_DISPLAYALLON_RESUME); // 0xA4
	SSD1306_Command(SSD1306_NORMALDISPLAY);       // 0xA6
	SSD1306_Command(SSD1306_DEACTIVATE_SCROLL);

	SSD1306_Command(SSD1306_DISPLAYON); // Main screen turn on

}


