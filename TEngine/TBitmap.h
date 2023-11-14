#ifndef __TBMP_H__
#define __TBMP_H__

// Custom Bitmap Loader
// Note: the image is stored upside down

#include <stdio.h>

// Bitmap header
struct BMP_Header
{
	unsigned short		magic;				// Bitmap Identifier
	unsigned int		fileSize;			// Size of the file (bytes)
	unsigned short		reserved1;			// Reserved by OS
	unsigned short		reserved2;
	unsigned int		dataOffset;			// Offset of image data
	unsigned int		headerSize;			// Header size (bytes)
	unsigned int		width;				// Image width
	unsigned int		height;				// Image height
	unsigned short		planes;
	unsigned short		bitsPerPixel;		// Bit depth
	unsigned int		compressionType;	// Currently unused
	unsigned int		imageDataSize;		// Size of image data
	unsigned int		hPixelsPerMeter;	// Horizontal resolution
	unsigned int		vPixelsPerMeter;	// Vertical resolution
	unsigned int		colorsUsed;			// Number of color indexes in the color table that are actually used by the bitmap
	unsigned int		colorsRequired;		// Number of color indexes that are required for displaying the bitmap
};

// Size of the palette data for 8 BPP bitmaps
#define BPP8_PALETTE_SIZE	(256 * 4)

class TBitmap
{
public:
	TBitmap();
	~TBitmap();

	bool ReadFile(const char* filename);
	void CompressPalette(int tolerance);

	unsigned int   GetWidth()  const;
	unsigned int   GetHeight() const;
	unsigned short GetDepth()  const;

	void GetPixelRGB(unsigned int x, unsigned int y, unsigned char *r, unsigned char *g, unsigned char *b);
	void SetPixelRGB(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
	void GetPixelIndex(unsigned int x, unsigned int y, unsigned char *value);
	void SetPixelIndex(unsigned int x, unsigned int y, unsigned char value);
	void GetPaletteColor(unsigned char index, unsigned char *r, unsigned char *g, unsigned char *b);
	void SetPaletteColor(unsigned char index, unsigned char r, unsigned char g, unsigned char b);

	char* GetLastError() const;

private:
	bool ReadHeader	(FILE* f);
	bool WriteHeader(FILE* f);
	bool ReadUINT	(unsigned int *x, FILE* f);
	bool ReadUSHORT	(unsigned short *x, FILE* f);
	int  WriteUINT	(unsigned int x, FILE* f);
	int  WriteUSHORT(unsigned short x, FILE* f);

	BMP_Header m_header;
	unsigned char* m_palette;
	unsigned char* m_data;
	char* m_lastError;
};

#endif
