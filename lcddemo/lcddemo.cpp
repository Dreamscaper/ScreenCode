#include "SurfaceHandler.h"
#include <unistd.h>
#include <cmath>
#include <iostream>

using namespace std;

SurfaceHandler surface;

bool dosomething = true;

int main() {
	surface.clearDisplay();
	surface.clearLineBuffer();
	surface.addRectangleToBuffer(-5,-5,105,105, false);
	surface.addRectangleToBuffer(10, 10, 7, 7, true);
	surface.addRectangleToBuffer(50, 50, 20, 20, true);
	surface.addRectangleToBuffer(48, 48, 6, 7, false);
	surface.drawDisplay();
	return 0;
}
