/*
 * drv_lcdModule.c
 *
 *  Created on: Jun 17, 2021
 *      Author: kevin
 */

#include "main.h"

/************************************************************************************/
/*									Defines											*/
/************************************************************************************/
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

#ifndef abs
	#define abs(a) ((a) < 0 ? -(a) : (a))
#endif

#ifndef _swap_int16_t
 	 #define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif





/************************************************************************************/
/*									Private Variables								*/
/************************************************************************************/
static SPI_HandleTypeDef *_hSpi;
static uint16_t _width 	= ILI9341_TFTWIDTH;
static uint32_t _height = ILI9341_TFTHEIGHT;
static uint16_t _rotation = 0;
static uint16_t _cursor_x = 0;
static uint16_t _cursor_y = 0;
static uint16_t _textsize = 1;
static uint16_t _textColor = 0xFFFF;
static uint16_t _textBgColor = 0xFFFF;
static bool _wrap = true;
static bool _cp437 = false;





/************************************************************************************/
/*									Private Functions								*/
/************************************************************************************/
static void spiWrite(uint8_t c);
static void writeCommand(uint8_t c);
static void writeData(uint8_t c);
static void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
static void drawPixel(int16_t x, int16_t y, uint16_t color);
static void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
static void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
static void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);



void spiWrite(uint8_t c)
{
	HAL_SPI_Transmit(_hSpi, &c, 1, 10);
}

void writeCommand(uint8_t c)
{
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	spiWrite(c);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void writeData(uint8_t c)
{
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	spiWrite(c);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)	//comment: ok
{
	//Column Address Set
	writeCommand(ILI9341_CASET);
	writeData(x0 >> 8);
	writeData(x0 & 0xFF);     // XSTART
	writeData(x1 >> 8);
	writeData(x1 & 0xFF);     // XEND

	//Row Address Set
	writeCommand(ILI9341_PASET);
	writeData(y0>>8);
	writeData(y0 & 0xFF);     // YSTART
	writeData(y1>>8);
	writeData(y1 & 0xFF);     // YEND

	//Write to RAM
	writeCommand(ILI9341_RAMWR);
}

void drawPixel(int16_t x, int16_t y, uint16_t color)
{
	//Check if 'x' and 'y' coordinates are within the valid range
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height))
		return;

	//Set cursor
	setAddrWindow(x,y,x+1,y+1);

	//Send 16bit color data
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	spiWrite(color >> 8);
	spiWrite(color & 0xFF);				//comment: agregado  & 0xFF
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}

		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1)
		{
			ILI9341_drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			ILI9341_drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}

		if (cornername & 0x2)
		{
		  ILI9341_drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
		  ILI9341_drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}

void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color)
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}

		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x4)
		{
			drawPixel(x0 + x, y0 + y, color);
			drawPixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2)
		{
			drawPixel(x0 + x, y0 - y, color);
			drawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8)
		{
			drawPixel(x0 - y, y0 + x, color);
			drawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1)
		{
			drawPixel(x0 - y, y0 - x, color);
			drawPixel(x0 - x, y0 - y, color);
		}
	}
}

void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size)
{
	int8_t i;
	if((x >= _width)            	||  // Clip right
		 (y >= _height)           	||  // Clip bottom
		 ((x + 6 * size - 1) < 0) 	||  // Clip left
		 ((y + 8 * size - 1) < 0))  	// Clip top
	return;

	if(!_cp437 && (c >= 176))
		c++; 	// Handle 'classic' charset behavior

	for(i=0; i<6; i++ )
	{
		uint8_t line;
		if(i < 5)	line = pgm_read_byte(font+(c*5)+i);
		else		line = 0x0;

		for(int8_t j=0; j<8; j++, line >>= 1)
		{
			if(line & 0x1)
			{
				if(size == 1)	drawPixel(_width-(x+i), y+j, color);
				else			ILI9341_fillRect(_width-(x+i*size), (y+j*size), size, size, color);
			}

			else if(bg != color)
			{
				if(size == 1)	drawPixel(_width-(x+i), y+j, bg);
				else			ILI9341_fillRect(_width-(x+i*size), (y+j*size), size, size, bg);
			}
		}
	}
}





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
void ILI9341_begin(SPI_HandleTypeDef *hSpi)
{
	_hSpi = hSpi;

	//1. Hardware Reset
	HAL_GPIO_WritePin(LCD_Reset_GPIO_Port, LCD_Reset_Pin,0);
	HAL_Delay(150);
	HAL_GPIO_WritePin(LCD_Reset_GPIO_Port, LCD_Reset_Pin,1);
	HAL_Delay(100);

	//2. Software Reset (01h)
	writeCommand(ILI9341_SWRESET);
	writeCommand(ILI9341_SWRESET);
	HAL_Delay(100);

	//3. Power Control B (CFh)
	writeCommand(0xCF);
	writeData(0x00);
	writeData(0xC9);
	writeData(0X30);

	//4. Power on Sequence Control (EDh)
	writeCommand(0xED);
	writeData(0x64);
	writeData(0x03);
	writeData(0X12);
	writeData(0X81);

	//5. Driver Timing Control A (E8h)
	writeCommand(0xE8);
	writeData(0x85);
	writeData(0x10);
	writeData(0x7A);

	//6. Power Control A (CBh)
	writeCommand(0xCB);
	writeData(0x39);
	writeData(0x2C);
	writeData(0x00);
	writeData(0x34);
	writeData(0x02);

	//7. Pump Ratio Control (F7h)
	writeCommand(0xF7);
	writeData(0x20);

	//8. Driver Timing Control B (EAh)
	writeCommand(0xEA);
	writeData(0x00);
	writeData(0x00);

	//9. Power Control 1 (C0h)
	writeCommand(ILI9341_PWCTR1);
	writeData(0x21);

	//10. Power Control 2 (C1h)
	writeCommand(ILI9341_PWCTR2);
	writeData(0x12);

	//11. VCOM Control 1 (C5h)
	writeCommand(ILI9341_VMCTR1);
	writeData(0x39);
	writeData(0x37);

	//12. VCOM Control 2 (C7h)
	writeCommand(ILI9341_VMCTR2);
	writeData(0xAB);

	//13. Memory Access Control (36h)
	writeCommand(ILI9341_MADCTL);
	writeData(0x48);

	//14. Pixel Format Set (3Ah)
	writeCommand(ILI9341_PIXFMT);
	writeData(0x55);

	//15. Frame Rate Control (In Normal Mode/Full Colors) (B1h)
	writeCommand(ILI9341_FRMCTR1);
	writeData(0x00);
	writeData(0x1B);

	//16. Display Function Control (B6h)
	writeCommand(ILI9341_DFUNCTR);
	writeData(0x0A);
	writeData(0xA2);
	writeData(0x27);
	writeData(0x00);

	//17. Enable 3G (F2h)
	writeCommand(0xF2);
	writeData(0x02);

	//18. Gamma Set (26h)
	writeCommand(ILI9341_GAMMASET);
	writeData(0x01);

	//19. Positive Gamma Correction (E0h)
	writeCommand(ILI9341_GMCTRP1);
	writeData(0x0F);
	writeData(0x23);
	writeData(0x1F);
	writeData(0x0B);
	writeData(0x0E);
	writeData(0x08);
	writeData(0x4B);
	writeData(0XA8);
	writeData(0x3B);
	writeData(0x0A);
	writeData(0x14);
	writeData(0x06);
	writeData(0x10);
	writeData(0x09);
	writeData(0x00);

	//20. Negative Gamma Correction (E1h)
	writeCommand(ILI9341_GMCTRN1);
	writeData(0x00);
	writeData(0x1C);
	writeData(0x20);
	writeData(0x04);
	writeData(0x10);
	writeData(0x08);
	writeData(0x34);
	writeData(0x47);
	writeData(0x44);
	writeData(0x05);
	writeData(0x0B);
	writeData(0x09);
	writeData(0x2F);
	writeData(0x36);
	writeData(0x0F);

	//21. Page Address Set (2Bh)
	writeCommand(0x2B);
	writeData(0x00);
	writeData(0x00);
	writeData(0x01);
	writeData(0x3F);

	//22. Column Address Set (2Ah)
	writeCommand(0x2A);
	writeData(0x00);
	writeData(0x00);
	writeData(0x00);
	writeData(0xEF);

	//23. Sleep Out (11h)
	writeCommand(ILI9341_SLPOUT);
	HAL_Delay(120);

	//24. Display ON (29h)
	writeCommand(ILI9341_DISPON);
}

void ILI9341_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	drawPixel(x0  , y0+r, color);
	drawPixel(x0  , y0-r, color);
	drawPixel(x0+r, y0  , color);
	drawPixel(x0-r, y0  , color);

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		drawPixel(x0 + x, y0 + y, color);
		drawPixel(x0 - x, y0 + y, color);
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 - x, y0 - y, color);
		drawPixel(x0 + y, y0 + x, color);
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 + y, y0 - x, color);
		drawPixel(x0 - y, y0 - x, color);
	}
}

void ILI9341_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	ILI9341_drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}

void ILI9341_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep)
	{
		_swap_int16_t(x0, y0);
		_swap_int16_t(x1, y1);
	}

	if (x0 > x1)
	{
		_swap_int16_t(x0, x1);
		_swap_int16_t(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1)
		ystep = 1;
	else
		ystep = -1;

	for (; x0<=x1; x0++)
	{
		if (steep) 	drawPixel(y0, x0, color);
		else 		drawPixel(x0, y0, color);

		err -= dy;
		if (err < 0)
		{
			y0 += ystep;
			err += dx;
		}
	}
}

void ILI9341_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	ILI9341_drawFastHLine(x, y, w, color);
	ILI9341_drawFastHLine(x, y+h-1, w, color);
	ILI9341_drawFastVLine(x, y, h, color);
	ILI9341_drawFastVLine(x+w-1, y, h, color);
}

void ILI9341_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	// rudimentary clipping (drawChar w/big text requires this)
	if((x >= _width) || (y >= _height)) return;
	if((x + w - 1) >= _width)  w = _width  - x;
	if((y + h - 1) >= _height) h = _height - y;

	setAddrWindow(x, y, x+w-1, y+h-1);

	uint8_t hi = color >> 8, lo = color;

	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	for(y=h; y>0; y--)
	{
		for(x=w; x>0; x--)
		{
			spiWrite(hi);
			spiWrite(lo);
		}
	}
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void ILI9341_fillScreen(uint16_t color)
{
  ILI9341_fillRect(0, 0,  _width, _height, color);
}

void ILI9341_invertDisplay(bool i)
{
	writeCommand(i ? ILI9341_INVON : ILI9341_INVOFF);
}

void ILI9341_drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
	// smarter version
	ILI9341_drawFastHLine(x+r  , y    , w-2*r, color); // Top
	ILI9341_drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
	ILI9341_drawFastVLine(x    , y+r  , h-2*r, color); // Left
	ILI9341_drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
	// draw four corners
	drawCircleHelper(x+r    , y+r    , r, 1, color);
	drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

void ILI9341_fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color)
{
	// smarter version
	ILI9341_fillRect(x+r, y, w-2*r, h, color);

	// draw four corners
	fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

void ILI9341_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	ILI9341_drawLine(x0, y0, x1, y1, color);
	ILI9341_drawLine(x1, y1, x2, y2, color);
	ILI9341_drawLine(x2, y2, x0, y0, color);
}

void ILI9341_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
	int16_t a, b, y, last;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1)
		_swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
	if (y1 > y2)
		_swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
	if (y0 > y1)
		_swap_int16_t(y0, y1); _swap_int16_t(x0, x1);

	// Handle awkward all-on-same-line case as its own thing
	if(y0 == y2)
	{
		a = b = x0;
		if(x1 < a)
			a = x1;
		else if(x1 > b)
			b = x1;
		if(x2 < a)
			a = x2;
		else if(x2 > b)
			b = x2;
		ILI9341_drawFastHLine(a, y0, b-a+1, color);
		return;
	}

	int16_t
	dx01 = x1 - x0,
	dy01 = y1 - y0,
	dx02 = x2 - x0,
	dy02 = y2 - y0,
	dx12 = x2 - x1,
	dy12 = y2 - y1;
	int32_t
	sa   = 0,
	sb   = 0;

	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if(y1 == y2)
		last = y1;   // Include y1 scanline
	else
		last = y1-1; // Skip it

	for(y=y0; y<=last; y++)
	{
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		/* longhand:
		a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b)
			_swap_int16_t(a,b);
		ILI9341_drawFastHLine(a, y, b-a+1, color);
	}

	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++)
	{
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		/* longhand:
		a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b)
			_swap_int16_t(a,b);
		ILI9341_drawFastHLine(a, y, b-a+1, color);
	}
}

void ILI9341_setTextSize(uint8_t s)
{
	_textsize = (s > 0) ? s : 1;
}

void ILI9341_setTextColor(uint16_t c)
{
	// For 'transparent' background, we'll set the bg
	// to the same as fg instead of using a flag
	_textColor = c;
}

void ILI9341_setTextBgColor(uint16_t c)
{
	// For 'transparent' background, we'll set the bg
	// to the same as fg instead of using a flag
	_textBgColor = c;
}

void ILI9341_setTextWrap(bool w)
{
	_wrap = w;
}

void ILI9341_setCursor(int16_t x, int16_t y)
{
	_cursor_x = x;
	_cursor_y = y;
}

uint16_t ILI9341_getCursorX(void)
{
	return _cursor_x;
}

uint16_t ILI9341_getCursorY(void)
{
	return _cursor_y;
}

void ILI9341_write(uint8_t c)
{
	if(c == '\n')
	{
		_cursor_y += _textsize*8;
		_cursor_x  = 0;
	}
	else if(c == '\r')
	{
	// skip em
	}
	else
	{
		if(_wrap && ((_cursor_x + _textsize * 6) >= _width))
		{ // Heading off edge?
			_cursor_x  = 0;            // Reset x to zero
			_cursor_y += _textsize * 8; // Advance y one line
		}
		drawChar(_cursor_x, _cursor_y, c, _textColor, _textBgColor, _textsize);
		_cursor_x += _textsize * 6;
	}
}

void ILI9341_getTextBounds(char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)
{
	uint8_t c; // Current character

	*x1 = x;
	*y1 = y;
	*w  = *h = 0;

	uint16_t lineWidth = 0, maxWidth = 0; // Width of current, all lines

	while((c = *str++))
	{
		if(c != '\n')
		{ // Not a newline
			if(c != '\r')
			{ // Not a carriage return, is normal char
				if(_wrap && ((x + _textsize * 6) >= _width))
				{
					x  = 0;            // Reset x to 0
					y += _textsize * 8; // Advance y by 1 line
					if(lineWidth > maxWidth)
						maxWidth = lineWidth; // Save widest line
					lineWidth  = _textsize * 6; // First char on new line
				} else
				{ // No line _wrap, just keep incrementing X
					lineWidth += _textsize * 6; // Includes interchar x gap
				}
			} // Carriage return = do nothing
		}
		else
		{ // Newline
			x  = 0;            // Reset x to 0
			y += _textsize * 8; // Advance y by 1 line
			if(lineWidth > maxWidth)
				maxWidth = lineWidth; // Save widest line
			lineWidth = 0;     // Reset lineWidth for new line
		}
	}
	// End of string
	if(lineWidth)
		y += _textsize * 8; // Add height of last (or only) line
	*w = maxWidth - 1;               // Don't include last interchar x gap
	*h = y - *y1;
}

void ILI9341_cp437(bool x)
{
	// Enable (or disable) Code Page 437-compatible charset.
	// There was an error in glcdfont.c for the longest time -- one character
	// (#176, the 'light shade' block) was missing -- this threw off the index
	// of every character that followed it.  But a TON of code has been written
	// with the erroneous character indices.  By default, the library uses the
	// original 'wrong' behavior and old sketches will still work.  Pass 'true'
	// to this function to use correct CP437 character values in your code.
	_cp437 = x;
}

uint16_t ILI9341_getWidth(void)
{
	return _width;
}

uint16_t ILI9341_getHeight(void)
{
	return _height;
}

uint16_t ILI9341_getTextSize(void)
{
	return _textsize;
}

uint16_t ILI9341_getTextColor(void)
{
	return _textColor;
}

void ILI9341_pushColor(uint16_t color)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	spiWrite(color >> 8);
	spiWrite(color);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void ILI9341_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  // Rudimentary clipping
	if((x >= _width) || (y >= _height))
		return;

	if((y+h-1) >= _height)
		h = _height-y;

	setAddrWindow(x, y, x, y+h-1);

	uint8_t hi = color >> 8, lo = color;

	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	while (h--)
	{
		spiWrite(hi);
		spiWrite(lo);
	}
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

void ILI9341_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
	// Rudimentary clipping
	if((x >= _width) || (y >= _height))
		return;
	if((x+w-1) >= _width)
		w = _width-x;
	setAddrWindow(x, y, x+w-1, y);

	uint8_t hi = color >> 8, lo = color;

	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	while (w--)
	{
		spiWrite(hi);
		spiWrite(lo);
	}
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

uint16_t ILI9341_color565(uint8_t r, uint8_t g, uint8_t b)
{ // Pass 8-bit (each) R,G,B, get back 16-bit packed color
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void ILI9341_setRotation(uint8_t m)
{
	writeCommand(ILI9341_MADCTL);
	_rotation = m % 4; // can't be higher than 3
	switch (_rotation)
	{
		case 0:
			writeData(MADCTL_MX | MADCTL_BGR);
			_width  = ILI9341_TFTWIDTH;
			_height = ILI9341_TFTHEIGHT;
		break;
		case 1:
			writeData(MADCTL_MV | MADCTL_BGR);
			_width  = ILI9341_TFTHEIGHT;
			_height = ILI9341_TFTWIDTH;
		break;
		case 2:
			writeData(MADCTL_MY | MADCTL_BGR);
			_width  = ILI9341_TFTWIDTH;
			_height = ILI9341_TFTHEIGHT;
		break;
		case 3:
			writeData(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
			_width  = ILI9341_TFTHEIGHT;
			_height = ILI9341_TFTWIDTH;
		break;
	}
}

uint16_t ILI9341_getRotation(void)
{
	return _rotation;
}
