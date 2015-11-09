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
	//int numSpaces = 0;
	
	/*while (thingToSay[i] != '\0')
	{
		if (thingToSay[i] == ' ')
		{
			numSpaces++;
		}
		i++;
	}*/
	
	//int stringWidth = (((i - numSpaces) + 1) * font.getCharacterWidth('A')) + (numSpaces * font.getCharacterWidth(' '));
	
	//int numColumns = (surface.getScreenWidth() / stringWidth) + ((surface.getScreenWidth() % stringWidth == 0) ? 0 : 1);
		
	while (thingToSay[i] != '\0')
	{
		surface.addBitmapToBuffer(cursorX + windowPosX, cursorY + windowPosY, font.getCharacterWidth(thingToSay[i]), font.getCharacterHeight(), invert, font.getBitmap(thingToSay[i]));
		cursorX += font.getCharacterWidth(thingToSay[i]);
		i++;
	}
	/*while (thingToSay[i] != '\0' && (numColumns - column > 0 && column >= 0))
	{
		surface.addBitmapToBuffer((column * font.getCharacterWidth(thingToSay[i])) + windowPosX, (cursorY * font.getCharacterHeight()) + windowPosY, font.getCharacterWidth(thingToSay[i]), font.getCharacterHeight(), invert, font.getBitmap(thingToSay[i]));
		column++;
		i++;
	}*/
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

void Window::displayWindow()
{
	surface.drawDisplay();
}
