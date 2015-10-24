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
					SurfaceHandler::lineBuffer[startByteIndex] = (MASK >> leftShiftValue) | ((frameBuffer[top + y][startByteIndex]) & (MASK >> leftShiftValue));
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex] = (~(MASK >> leftShiftValue)) ^ ((~(frameBuffer[top + y][startByteIndex])) &  (~(MASK >> leftShiftValue)));
				}
				if (x == (bytesNeeded - 1))
				{
					if (invertStatus)
					{
						SurfaceHandler::lineBuffer[endByteIndex] = ((MASK << rightShiftValue) & (MASK >> leftShiftValue)) | ((frameBuffer[top + y][startByteIndex]) & ((MASK >> (8 - rightShiftValue)) & (MASK >> leftShiftValue)));
					}
					else
					{
						SurfaceHandler::lineBuffer[endByteIndex] = (~((MASK << rightShiftValue)&(MASK >> leftShiftValue))) ^ ((~(frameBuffer[top + y][startByteIndex])) &  (~((MASK << rightShiftValue)&(MASK >> leftShiftValue))));
					}
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
			}
			else if (x == (bytesNeeded - 1))
			{
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (MASK << rightShiftValue) | ((frameBuffer[top + y][endByteIndex]) & (MASK >> (8 - rightShiftValue)));
				}
				else
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (~(MASK << rightShiftValue)) ^ ((~(frameBuffer[top + y][endByteIndex])) & (~(MASK << rightShiftValue)));
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
	//drawDisplay(); Use this for animation, otherwise it causes much lag xD
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
		cout << "Even a solitary pixel is two dimensional!" << endl;
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
					SurfaceHandler::lineBuffer[startByteIndex] = ((MASK >> leftShiftValue) & (bitmap[y] >> leftShiftValue)) | ((frameBuffer[top + y][startByteIndex]) & (MASK >> leftShiftValue));
				}
				else
				{
					SurfaceHandler::lineBuffer[startByteIndex] = (~((MASK >> leftShiftValue) & (bitmap[y] >> leftShiftValue))) ^ ((~(frameBuffer[top + y][startByteIndex])) &  (~((MASK >> leftShiftValue))));
				}
				if (x == (bytesNeeded - 1))
				{
					if (invertStatus)
					{
						SurfaceHandler::lineBuffer[endByteIndex] = (((MASK << rightShiftValue) & (bitmap[y] >>  (8 - rightShiftValue))) | ((MASK >> leftShiftValue) & (bitmap[y] << leftShiftValue))) | ((frameBuffer[top + y][startByteIndex]) & ((MASK << (rightShiftValue)) & (MASK >> leftShiftValue)));
					}
					else
					{
						SurfaceHandler::lineBuffer[endByteIndex] = (~((MASK << rightShiftValue) & (MASK >> leftShiftValue) & bitmap[y])) ^ ((~(frameBuffer[top + y][startByteIndex])) &  (~((MASK << rightShiftValue) & (MASK >> leftShiftValue))))  | ~(bitmap[y] & (MASK << (8 - rightShiftValue)));
					}
				}
				SurfaceHandler::frameBuffer[top + y][startByteIndex] = lineBuffer[startByteIndex];
			}
			else if (x == (bytesNeeded - 1))
			{
				if (invertStatus)
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (((bitmap[y] >> (8 - rightShiftValue)) & (MASK << rightShiftValue)) | ((frameBuffer[top + y][endByteIndex]) & (MASK << rightShiftValue))) ;
				}
				else
				{
					SurfaceHandler::lineBuffer[endByteIndex] = (~(MASK << rightShiftValue)) ^ ((~(frameBuffer[top + y][endByteIndex])) & (~((MASK << rightShiftValue)))) | ~(bitmap[y] & (MASK << (8 - rightShiftValue)));
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