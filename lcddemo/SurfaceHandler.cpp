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
	
	int startByteIndex = (((left + 1) / 8) + (((left + 1) % 8 != 0) ? 0 : 1));
	//int bytesNeeded = (width / 8) + ((((((left + 1) % 8) == width % 8) || (((SCREENWIDTH - (left + width + 1)) % 8) == width % 8)) ? ((width % 8 == 0) ? 0 : 1) : 2));
	//int startByteIndex = ceil((left + 1) / 8.0) - 1;
	//int bytesNeeded = ceil(width / 8.0);
	
	//int shiftValue;
	
	int leftShiftValue = ((left) % 8);
	if(leftShiftValue < 0)
	{
		leftShiftValue = 0;	
	}
	int rightShiftValue = ((SCREENWIDTH - (width + left)) % 8);                                  
	if(rightShiftValue < 0)
	{
		rightShiftValue = 0;	
	}
	int bytesNeeded;
	if (width / 8 == 0)
	{
		bytesNeeded = 1;
	}
	else
	{
		bytesNeeded = (width / 8) + ((leftShiftValue == 0 && rightShiftValue == 0) ? 0 : ((leftShiftValue == 0 || rightShiftValue == 0) ? 1 : 2));
	}
	int endByteIndex = startByteIndex + bytesNeeded - 1;                                
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < bytesNeeded; x++)
		{
			if (x == 0) ///Acting on the first byte in a line
			{
				//shiftValue = ((left + 1) % 8) - 1;
				
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[startByteIndex] = (0b11111111 >> leftShiftValue) | ((frameBuffer[top + y][startByteIndex]) & (0b11111111 << (8 - leftShiftValue)));
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex] = (~(0b11111111 >> leftShiftValue)) ^ ((~(frameBuffer[top + y][startByteIndex])) &  (~(0b11111111 >> leftShiftValue)) ); //| ((frameBuffer[top + y][startByteIndex]) & (0b11111111 << (8 - leftShiftValue)));
				}
				if (x == (bytesNeeded - 1))
				{
					if (invertStatus)
					{
						SurfaceHandler::lineBuffer[endByteIndex] = (0b11111111 << rightShiftValue) | ((SurfaceHandler::lineBuffer[endByteIndex]) & (0b11111111 >> (8 - rightShiftValue)));
					}
					else
					{
						SurfaceHandler::lineBuffer[endByteIndex] = (~(0b11111111 << rightShiftValue)) ^ ((~(SurfaceHandler::lineBuffer[endByteIndex])) &  (~(0b11111111 << rightShiftValue)) );////| ((SurfaceHandler::lineBuffer[endByteIndex]) & (0b11111111 >> (8 - rightShiftValue)));
					}
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
			}
			else if (x == (bytesNeeded - 1))
			{
				//shiftValue = ((SCREENWIDTH - (left + width + 1)) % 8);

				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (0b11111111 << rightShiftValue) | ((frameBuffer[top + y][endByteIndex]) & (0b11111111 >> (8 - rightShiftValue)));
				}
				else
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (~(0b11111111 << rightShiftValue)) ^ ((~(frameBuffer[top + y][endByteIndex])) &   (~(0b11111111 << rightShiftValue)));//| ((frameBuffer[top + y][endByteIndex]) & (0b11111111 >> (8 - rightShiftValue)));
				}
				SurfaceHandler::frameBuffer[top + y][endByteIndex] = lineBuffer[endByteIndex];
			}
			else
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