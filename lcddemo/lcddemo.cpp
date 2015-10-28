#include "Window.h"
using namespace std;


SurfaceHandler surface;
Font font(lucidaConsole_8ptFontInfo);

int main()
{
	Window window(surface, font, 10,10,surface.getScreenWidth(), surface.getScreenHeight(), 0);
	window.addTextToLine("Hello", 1, 1, true);
}
