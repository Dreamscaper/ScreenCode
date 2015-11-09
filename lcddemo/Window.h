#ifndef WINDOW_H
#define WINDOW_H
#include "ConsoleFont.h"
#include "SurfaceHandler.h"

class Window
{
	public:
	/*
	BackGroundColor:
	0 = Black;
	1 = White;
	all else is transparent.
	*/
	Window(SurfaceHandler &surfacehandler, Font &consolefont, int windowPositionX, int windowPositionY, int width, int height, int backgroundColor);
	void addTextToLine(const char*, int, int, bool);
	void clearWindow();
	void displayWindow();
	private:
	Font &font;
	SurfaceHandler &surface;
	int windowPosX;
	int windowPosY;
	int windowWidth;
	int windowHeight;
	int BGcolor;
};
#endif
