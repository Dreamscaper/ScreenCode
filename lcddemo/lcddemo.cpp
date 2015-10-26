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
	surface.addRectangleToBuffer(0, 0, 70, 70, false);
	surface.addBitmapToBuffer(46,46,font.getCharacterWidth(),font.getCharacterHeight(), true, font.getBitmap('A'));
	surface.drawDisplay();
	return 0;
}
