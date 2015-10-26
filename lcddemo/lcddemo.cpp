#include <unistd.h>
#include <cmath>
#include <iostream>
#include "ConsoleFont.h"
#include "SurfaceHandler.h"
using namespace std;


SurfaceHandler surface;
ConsoleFont font;

void addTextToLine(char*, ConsoleFont, int, int, bool);

int main() {
	//surface.addRectangleToBuffer(0, 0, 20, 20, false);
	//surface.addRectangleToBuffer(9,9,15,6, true);
	surface.addRectangleToBuffer(0, 0, 96, 96, false);
	addTextToLine("Hello", font, 3, 2, true);
	addTextToLine("World!", font, 5, 1, true);
	surface.drawDisplay();
	//surface.addBitmapToBuffer(46,46,font.getCharacterWidth(),font.getCharacterHeight(), true, font.getBitmap('A'));
	//surface.drawDisplay();
	return 0;
}

/*
Takes in a null terminated string, and writes up to twelve letters onto a line at the specified location.
Row and column are values starting at zero and go up to eleven.
*/

void addTextToLine(char* thingToSay, ConsoleFont fnt, int row, int column, bool invert)
{
	int i = 0;
	while (thingToSay[i] != '\0' && 11 - column >= 0)
	{
		if (thingToSay[i] - fnt.getStartCharacter() >= 0 && thingToSay[i] < fnt.getEndCharacter())
		{
			surface.addBitmapToBuffer(column * 8, row * 8, fnt.getCharacterWidth(), fnt.getCharacterHeight(), invert, fnt.getBitmap(thingToSay[i]));
		}
		column++;
		i++;
	}
}
