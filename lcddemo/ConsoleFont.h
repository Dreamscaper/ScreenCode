// Font data for Lucida Console 8pt

#include "Font.h"

extern const unsigned char lucidaConsole_8ptBitmaps [];
extern const FONT_INFO lucidaConsole_8ptFontInfo;
extern const FONT_CHAR_INFO lucidaConsole_8ptDescriptors [];
class ConsoleFont
{
	public:
	
	int getCharacterHeight();
	int getSpaceCharacterWidth();
	int getCharacterWidth();
	unsigned char* getBitmap(char character);
	private:
	const int font_width = lucidaConsole_8ptFontInfo.width;
	const int font_height = lucidaConsole_8ptFontInfo.height;
	static unsigned char letterBitmap[];
	
	
};
