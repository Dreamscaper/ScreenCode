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
	surface.addRectangleToBuffer(0,0,71,71, false);
	surface.addRectangleToBuffer(30, 40, 23, 18, false);
	//surface.addRectangleToBuffer(6, 6, 5, 56, false);


	surface.drawDisplay();
	return 0;
}
