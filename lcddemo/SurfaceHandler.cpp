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
	else if (top + height < 0)
	{
		return;
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

	if (left + width > SCREENWIDTH)
	{
		width = SCREENWIDTH - left;
	}
	
	int startByteIndex = ceil((left + 1)/ 8.0) - 1;
	int bytesNeeded = ceil(width / 8.0);
	
	for(int y = 0; y < height; y++)
	{
		for (int x = 0; x < bytesNeeded; x++)
		{
			if (x == 0) ///Acting on the first byte in a line
			{
				if (!invertStatus)
				{
					SurfaceHandler::lineBuffer[startByteIndex] = (0b11111111 >> (((left + 1) % 8) - 1)) | ((frameBuffer[top + y][startByteIndex]) & ~(0b11111111 >> (((left + 1) % 8) - 1))); //Testing
					SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex] = (0b11111111 >> (((left + 1) % 8) - 1)) | ((frameBuffer[top + y][startByteIndex]) & ~(0b11111111 >> (((left + 1) % 8) - 1))); //Testing
					SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
				}
				
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
			if (y == 10 && x == 1)
			{
				frameBuffer[y][x] = 0b10101010;
			}
			else
			{
				frameBuffer[y][x] = 0b00000000;
			}
			
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