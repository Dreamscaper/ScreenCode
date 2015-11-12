
#ifndef __BITMAPIMAGES_H__
#define __BITMAPIMAGES_H__


typedef struct
{
	int height; // Character height in bits.
	int width; //Character width in bits.
	int bitmapCount;
	int startIndex;
	const unsigned char *p_bitmap_images; // Character bitmap array.
}
BITMAP_IMAGE_INFO;

extern const BITMAP_IMAGE_INFO BatteryBitmapInfo; 

class BitmapImages
{
protected:
	const BITMAP_IMAGE_INFO &bmpInfo;
	
public:
	BitmapImages(const BITMAP_IMAGE_INFO &image);
	unsigned char* getBatteryBitmap1(int frame); ///Between 1 and 10
	unsigned char* getBatteryBitmap2(int frame); ///Between 1 and 10
private:
	unsigned char *bmpImage;
};
 
#endif // __FONT_H__
