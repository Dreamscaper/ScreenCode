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
	surface.addRectangleToBuffer(20, 20, 10, 10, false);
	surface.drawDisplay();
	return 0;
}
