#ifndef __FONT_H__
#define __FONT_H__
 
typedef struct
{
	int width; // Character width in bits.
	int offset; // Offset in bytes into font bitmap.
}
FONT_CHAR_INFO;
 
 
typedef struct
{
	int height; // Character height in bits.
	int width; //Character width in bits.
	char start_char; // Start character.
	char end_char;
	int space_width;
	const FONT_CHAR_INFO *p_character_descriptor; // Character decriptor array.
	const unsigned char *p_character_bitmaps; // Character bitmap array.
}
FONT_INFO;
 
 
#endif // __FONT_H__
