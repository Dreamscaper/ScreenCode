#ifndef SURFACEHANDLER_H
#define SURFACEHANDLER_H


#include "MemoryLCD.h"
#include "BitmapImages.h"

#define SCREENWIDTH 96  ///NOTE: These values must match the screen's actual dimensions as defined in MemoryLCD, and SCREENWIDTH % 8 must equal 0.
#define SCREENHEIGHT 96



class SurfaceHandler
{
	private:
	  /*
   * The Raspberry Pi GPIO pins used for SPI are:
   * P1-19 (MOSI)
   * P1-21 (MISO)
   * P1-23 (CLK)
   * P1-24 (CE0)
   * P1-26 (CE1)
   */
  

	MemoryLCD memLcd;
	
	unsigned char MASK;
	
	unsigned char lineBuffer[SCREENWIDTH / 8];
	unsigned char frameBuffer[SCREENHEIGHT][SCREENWIDTH / 8];
	unsigned char dirtyBits[12];

	public:
	
	int getScreenWidth();
	int getScreenHeight();
	SurfaceHandler();

	void addCircleToBuffer(int center, bool invertStatus);
	void addRectangleToBuffer(int left, int top, int width, int height, bool invertStatus);
	void addBitmapToBuffer(int left, int top, int width, int height, bool invertStatus, unsigned char pattern);
	void addBitmapToBuffer(int left, int top, int width, int height, bool invertStatus, unsigned char bitmap []);
	void clipLeft(unsigned char* bitmap, int amount, int width, int height, bool invertStatus);
	
	//<summary>This is a really lame comment</summary>
		
	void clipRight(unsigned char* bitmap, int amount, int width, int height, bool invertStatus);
	bool findTrueCoordinates(int& left, int& top, int offsetX, int offsetY, int surfaceWidth, int surfaceHeight, int& bitmapWidth, int& bitmapHeight);
	void drawDisplay();
	void clearDisplay();
	void clearLineBuffer();
};
#endif
