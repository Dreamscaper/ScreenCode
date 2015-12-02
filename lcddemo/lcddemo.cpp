#include "Window.h"
#include "BitmapImages.h"
using namespace std;


SurfaceHandler surface;
Font font(lucidaConsole_8ptFontInfo);
BitmapImages bmaps(BatteryBitmapInfo);

int main()
{
	Window window2(surface, font, 4, 4, 50, 50, 0);
	//window2.addTextToLine("Menu", 2, 2, false);

	//surface.addBitmapToBuffer(5, 5, BatteryBitmapInfo.width, BatteryBitmapInfo.height, false, bmaps.getBatteryBitmap1(2));
	//surface.addBitmapToBuffer(5 + BatteryBitmapInfo.width, 5, BatteryBitmapInfo.width, BatteryBitmapInfo.height, false, bmaps.getBatteryBitmap2(2));
	window2.addTextToLine("HalloThar", -2,1, true);
	surface.drawDisplay();
	//TO FIX: Windows share one Frame Buffer...keep track of each one's contents somehow
}
