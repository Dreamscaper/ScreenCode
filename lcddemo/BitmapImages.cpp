#include "BitmapImages.h"

BitmapImages::BitmapImages(const BITMAP_IMAGE_INFO &image) : bmpInfo(image)
{ 
	bmpImage = new unsigned char[bmpInfo.height * 1];  // HACK: assumes width of font is 8 bits or less
}
// Font information for Lucida Console 8pt
const BITMAP_IMAGE_INFO BatteryBitmapInfo =
{
	11, //  Character height
	8, //Character Width
	2, //BitmapCount
	0, //arrayStartIndex
};

unsigned char* BitmapImages::getBatteryBitmap1(int frame)
{
	int MASK = 0b11111111;
	
	bmpImage[0] = 0x00;
	bmpImage[1] = 0x3F;
	
	if (frame == 1)
	{
		bmpImage[2] = 0x3F;
		bmpImage[3] = 0x3F;
		bmpImage[4] = 0x7F;
		bmpImage[5] = 0x7F;
		bmpImage[6] = 0x7F;
		bmpImage[7] = 0x3F;
		bmpImage[8] = 0x3F;
	}
	else if (frame > 5)
	{
		bmpImage[2] = 0x20;
		bmpImage[3] = 0x20;
		bmpImage[4] = 0x60;
		bmpImage[5] = 0x60;
		bmpImage[6] = 0x60;
		bmpImage[7] = 0x20;
		bmpImage[8] = 0x20;
	}
	else
	{
		bmpImage[2] = ((MASK << 5) & 0x3F) | ((MASK >> (frame + 2) & 0x3F));
		bmpImage[3] = bmpImage[2];
		bmpImage[4] = ((MASK << 5) & 0x7F) | ((MASK >> (frame + 2) & 0x7F));
		bmpImage[5] = bmpImage[4];
		bmpImage[6] = bmpImage[4];
		bmpImage[7] = bmpImage[2];
		bmpImage[8] = bmpImage[2];
	}
	
	bmpImage[9] = 0x3F;
	bmpImage[10] = 0x00;
	
	return bmpImage;
	
}


unsigned char* BitmapImages::getBatteryBitmap2(int frame)
{
	/*
	int MASK = 0b11111111;
	
	bmpImage[0] = 0x00;
	bmpImage[1] = 0x3F;
	
	if (frame == 1)
	{
		bmpImage[2] = 0x3F;
		bmpImage[3] = 0x3F;
		bmpImage[4] = 0x7F;
		bmpImage[5] = 0x7F;
		bmpImage[6] = 0x7F;
		bmpImage[7] = 0x3F;
		bmpImage[8] = 0x3F;
	}
	else if (frame > 5)
	{
		bmpImage[2] = 0x20;
		bmpImage[3] = 0x20;
		bmpImage[4] = 0x60;
		bmpImage[5] = 0x60;
		bmpImage[6] = 0x60;
		bmpImage[7] = 0x20;
		bmpImage[8] = 0x20;
	}
	else
	{
		bmpImage[2] = ((MASK << 5) & 0x3F) | ((MASK >> (frame + 2) & 0x3F));
		bmpImage[3] = bmpImage[2];
		bmpImage[4] = ((MASK << 5) & 0x7F) | ((MASK >> (frame + 2) & 0x7F));
		bmpImage[5] = bmpImage[4];
		bmpImage[6] = bmpImage[4];
		bmpImage[7] = bmpImage[2];
		bmpImage[8] = bmpImage[2];
	}
	*/
		
	bmpImage[0] = 0x00;
	bmpImage[1] = 0xFE;
		
	bmpImage[2] = 0xFE;
	bmpImage[3] = 0xFE;
	bmpImage[4] = 0xFE;
	bmpImage[5] = 0xFE;
	bmpImage[6] = 0xFE;
	bmpImage[7] = 0xFE;
	bmpImage[8] = 0xFE;
		
	bmpImage[9] = 0xFE;
	bmpImage[10] = 0x00;
	
	return bmpImage;
}

