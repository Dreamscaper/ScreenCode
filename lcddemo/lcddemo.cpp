#include "Window.h"
#include "BitmapImages.h"
using namespace std;


SurfaceHandler surface;
Font font(lucidaConsole_8ptFontInfo);
BitmapImages bmaps(BatteryBitmapInfo);

int main()
{
	Window window1(surface, font, 5, 5, 40, 20, 0);
	//Window window(surface, font, 11,11,50, 50, 1);
	
	//Window window2(surface, font, 25, 25, 15, 15, 1);
	//window.addTextToLine("S p a ce", 8,8, true);
	
	//window.displayWindow();
	window1.addTextToLine("Menu", 20, 0, false);
	surface.addRectangleToBuffer(0, 22, 96, 80, true);
	surface.addBitmapToBuffer(75, 5, BatteryBitmapInfo.width, BatteryBitmapInfo.height, false, bmaps.getBatteryBitmap1(4));
	surface.addBitmapToBuffer(75 + BatteryBitmapInfo.width, 5, BatteryBitmapInfo.width, BatteryBitmapInfo.height, false, bmaps.getBatteryBitmap2(1));
	surface.drawDisplay();
	//TO FIX: Windows share one Frame Buffer...keep track of each one's contents somehow
}
