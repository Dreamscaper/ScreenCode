#include "SurfaceHandler.h"
#include <math.h>
#include <iostream>
#include <unistd.h>

using namespace std;

SurfaceHandler::SurfaceHandler() :  memLcd(SCS, DISP, EXTCOMIN, true)
{
	clearDisplay();
	clearLineBuffer();
}

void SurfaceHandler::addCircleToBuffer(int center, bool invertStatus)
{

}

void SurfaceHandler::addRectangleToBuffer(int left, int top, int width, int height, bool invertStatus)
{
	
	if (width <= 0 || height <= 0)
	{
		cout << "Even a solitary pixel is two dimensional!" << endl;
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
		cout << "Even a solitary pixel is two dimensional!" << endl;
		return; ////Even a solitary pixel is two-dimensional! 
	}
	
	int startByteIndex = ceil((left + 1) / 8.0) - 1;
	int bytesNeeded = ceil(width / 8.0);
	int endByteIndex = startByteIndex + bytesNeeded - 1;
	int shiftValue;
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < bytesNeeded; x++)
		{
			if (x == 0) ///Acting on the first byte in a line
			{
				shiftValue = ((left + 1) % 8) - 1;
				
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[startByteIndex] = (0b11111111 >> shiftValue) | ((frameBuffer[top + y][startByteIndex]) & ~(0b11111111 >> shiftValue));
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex] = ~(0b11111111 >> shiftValue) | ((frameBuffer[top + y][startByteIndex]) & ~(0b11111111 >> shiftValue));
				}
				
				if (x == bytesNeeded - 1)
				{
					shiftValue = (SCREENWIDTH - (left + width)) % 8;
					if (!invertStatus)
					{
						SurfaceHandler::lineBuffer[startByteIndex] = ~(~SurfaceHandler::lineBuffer[startByteIndex] ^ (~(0b11111111 << shiftValue) & lineBuffer[endByteIndex]));
					}
					else
					{
						SurfaceHandler::lineBuffer[startByteIndex] = ~(~SurfaceHandler::lineBuffer[startByteIndex] & (~(0b11111111 << shiftValue) & lineBuffer[endByteIndex]));
					}
					
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
			}
			else if (x == bytesNeeded - 1)
			{
				shiftValue = (SCREENWIDTH - (left + width)) % 8;
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (0b11111111 << shiftValue) | ((frameBuffer[top + y][endByteIndex]) & ~(0b11111111 << shiftValue));
				}
				else
				{
					SurfaceHandler::lineBuffer[endByteIndex] = ~(0b11111111 << shiftValue) | ((frameBuffer[top + y][endByteIndex]) & ~(0b11111111 << shiftValue));
				}
				SurfaceHandler::frameBuffer[top + y][endByteIndex] = lineBuffer[endByteIndex];
			}
			if(x != bytesNeeded - 1 && x != 0)
			{
				if (invertStatus)
				{
					lineBuffer[startByteIndex + x] = 0b11111111;
				}
				else
				{
					lineBuffer[startByteIndex + x] = 0b00000000;
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex + x] = lineBuffer[startByteIndex + x];
			}
			
		}
		
	}
	drawDisplay();
}
void SurfaceHandler::addBitmap(bool invertStatus)
{

}

void SurfaceHandler::clearDisplay()
{
	for (int y = 0; y < SCREENHEIGHT; y++)
	{
		for (int x = 0; x < SCREENWIDTH / 8; x++)
		{
				frameBuffer[y][x] = 0b11111111;
		}
		cout << endl;
	}
	
	memLcd.clearDisplay();
}

void SurfaceHandler::clearLineBuffer()
{
	for (int x = 0; x < SCREENWIDTH / 8; x++)
	{
		lineBuffer[x] = 0b00000000;
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