#include "Window.h"

Window::Window(SurfaceHandler& surfac, Font& fnt, int wposX, int wposY, int width, int height, int background) :  font(fnt), surface(surfac)
{
	
	windowPosX = wposX;
	windowPosY = wposY;
	windowWidth = width;
	windowHeight = height;
	BGcolor = background;
	
	clearWindow();
	
	//addTextToLine("Hellooooooooooooooooooooooooooo", 3, 2, true);
	//addTextToLine("World!", 5, 1, true);
}

void Window::addTextToLine(const char* thingToSay, int cursorX, int cursorY, bool invert)
{
	int i = 0;
		
	while (thingToSay[i] != '\0')
	{
		if (cursorX + font.getCharacterWidth(thingToSay[i]) > windowPosY + windowWidth)
		{
			//TO FIX: Add checks for text in bounds
		}
		surface.addBitmapToBuffer(cursorX + windowPosX, cursorY + windowPosY, font.getCharacterWidth(thingToSay[i]), font.getCharacterHeight(), invert, font.getBitmap(thingToSay[i]));
		cursorX += font.getCharacterWidth(thingToSay[i]);
		i++;
	}

}

void Window::clearWindow()
{
	if (BGcolor == 0)
	{
		surface.addRectangleToBuffer(windowPosX, windowPosY, windowWidth, windowHeight, false);
	}
	else if (BGcolor == 1)
	{
		surface.addRectangleToBuffer(windowPosX, windowPosY, windowWidth, windowHeight, true);
	}
}

void Window::displayWindow()
{
	surface.drawDisplay();
}
