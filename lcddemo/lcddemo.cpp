#include "Window.h"
using namespace std;


SurfaceHandler surface;
Font font(lucidaConsole_8ptFontInfo);

int main()
{
	Window window(surface, font, 10,10,surface.getScreenWidth(), surface.getScreenHeight(), 1);
	//window.addTextToLine("S p a ce", 8,8, true);
	window.displayWindow();
}
