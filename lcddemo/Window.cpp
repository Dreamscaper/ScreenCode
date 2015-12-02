#include "Window.h"

Window::Window(SurfaceHandler& surfac, Font& fnt, int wposX, int wposY, int width, int height, int background) :  font(fnt), surface(surfac)
{
	
	windowPosX = wposX;
	windowPosY = wposY;
	windowWidth = width;
	windowHeight = height;
	BGcolor = background;
	
	bmap = new unsigned char[font.getCharacterHeight()];
	clearWindow();
	
	
}

void Window::addTextToLine(const char* thingToSay, int cursorX, int cursorY, bool invert)
{
	int i = 0;
	int width = 0;
	int height = 0;
	
	cursorX = cursorX + windowPosX;
	while (thingToSay[i] != '\0')
	{
		for (int j = 0;j < font.getCharacterHeight(); j++)
		{
			bmap[j] = font.getBitmap(thingToSay[i])[j];
		}
		
		width = font.getCharacterWidth(thingToSay[i]);
		height = font.getCharacterHeight();
		

		if (Window::findTrueCoordinates(cursorX, cursorY, width, height))
		{
			surface.addBitmapToBuffer(cursorX, cursorY, width, height, invert, bmap);
		}
			cursorX = cursorX + width; // This is broken
			i++;
	}

}

bool Window::findTrueCoordinates(int& left, int& top, int& bitmapWidth, int& bitmapHeight)
{
	if (bitmapWidth <= 0 || bitmapHeight <= 0)
	{
		
		return false; ////Even a solitary pixel is two-dimensional! 
	}
	if (left < windowPosX)
	{
		bitmapWidth = (left + bitmapWidth) - windowPosX;
		left = windowPosX;
		surface.clipRight(bmap, 8 - bitmapWidth, bitmapHeight);
	}
	else if (left > windowWidth + windowPosX)
	{
		return false;
	}
	
	if (top < windowPosY)
	{
		bitmapHeight = (top + bitmapHeight) - windowPosY;
		top = windowPosY;
	}
	else if (top >= windowHeight + windowPosY)
	{
		return false;
	}
	
	if (top + bitmapHeight >= windowHeight + windowPosY)
	{
		bitmapHeight = (windowHeight + windowPosY) - top;
	}
	if (left + bitmapWidth >= windowWidth + windowPosX)
	{
		bitmapWidth = (windowPosX + windowWidth) - left;
		surface.clipRight(bmap, bitmapWidth, bitmapHeight);
	}
	
	if (bitmapWidth <= 0 || bitmapHeight <= 0)
	{
		return false; ////Even a solitary pixel is two-dimensional! 
	}
	
	return true;
}

void Window::clearWindow()
{
	if (BGcolor == 1)
	{
		surface.addRectangleToBuffer(windowPosX, windowPosY, windowWidth, windowHeight, false);
	}
	else if (BGcolor == 0)
	{
		surface.addRectangleToBuffer(windowPosX, windowPosY, windowWidth, windowHeight, true);
	}
}

Window::~Window()
{
	delete [] bmap;
}
