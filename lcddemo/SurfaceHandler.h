#include "MemoryLCD.h"
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
  

	// use the pin name/number, not the number based on physical header position
	char SCS       = 12;      // Use any pin except the dedicated SPI SS pins?
	char DISP      = 6;      // Use any non-specialised GPIO pin
	char EXTCOMIN  = 25;	     // Use any non-specialised GPIO pin
	
	MemoryLCD memLcd;
	
	unsigned char lineBuffer[SCREENWIDTH / 8];
	unsigned char frameBuffer[SCREENHEIGHT][SCREENWIDTH / 8];
	unsigned char dirtyBits[12];

	public:
	
	SurfaceHandler();

	void addCircleToBuffer(int center, bool invertStatus);
	void addRectangleToBuffer(int left, int top, int width, int height, bool invertStatus);
	void addBitmap(bool invertStatus);

	void drawDisplay();
	void clearDisplay();
	void clearLineBuffer();
};
