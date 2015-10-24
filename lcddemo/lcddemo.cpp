#include <unistd.h>
#include <cmath>
#include <iostream>
#include "ConsoleFont.h"
#include "SurfaceHandler.h"
using namespace std;

SurfaceHandler surface;
ConsoleFont font;

int main() {
	//surface.addRectangleToBuffer(0, 0, 20, 20, false);
	//surface.addRectangleToBuffer(9,9,15,6, true);
	//surface.addRectangleToBuffer(0, 0, 50, 50, false);
	surface.addBitmapToBuffer(25,25,font.getCharacterWidth(),font.getCharacterHeight(), false, font.getBitmap('A'));
	surface.drawDisplay();
	return 0;
}
