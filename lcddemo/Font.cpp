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
	if (fontInfo.space_width > 8)
	{
		return 8;
	}
	else if (fontInfo.space_width < 0)
	{
		return 0;
	}
	
	return fontInfo.space_width;
}

int Font::getCharacterWidth(char character)
{
	if (character == ' ')
	{
		return getSpaceCharacterWidth();
	}
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
	if (character == ' ')
	{
		for (int i = 0; i < fontInfo.height;i++)
		{
			letterBitmap[i] = 0b00000000;
		}
		return letterBitmap;
	}
	else if (!((character - getStartCharacter()) >= 0 && character <= getEndCharacter()))
	{
		character = '!';
	}
	
	for (int i = 0; i < fontInfo.height;i++)
	{
		letterBitmap[i] = fontInfo.p_character_bitmaps[fontInfo.p_character_descriptor[character - getStartCharacter()].offset + i];
	}
	return letterBitmap;
}
