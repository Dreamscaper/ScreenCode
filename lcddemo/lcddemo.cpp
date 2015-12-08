#include "Window.h"
#include "BitmapImages.h"
using namespace std;


SurfaceHandler surface;
Font font(lucidaConsole_8ptFontInfo);
BitmapImages bmaps(BatteryBitmapInfo);

int main()
{
	Window window1(surface, font, 0, 0, 96, 96, 1);
	Window window2(surface, font, 15, 15,37, 44, 0);

	window2.addTextToLine("HalloThere", 5,0, true);
	
	//surface.addBitmapToBuffer(10, 10, 4, font.getCharacterHeight(), false, font.getBitmap('T'));
	surface.drawDisplay();
	//TO FIX: Windows share one Frame Buffer...keep track of each one's contents somehow
}
