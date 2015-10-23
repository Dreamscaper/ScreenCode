#include "SurfaceHandler.h"
#include <unistd.h>
#include <cmath>
#include <iostream>

using namespace std;

SurfaceHandler surface;

int main() {
	surface.addRectangleToBuffer(0, 0, 20, 20, false);
	surface.addRectangleToBuffer(9,9,15,6, true);
	surface.drawDisplay();
	return 0;
}
