#include "Window.h"

Window::Window(SurfaceHandler& surfac, Font& fnt, int wposX, int wposY, int width, int height, int background) :  font(fnt), surface(surfac)
{
	
	windowPosX = wposX;
	windowPosY = wposY;
	windowWidth = width;
	windowHeight = height;
	BGcolor = background;
	
	clearWindow();
	
	addTextToLine("Hellooooooooooooooooooooooooooo", 3, 2, true);
	addTextToLine("World!", 5, 1, true);
	surface.drawDisplay();
}

void Window::addTextToLine(const char* thingToSay, int row, int column, bool invert)
{
	int i = 0;
	int numColumns = (surface.getScreenWidth() / font.getCharacterWidth()) + ((surface.getScreenWidth() % font.getCharacterWidth() == 0) ? 0 : 1);
		
	while (thingToSay[i] != '\0' && (numColumns - column > 0 && column >= 0))
	{
		if (thingToSay[i] - font.getStartCharacter() >= 0 && thingToSay[i] < font.getEndCharacter())
		{
			surface.addBitmapToBuffer((column * font.getCharacterWidth()) + windowPosX, (row * font.getCharacterHeight()) + windowPosY, font.getCharacterWidth(), font.getCharacterHeight(), invert, font.getBitmap(thingToSay[i]));
		}
		column++;
		i++;
	}
}

void Window::clearWindow()
{
	if (BGcolor == 0)
	{
		surface.addRectangleToBuffer(windowPosX, windowPosY, surface.getScreenWidth() - windowPosX, surface.getScreenHeight() - windowPosY, false);
	}
	else if (BGcolor == 1)
	{
		surface.addRectangleToBuffer(windowPosX, windowPosY, surface.getScreenWidth() - windowPosX, surface.getScreenHeight() - windowPosY, true);
	}
}
