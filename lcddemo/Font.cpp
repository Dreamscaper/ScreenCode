#include "Font.h"

Font::Font(const FONT_INFO &font) : fontInfo(font)
{ 
	letterBitmap = new unsigned char[fontInfo.height * 1];  // HACK: assumes width of font is 8 bits or less
}
// FIXME: letterBitmap is orphaned, need a destructor

int Font::getCharacterHeight()
{
	return fontInfo.height;
}

int Font::getSpaceCharacterWidth()
{
	return fontInfo.space_width;
}

int Font::getCharacterWidth()
{
	return fontInfo.width;
}

char Font::getStartCharacter()
{
	return fontInfo.start_char;
}

char Font::getEndCharacter()
{
	return fontInfo.end_char;
}
unsigned char* Font::getBitmap(char character)
{
	if (!((character - fontInfo.start_char) >= 0 && character <= fontInfo.end_char))
	{
		character = '!';
	}

	for (int i = 0; i < fontInfo.height;i++)
	{
		letterBitmap[i] = fontInfo.p_character_bitmaps[fontInfo.p_character_descriptor[character - fontInfo.start_char].offset + i];
	}
	return letterBitmap;
}
