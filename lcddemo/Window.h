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
	~Window();
	unsigned char* bmap;
	bool findTrueCoordinates(int& left, int& top, int& bitmapWidth, int& bitmapHeight, bool invertStat);
	void addTextToLine(const char* thingToSay, int cursorX, int cursorY, bool invert);
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

