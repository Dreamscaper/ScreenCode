#include "Window.h"
#include "BitmapImages.h"
using namespace std;


SurfaceHandler surface;
Font font(lucidaConsole_8ptFontInfo);
BitmapImages bmaps(BatteryBitmapInfo);

int main()
{
	//Window window1(surface, font, 0, 0, 96, 96, 0);
	for (int i = 0; i < 50; i++)
	{
		Window window2(surface, font,i,i, 35, 35, 1);
		window2.addTextToLine("HalloThere", -3, 0, true);
		surface.drawDisplay();
	}
	///Window window2(surface, font, 7, 7,35,35, 1);
	///window2.addTextToLine("HalloThere",-3,0, true);
	///surface.drawDisplay();
		
		

		
	//Window window2(surface, font, 15, 15,35, 35, 1);

	//
	
	
	//surface.addRectangleToBuffer(5, 5, 14, 21, false);
	//surface.addBitmapToBuffer(10, 10, 4, font.getCharacterHeight(), true, font.getBitmap('T'));
	
	
	//TO FIX: Windows share one Frame Buffer...keep track of each one's contents somehow
}
