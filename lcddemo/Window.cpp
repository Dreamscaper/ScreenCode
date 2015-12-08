#include "Window.h"
using namespace std;

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
	cursorY = cursorY + windowPosY;
	while (thingToSay[i] != '\0')
	{
		for (int j = 0;j < font.getCharacterHeight(); j++)
		{
			bmap[j] = font.getBitmap(thingToSay[i])[j];
		}
		
		width = font.getCharacterWidth(thingToSay[i]);
		height = font.getCharacterHeight();
		
		std::cout << "Orig X=" << cursorX << ", Y=" << cursorY << ", width=" << width << ", height=" << height <<  std::endl;
		if (Window::findTrueCoordinates(cursorX, cursorY, width, height, invert))
		{
			std:cout << "True X=" << cursorX << ", Y=" << cursorY << ", width=" << width << ", height=" << height << std::endl;
//				std::cout << cursorX << " " << width << std::endl;
			surface.addBitmapToBuffer(cursorX,cursorY, width, height, invert, bmap);
		}
			cursorX += width; // This is broken
			i++;
	}

}

bool Window::findTrueCoordinates(int& left, int& top, int& bitmapWidth, int& bitmapHeight, bool invertStat)
{
	int leftVal = left;
	int topVal = top;
	int bW = bitmapWidth;
	int bH = bitmapHeight;


	std::cout << "BITMAP LEFT: " << leftVal;
	std::cout << " BITMAP RIGHT: " << (leftVal + bW);
	
	std::cout << " BITMAP WIDTH: " << bW;
	std::cout << " WINDOWPOSX: " << windowPosX;
	std::cout << " WINDOW_WIDTH: " << windowWidth << std::endl;
	
	
	if (bW <= 0 || bH <= 0)
	{
		return false; ////Even a solitary pixel is two-dimensional! 
	}
	if (leftVal < windowPosX)
	{
		if ((leftVal + bW) < windowPosX)
		{
			std::cout << "Width or Height not acceptable value, upon First Check. Returned false." << std::endl;
			return false;
		}
		bW = (left + bW) - windowPosX;
		leftVal = windowPosX;
		surface.clipLeft(bmap, bitmapWidth - bW, bitmapWidth, bH, invertStat);
		
		//left = leftVal;
		//top	= topVal;
		//bitmapWidth = bW;
		//bitmapHeight = bH;
		
		std::cout << "LEFT_CLIPPING: ";
		std::cout << " New Bitmap Width: " << bW;
		std::cout << " New Left Val: " << leftVal;
		std::cout << " Left Clipping: " << (8 - bW) << endl;
	}
	else if (leftVal >= (windowWidth + windowPosX))
	{
		std::cout << "Left was greater than bW. Returned false." << std::endl;
		return false;
	}
	
	
	if ((leftVal + bW) >= (windowWidth + windowPosX))
	{
		int newBW = (windowPosX + windowWidth) - (leftVal);
		surface.clipRight(bmap, (bW - newBW ),bW, bH, invertStat);
		bW = newBW;
		// left = leftVal;
		// top	= topVal;
		// bitmapWidth = bW;
		// bitmapHeight = bH;
		std::cout << "RIGHT_CLIPPING: ";
		std::cout << " New Bitmap Width: " << bW;
		std::cout << " New Left Val: " << leftVal;
		std::cout << " Right Clipping: " << (8 - bW) << endl;
	}
	/*
	if (topVal < windowPosY)
	{
		bH = (topVal + bH) - (windowPosY);
		topVal = windowPosY;
	}
	else if (topVal > windowHeight + windowPosY)
	{
		return false;
	}
	
	if (topVal + bH > windowHeight + windowPosY)
	{
		bH = (windowHeight + windowPosY) - topVal;
	}
	*/
	
	
	if (bW <= 0 || bH <= 0)
	{
		return false; ////Even a solitary pixel is two-dimensional! 
		std::cout << "Width or Height not acceptable value, upon Second Check. Returned false." << std::endl;
	}
	
	left = leftVal;
	top	= topVal;
	bitmapWidth = bW;
	bitmapHeight = bH;
	
	return true;
}

void Window::clearWindow()
{
	std::cout << "clearWindow(" << windowPosX << "," << windowPosY << "," << windowWidth << "," << windowHeight << ")" << std::endl;
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
