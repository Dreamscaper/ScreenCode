#include "SurfaceHandler.h"
#include <iostream>


// use the pin name/number, not the number based on physical header position
static char SCS       = 12;      // Use any pin except the dedicated SPI SS pins?
static char DISP      = 6;      // Use any non-specialised GPIO pin
static char EXTCOMIN  = 25;	     // Use any non-specialised GPIO pin

SurfaceHandler::SurfaceHandler()
	: memLcd(SCS, DISP, EXTCOMIN, true)
	, MASK(0b11111111)
{
	clearDisplay();
	clearLineBuffer();
}

int SurfaceHandler::getScreenWidth()
{
	return SCREENWIDTH;
}

int SurfaceHandler::getScreenHeight()
{
	return SCREENHEIGHT;
}

void SurfaceHandler::addCircleToBuffer(int center, bool invertStatus)
{

}

void SurfaceHandler::addRectangleToBuffer(int left, int top, int width, int height, bool invertStatus)
{
	int iterations = (width / 8) + ((width % 8 == 0) ? 0 : 1);
	
	for(int i = 0; i < iterations; i++)
	{
		if(i != (iterations - 1))
			{
				SurfaceHandler::addBitmapToBuffer(left + (8 * i),top,8,height, invertStatus,0b11111111);
			}
		else
			{
				SurfaceHandler::addBitmapToBuffer(left + (8 * i), top, width % 8, height,invertStatus, 0b11111111);
			}
	}
	
	/*
		if (width <= 0 || height <= 0)
		{
			return; ////Even a solitary pixel is two-dimensional! 
		}
		if (left < 0)
		{
			width += left;
			left = 0;
		}
		else if (left >= SCREENWIDTH)
		{
			return;
		}
	
		if (top < 0)
		{
			height += top;
			top = 0;
		}
		else if (top >= SCREENHEIGHT)
		{
			return;
		}
	
		if (top + height > SCREENHEIGHT)
		{
			height = SCREENHEIGHT - top;
		}
		if (left + width > SCREENWIDTH)
		{
			width = SCREENWIDTH - left;
		}
	
		if (width <= 0 || height <= 0)
		{
			return; ////Even a solitary pixel is two-dimensional! 
		}
	
		int startByteIndex = (((left + 1) / 8) + (((left + 1) % 8 != 0) ? 0 : 1));
	
		int leftShiftValue = ((left) % 8);
		if (leftShiftValue < 0)
		{
			leftShiftValue = 0;	
		}
		int rightShiftValue = ((SCREENWIDTH - (width + left)) % 8);                                  
		if (rightShiftValue < 0)
		{
			rightShiftValue = 0;	
		}
		int bytesNeeded;

		if (leftShiftValue == 0 || rightShiftValue == 0)
		{
			if (width % 8 == 0)
			{
				bytesNeeded = width / 8;
			}
			else
			{
				bytesNeeded = (width / 8) + 1;
			}
		}
		else
		{
			if (width == width % 8)
			{
				if ((width - (8 - leftShiftValue)) > 0)
				{
					bytesNeeded = (width / 8) + 2;
				}
				else
				{
					bytesNeeded = (width / 8) + 1;
				}
			}
			else
			{
				if ((((8 - leftShiftValue) + (8 - rightShiftValue)) / 8) > 0)
				{
					bytesNeeded = (width / 8) + 1;
				}
				else
				{
					bytesNeeded = (width / 8) + 2;
				}
			}
		}
	
		int endByteIndex = startByteIndex + bytesNeeded - 1;     
	
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < bytesNeeded; x++)
			{
				if (x == 0) ///Acting on the first byte in a line
				{

					if (invertStatus)
					{
						SurfaceHandler::lineBuffer[startByteIndex] = (~(MASK >> leftShiftValue)) & ((frameBuffer[top + y][startByteIndex]));
					}
					else
					{
						SurfaceHandler::lineBuffer[startByteIndex] = ((~(MASK >> leftShiftValue)) & ((frameBuffer[top + y][startByteIndex]))) | (MASK >> leftShiftValue);
					}
					if (x == (bytesNeeded - 1))
					{
						if (invertStatus)
						{
							SurfaceHandler::lineBuffer[startByteIndex] = (((MASK >> leftShiftValue) & (MASK << rightShiftValue)) & lineBuffer[startByteIndex]) | ((~((MASK >> leftShiftValue) & (MASK << rightShiftValue))) & frameBuffer[top + y][startByteIndex]);
						}
						else
						{
							SurfaceHandler::lineBuffer[startByteIndex] = (((MASK >> leftShiftValue) & (MASK << rightShiftValue)) & lineBuffer[startByteIndex]) | ((~((MASK >> leftShiftValue) & (MASK << rightShiftValue))) & frameBuffer[top + y][startByteIndex]);
						}
					}
					SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
				}
				else if (x == (bytesNeeded - 1))
				{
					if (invertStatus)
					{
						SurfaceHandler::lineBuffer[endByteIndex] = (frameBuffer[y][x] & ~(MASK << rightShiftValue)) | (~(MASK << rightShiftValue));
					}
					else
					{
						SurfaceHandler::lineBuffer[endByteIndex] = (frameBuffer[y][x] & MASK << rightShiftValue) | (~(MASK << rightShiftValue));
					}
					frameBuffer[top + y][endByteIndex] = lineBuffer[endByteIndex];
				}
				else
				{
					if (invertStatus)
					{
						lineBuffer[startByteIndex + x] = ~(MASK);
					}
					else
					{
						lineBuffer[startByteIndex + x] = MASK;
					}
					SurfaceHandler::frameBuffer[top + y][startByteIndex + x] = lineBuffer[startByteIndex + x];
				}
			
			}
		
		}*/
}

void SurfaceHandler::addBitmapToBuffer(int left, int top, int width, int height, bool invertStatus, unsigned char pattern)
{	
	if (width <= 0 || height <= 0)
	{
		return; ////Even a solitary pixel is two-dimensional! 
	}
	if (left < 0)
	{
		width += left;
		left = 0;
	}
	else if (left >= SCREENWIDTH)
	{
		return;
	}
	
	if (top < 0)
	{
		height += top;
		top = 0;
	}
	else if (top >= SCREENHEIGHT)
	{
		return;
	}
	
	if (top + height > SCREENHEIGHT)
	{
		height = SCREENHEIGHT - top;
	}
	if (left + width > SCREENWIDTH)
	{
		width = SCREENWIDTH - left;
	}
	
	if (width <= 0 || height <= 0)
	{
		return; ////Even a solitary pixel is two-dimensional! 
	}
	
	int startByteIndex = left / 8;//(((left + 1) / 8) + (((left + 1) % 8 != 0) ? 0 : 1));
	
	int leftShiftValue = ((left) % 8);
	if (leftShiftValue < 0)
	{
		leftShiftValue = 0;	
	}
	int rightShiftValue = ((SCREENWIDTH - (width + left)) % 8);                                  
	if (rightShiftValue < 0)
	{
		rightShiftValue = 0;	
	}
	int bytesNeeded;

	if (leftShiftValue == 0 || rightShiftValue == 0)
	{
		if (width % 8 == 0)
		{
			bytesNeeded = width / 8;
		}
		else
		{
			bytesNeeded = (width / 8) + 1;
		}
	}
	else
	{
		if (width == width % 8)
		{
			if ((width - (8 - leftShiftValue)) > 0)
			{
				bytesNeeded = (width / 8) + 2;
			}
			else
			{
				bytesNeeded = (width / 8) + 1;
			}
		}
		else
		{
			if ((((8 - leftShiftValue) + (8 - rightShiftValue)) / 8) > 0)
			{
				bytesNeeded = (width / 8) + 1;
			}
			else
			{
				bytesNeeded = (width / 8) + 2;
			}
		}
	}
	
	int endByteIndex = startByteIndex + bytesNeeded - 1;     
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < bytesNeeded; x++)
		{
			if (x == 0) ///Acting on the first byte in a line
			{
				
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[startByteIndex] = ((MASK >> leftShiftValue) & (pattern >> leftShiftValue)) | ((SurfaceHandler::frameBuffer[top + y][startByteIndex]) & (MASK << (8 - leftShiftValue)));
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex] = ((((MASK >> leftShiftValue) & ((~pattern) >> leftShiftValue)) ^ ((~(SurfaceHandler::frameBuffer[top + y][startByteIndex])) &  (MASK << (8 - leftShiftValue)))) ^ ((~(MASK >> leftShiftValue)) & frameBuffer[top + y][startByteIndex])) & ((MASK >> leftShiftValue) | frameBuffer[top + y][startByteIndex]);
				}
				if (x == (bytesNeeded - 1))
				{
					if (invertStatus)
					{
							SurfaceHandler::lineBuffer[endByteIndex] = (SurfaceHandler::lineBuffer[endByteIndex] & (MASK << rightShiftValue)) | ((SurfaceHandler::frameBuffer[top + y][endByteIndex]) & (~(MASK << rightShiftValue)));
					}
					else
					{
						SurfaceHandler::lineBuffer[endByteIndex] =  (SurfaceHandler::lineBuffer[endByteIndex] & (MASK << rightShiftValue)) ^ ((SurfaceHandler::frameBuffer[top + y][endByteIndex]) & (~(MASK << rightShiftValue)));
					}
					SurfaceHandler::frameBuffer[top + y][endByteIndex] = lineBuffer[endByteIndex];
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
			}
			else if (x == (bytesNeeded - 1))
			{
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[endByteIndex] = ((MASK << rightShiftValue) & (pattern << rightShiftValue)) | ((SurfaceHandler::frameBuffer[top + y][endByteIndex]) & (MASK >> (8 - rightShiftValue)));
				}
				else
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (((MASK << rightShiftValue) & ((~pattern) << rightShiftValue)) ^ ((~(SurfaceHandler::frameBuffer[top + y][endByteIndex])) & (MASK >> (8 - rightShiftValue))) ^ ((~(MASK << rightShiftValue)) & frameBuffer[top + y][endByteIndex])) & ((MASK << rightShiftValue) | frameBuffer[top + y][endByteIndex]);
				}
				SurfaceHandler::frameBuffer[top + y][endByteIndex] = SurfaceHandler::lineBuffer[endByteIndex];
			}
			else
			{
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[startByteIndex + x] = ~(pattern);
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex + x] = pattern;
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex + x] = lineBuffer[startByteIndex + x];
			}
			
		}
		
	}
}

void SurfaceHandler::clipLeft(unsigned char* bitmap, int amount, int width, int height, bool invertStatus)
{
	if (amount >  8)
	{
		amount = 8;
		std::cout << "amount was greater than 8" << std::endl;
	}
	if (amount < 0)
	{
		amount = 0;
		std::cout << "amount was less than 0" << std::endl;
		return;
	}
	for (int i = 0; i < height; i++)
	{
		bitmap[i] = (bitmap[i] << amount);
		std::cout << "LeftClip Bitmap[i] is: " << + bitmap[i] << std::endl;
	}
	
}

/*
Row Major:

unsigned char*matrix = { 01, 02, 03,
						 11, 12, 13,
						 21, 22, 23 }
						 
Column Major:
unsigned char*matrix = { 01, 21, 31,
						 02, 22, 32,
						 03, 32, 33 }
*/
void SurfaceHandler::clipRight(unsigned char* bitmap, int amount, int width, int height, bool invertStatus)
{
	if (amount >  8)
	{
		amount = 8;
		std::cout << "amount was greater than 8" << std::endl;
	}
	if (amount < 0)
	{
		amount = 0;
		std::cout << "amount was less than 0" << std::endl;
		return;
	}
	for (int i = 0; i < height; i++)
	{
		bitmap[i] = (bitmap[i] >> amount) << (amount + (8 - (amount + width)));
		std::cout << "RightClip Bitmap[i] is: " << + bitmap[i] << std::endl;
	}
}

bool SurfaceHandler::findTrueCoordinates(int& left, int& top, int offsetX, int offsetY, int surfaceWidth, int surfaceHeight, int& bitmapWidth, int& bitmapHeight)
{
	if (bitmapWidth <= 0 || bitmapHeight <= 0)
	{
		return false; ////Even a solitary pixel is two-dimensional! 
	}
	if (left < offsetX)
	{
		bitmapWidth = (left + bitmapWidth) - offsetX;
		left = offsetX;
	}
	else if (left > surfaceWidth + offsetX)
	{
		return false;
	}
	
	if (top < offsetY)
	{
		bitmapHeight = (top + bitmapHeight) - offsetY;
		top = offsetY;
	}
	else if (top >= surfaceHeight + offsetY)
	{
		return false;
	}
	
	if (top + bitmapHeight >= surfaceHeight + offsetY)
	{
		bitmapHeight = (surfaceHeight + offsetY) - top;
	}
	if (left + bitmapWidth >= surfaceWidth + offsetX)
	{
		bitmapWidth = (offsetX + surfaceWidth) - left;
	}
	
	if (bitmapWidth <= 0 || bitmapHeight <= 0)
	{
		return false; ////Even a solitary pixel is two-dimensional! 
	}
	
	return true;
}

void SurfaceHandler::addBitmapToBuffer(int left, int top, int width, int height, bool invertStatus, unsigned char bitmap [])
{	
	if (width <= 0 || height <= 0)
	{
		return; ////Even a solitary pixel is two-dimensional! 
	}
	if (left < 0)
	{
		width += left;
		left = 0;
	}
	else if (left >= SCREENWIDTH)
	{
		return;
	}
	
	if (top < 0)
	{
		height += top;
		top = 0;
	}
	else if (top >= SCREENHEIGHT)
	{
		return;
	}
	
	if (top + height > SCREENHEIGHT)
	{
		height = SCREENHEIGHT - top;
	}
	if (left + width > SCREENWIDTH)
	{
		width = SCREENWIDTH - left;
	}
	
	if (width <= 0 || height <= 0)
	{
		return; ////Even a solitary pixel is two-dimensional! 
	}
	
	int startByteIndex = left / 8;//(((left + 1) / 8) + (((left + 1) % 8 != 0) ? 0 : 1));
	
	int leftShiftValue = ((left) % 8);
	if (leftShiftValue < 0)
	{
		leftShiftValue = 0;	
	}
	int rightShiftValue = ((SCREENWIDTH - (width + left)) % 8);                                  
	if (rightShiftValue < 0)
	{
		rightShiftValue = 0;	
	}
	int bytesNeeded;

	if (leftShiftValue == 0 || rightShiftValue == 0)
	{
		if (width % 8 == 0)
		{
			bytesNeeded = width / 8;
		}
		else
		{
			bytesNeeded = (width / 8) + 1;
		}
	}
	else
	{
		
		/*if (width == (width % 8))
		{
			if ((leftShiftValue + width) > 8 || (rightShiftValue + width) > 8)
			{
				bytesNeeded = 2;
			}
			else
			{
				bytesNeeded = 1;
			}
		}*/
		if (width == (width % 8))
		{
			if (((width % 8) - (8 - leftShiftValue)) > 0)
			{
				bytesNeeded = (width / 8) + 2;
			}
			else
			{
				bytesNeeded = (width / 8) + 1;
			}
		}
		else
		{
			if ((((8 - leftShiftValue) + (8 - rightShiftValue)) / 8) > 0)
			{
				bytesNeeded = (width / 8) + 1;
			}
			else
			{
				bytesNeeded = (width / 8) + 2;
			}
		}
	}
	
	int endByteIndex = startByteIndex + bytesNeeded - 1;     
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < bytesNeeded; x++)
		{
			if (x == 0) ///Acting on the first byte in a line
			{
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[startByteIndex] = ((MASK >> leftShiftValue) & (bitmap[y] >> leftShiftValue)) | ((frameBuffer[top + y][startByteIndex]) & (MASK << (8 - leftShiftValue)));
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex] = ((((MASK >> leftShiftValue) & ((~bitmap[y]) >> leftShiftValue)) ^ ((~(frameBuffer[top + y][startByteIndex])) &  (MASK << (8 - leftShiftValue)))) ^ ((~(MASK >> leftShiftValue)) & frameBuffer[top + y][startByteIndex])) & ((MASK >> leftShiftValue) | frameBuffer[top + y][startByteIndex]);
				}
				if (x == (bytesNeeded - 1))
				{
					std::cout << "HERE" << std::endl;
					if (invertStatus)
					{
						SurfaceHandler::lineBuffer[endByteIndex] = ((MASK << rightShiftValue) & SurfaceHandler::lineBuffer[endByteIndex]) | ((SurfaceHandler::frameBuffer[top + y][endByteIndex]) & (~(MASK << rightShiftValue)));//(MASK >> (leftShiftValue + width)));
					}
					else
					{
						SurfaceHandler::lineBuffer[endByteIndex] = ((MASK << rightShiftValue) & SurfaceHandler::lineBuffer[endByteIndex]) ^ (((SurfaceHandler::frameBuffer[top + y][endByteIndex])) & (~(MASK << rightShiftValue))); ///& (MASK >> ((leftShiftValue + width))));
					}
					SurfaceHandler::frameBuffer[top + y][endByteIndex] = lineBuffer[endByteIndex];
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
			}
			else if (x == (bytesNeeded - 1))
			{
				unsigned char temp = bitmap[y];
				if (width < 8)
				{
					std::cout << "THERE" << std::endl; ///THIS IS THE FAILURE CONDITION I BELIEVE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
					///bitmap[y] = bitmap[y] >> 2; ////I DONT KNOW WHAT THE DEAL IS WITH THE NUMBER 2, but this fixes the 'o' for these cases. Somehow this number bust be mathematically derived.
					bitmap[y] = bitmap[y] >> 3; /////////The number three fixes the problems with the 'H'. Using these two data points, we can find the function that will work for whatever letter is placed wherever. So I hope. 
				}
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[endByteIndex] = ((MASK << rightShiftValue) & ((bitmap[y]) << rightShiftValue) ) | ((SurfaceHandler::frameBuffer[top + y][endByteIndex]) & (~(MASK << rightShiftValue)));
				}
				else
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (((MASK << rightShiftValue) & ((~bitmap[y]) << rightShiftValue)) ^ ((~(SurfaceHandler::frameBuffer[top + y][endByteIndex])) & (MASK >> (8 - rightShiftValue))) ^ ((~(MASK << rightShiftValue)) & SurfaceHandler::frameBuffer[top + y][endByteIndex])) & ((MASK << rightShiftValue) | SurfaceHandler::frameBuffer[top + y][endByteIndex]);
				}
				if (width < 8)
				{
					bitmap[y] = temp;
				}

				SurfaceHandler::frameBuffer[top + y][endByteIndex] = lineBuffer[endByteIndex];
			}
			else
			{
				if (invertStatus)
				{
					lineBuffer[startByteIndex + x] = ~(bitmap[y]);
				}
				else
				{
					lineBuffer[startByteIndex + x] = bitmap[y];
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex + x] = lineBuffer[startByteIndex + x];
			}
			
		}
		
	}
}

void SurfaceHandler::clearDisplay()
{
	for (int y = 0; y < SCREENHEIGHT; y++)
	{
		for (int x = 0; x < SCREENWIDTH / 8; x++)
		{
				frameBuffer[y][x] = 0b11111111;
		}
	}
	memLcd.clearDisplay();
}

void SurfaceHandler::clearLineBuffer()
{
	for (int x = 0; x < SCREENWIDTH / 8; x++)
	{
		lineBuffer[x] = 0b11111111;
	}
	memLcd.clearLineBuffer();
}

void SurfaceHandler::drawDisplay()
{
	
	for (int y = 0; y < SCREENHEIGHT; y++)
	{
		//if dirtyBits[y] == true:
		for (int x = 0; x < SCREENWIDTH / 8; x++)
		{
			lineBuffer[x] = frameBuffer[y][x];
			memLcd.writeByteToLineBuffer(x + 1, frameBuffer[y][x]);
		}
		memLcd.writeLineBufferToDisplay(y + 1);
	}
	
	sleep(2);
}