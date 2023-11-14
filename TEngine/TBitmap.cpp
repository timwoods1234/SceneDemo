#include <cstdlib>

#include "TBitmap.h"
#include "TDynamicSet.h"

//-------------------------------------------------------------------------------
TBitmap::TBitmap()
{
	m_lastError = "Ok";
}

//-------------------------------------------------------------------------------
TBitmap::~TBitmap()
{
	if (m_palette != NULL)
	{
		free(m_palette);
	}

	if (m_data != NULL)
	{
		free(m_data);
	}
}

//-------------------------------------------------------------------------------
char* TBitmap::GetLastError() const 
{
	return m_lastError;
}

//-------------------------------------------------------------------------------
unsigned int TBitmap::GetWidth()  const 
{
	return m_header.width;
}

//-------------------------------------------------------------------------------
unsigned int TBitmap::GetHeight() const 
{
	return m_header.height; 
}

//-------------------------------------------------------------------------------
unsigned short TBitmap::GetDepth()  const 
{
	return m_header.bitsPerPixel; 
}

//-------------------------------------------------------------------------------
bool TBitmap::ReadFile(const char* filename)
{
	FILE* f;
	fopen_s(&f, filename, "rb");

	if (!f)
	{
		m_lastError = "Failed to load file";
		return false;
	}

	// Read header
	if (!ReadHeader(f) || m_header.magic != 0x4D42)
	{
		m_lastError = "Invalid file";
		fclose(f);
		return false;
	}

	// Check it's a supported type
	if ((m_header.bitsPerPixel != 32 && m_header.bitsPerPixel != 24 && m_header.bitsPerPixel != 8)
		|| m_header.compressionType != 0 || m_header.headerSize != 40)
	{
		m_lastError = "Format not supported";
		fclose(f);
		return false;
	}

	// Create palette for 8bpp images
	if (m_header.bitsPerPixel == 8)
	{
		m_palette = (unsigned char*) malloc(BPP8_PALETTE_SIZE * sizeof(unsigned char));
		if (m_palette == NULL)
		{
			m_lastError = "Out of memory";
			fclose(f);
			return false;
		}

		if (fread(m_palette, sizeof(unsigned char), BPP8_PALETTE_SIZE, f) != BPP8_PALETTE_SIZE)
		{
			m_lastError = "File inavlid";
			fclose(f);
			free(m_palette);
			return false;
		}
	}
	else
	{
		// image doesn't use palette
		m_palette = NULL;
	}

	// Allocate memory for image data
	m_data = (unsigned char*) malloc(m_header.imageDataSize);
	if (m_data == NULL)
	{
		m_lastError = "Out of memory";
		fclose(f);
		free(m_palette);
		return false;
	}

	// read image data
	if (fread(m_data, sizeof(unsigned char), m_header.imageDataSize, f) != m_header.imageDataSize)
	{
		m_lastError = "Invalid file";
		fclose(f);
		free(m_data);
		free(m_palette);
		return false;
	}

	fclose(f);
	return true;
}

//-------------------------------------------------------------------------------
void TBitmap::GetPixelRGB(unsigned int x, unsigned int y, unsigned char *r, unsigned char *g, unsigned char *b)
{
	// Offsets (stride)
	unsigned char	bytesPerPixel = m_header.bitsPerPixel >> 3;
	unsigned int	bytesPerRow   = m_header.imageDataSize / m_header.height;

	// Pixel position (remember it's upside down)
	unsigned char* pixel = m_data + ((m_header.height - y - 1) * bytesPerRow + x * bytesPerPixel);

	// Indexed color mode gets color from the palette
	if (m_header.bitsPerPixel == 8)
	{
		pixel = m_palette + *pixel * 4;
	}

	// Remember colors stored in BGR order
	if (r) { *r = *(pixel + 2); }
	if (g) { *g = *(pixel + 1); }
	if (b) { *b = *(pixel + 0); }
}

//-------------------------------------------------------------------------------
void TBitmap::SetPixelRGB(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
{
	// Stride
	unsigned char bytesPerPixel = m_header.bitsPerPixel >> 3;
	unsigned int bytesPerRow = m_header.imageDataSize / m_header.height;

	// pxiel location (image is upside down)
	unsigned char *pixel = m_data + ((m_header.height - y - 1) * bytesPerRow + x * bytesPerPixel);

	// Get value (BGR order)
	*(pixel + 2) = r;
	*(pixel + 1) = g;
	*(pixel + 0) = b;
}

//-------------------------------------------------------------------------------
void TBitmap::GetPixelIndex(unsigned int x, unsigned int y, unsigned char* value)
{
	// Stride
	unsigned int bytesPerRow = m_header.imageDataSize / m_header.height;

	// Pixel location
	unsigned char *pixel = m_data + ((m_header.height - y - 1) * bytesPerRow + x);

	if (value)
	{
		*value = *pixel;
	}
}

//-------------------------------------------------------------------------------
void TBitmap::SetPixelIndex(unsigned int x, unsigned int y, unsigned char value)
{
	// Stride
	unsigned int bytesPerRow = m_header.imageDataSize / m_header.height;

	// pixel location
	unsigned char *pixel = m_data + ((m_header.height - y - 1) * bytesPerRow + x);

	*pixel = value;
}

//-------------------------------------------------------------------------------
void TBitmap::GetPaletteColor(unsigned char index, unsigned char* r, unsigned char* g, unsigned char* b)
{
	if (m_header.bitsPerPixel != 8)
	{
		m_lastError = "Type Mismatch";
	}
	else
	{
		if (r) *r = *(m_palette + index * 4 + 2);
		if (g) *g = *(m_palette + index * 4 + 1);
		if (b) *b = *(m_palette + index * 4 + 0);
	}
}

//-------------------------------------------------------------------------------
void TBitmap::SetPaletteColor(unsigned char index, unsigned char r, unsigned char g, unsigned char b)
{
	if (m_header.bitsPerPixel != 8)
	{
		m_lastError = "Type Mismatch";
	}
	else
	{
		// write directly to palette
		*(m_palette + index * 4 + 2) = r;
		*(m_palette + index * 4 + 1) = g;
		*(m_palette + index * 4 + 0) = b;
	}
}

//-------------------------------------------------------------------------------
void TBitmap::CompressPalette(int tolerance)
{
	TDynamicSet<unsigned char> newPalette;
	unsigned char r, g, b;

	// add initial color to palette (top left pixel)
	GetPixelRGB(0, 0, &r, &g, &b);
	newPalette.Add(b);
	newPalette.Add(g);
	newPalette.Add(r);
	newPalette.Add(0);	// round up to 4 bits

	// for each pixel
	for (unsigned int y=0; y<GetHeight(); y++)
	{
		for (unsigned int x=0; x<GetWidth(); x++)
		{
			// Get Color
			GetPixelRGB(x, y, &r, &g, &b);

			// add color to new Palette (if needed)
			bool found = false;
			unsigned int i = 0;

			do
			{
				// is color in palette[i]?
				if (   (newPalette[i+2]-tolerance <= r && r <= newPalette[i+2]+tolerance)
					&& (newPalette[i+1]-tolerance <= g && g <= newPalette[i+1]+tolerance)
					&& (newPalette[i+0]-tolerance <= b && b <= newPalette[i+0]+tolerance))
				{
					// yes, set this pixel to point to it
					SetPixelIndex(x, y, i/4);
					found = true;

					break;
				}
				i+=4;
			}
			while (i < newPalette.GetSize());

			if (!found)
			{
				// no, add color to palette
				newPalette.Add(b);
				newPalette.Add(g);
				newPalette.Add(r);
				newPalette.Add(0);	// round up to 4 bits

				// and set pixel pointer
				SetPixelIndex(x, y, i/4);
			}

		} // for
	} // for

	// free palette & assign new one
	if (m_palette != NULL)
	{
		free(m_palette);
	}

	m_palette = (unsigned char*) malloc(newPalette.GetSize() * sizeof(unsigned char));

	if (m_palette == NULL)
	{
		m_lastError = "Out of memory";
		return;
	}

	// copy data
	for (unsigned int i=0; i<newPalette.GetSize(); i++)
	{
		m_palette[i] = newPalette[i];
	}

	// palette is now smaller, removed "similar" colors (within tolerance)
	m_header.bitsPerPixel = 8;	// treat this bitmap as an 8BPP image from now on
								// (i.e. use palette colors)
}

//-------------------------------------------------------------------------------
bool TBitmap::ReadHeader(FILE* f)
{
	if (f == NULL)
	{
		return false;
	}

	if (!ReadUSHORT(&(m_header.magic), f))			return false;
	if (!ReadUINT(&(m_header.fileSize), f))			return false;
	if (!ReadUSHORT(&(m_header.reserved1), f))		return false;
	if (!ReadUSHORT(&(m_header.reserved2), f))		return false;
	if (!ReadUINT(&(m_header.dataOffset), f))		return false;
	if (!ReadUINT(&(m_header.headerSize), f))		return false;
	if (!ReadUINT(&(m_header.width), f))			return false;
	if (!ReadUINT(&(m_header.height), f))			return false;
	if (!ReadUSHORT(&(m_header.planes), f))			return false;
	if (!ReadUSHORT(&(m_header.bitsPerPixel), f))	return false;
	if (!ReadUINT(&(m_header.compressionType), f))	return false;
	if (!ReadUINT(&(m_header.imageDataSize), f))	return false;
	if (!ReadUINT(&(m_header.hPixelsPerMeter), f))	return false;
	if (!ReadUINT(&(m_header.vPixelsPerMeter), f))	return false;
	if (!ReadUINT(&(m_header.colorsUsed), f))		return false;
	if (!ReadUINT(&(m_header.colorsRequired), f))	return false;

	return true;
}

//-------------------------------------------------------------------------------
bool TBitmap::WriteHeader(FILE* f)
{
	if (f == NULL)
	{
		return false;
	}

	if (!WriteUSHORT(m_header.magic, f))		return false;
	if (!WriteUINT(m_header.fileSize, f))		return false;
	if (!WriteUSHORT(m_header.reserved1, f))	return false;
	if (!WriteUSHORT(m_header.reserved2, f))	return false;
	if (!WriteUINT(m_header.dataOffset, f))		return false;
	if (!WriteUINT(m_header.headerSize, f))		return false;
	if (!WriteUINT(m_header.width, f))			return false;
	if (!WriteUINT(m_header.height, f))			return false;
	if (!WriteUSHORT(m_header.planes, f))		return false;
	if (!WriteUSHORT(m_header.bitsPerPixel, f))	return false;
	if (!WriteUINT(m_header.compressionType, f))return false;
	if (!WriteUINT(m_header.imageDataSize, f))	return false;
	if (!WriteUINT(m_header.hPixelsPerMeter, f))return false;
	if (!WriteUINT(m_header.vPixelsPerMeter, f))return false;
	if (!WriteUINT(m_header.colorsUsed, f))		return false;
	if (!WriteUINT(m_header.colorsRequired, f))	return false;

	return true;
}

//-------------------------------------------------------------------------------
bool TBitmap::ReadUINT(unsigned int *x, FILE* f)
{
	unsigned char little[ 4 ];

	if (x == NULL || f == NULL)
	{
		return false;
	}

	if (fread(little, 4, 1, f) != 1)
	{
		return false;
	}

	*x = (little[ 3 ] << 24 | little[ 2 ] << 16 | little[ 1 ] << 8 | little[ 0 ]);

	return true;
}

//-------------------------------------------------------------------------------
bool TBitmap::ReadUSHORT(unsigned short *x, FILE* f)
{
	unsigned char little[ 2 ];

	if (x == NULL || f == NULL)
	{
		return false;
	}

	if (fread(little, 2, 1, f) != 1)
	{
		return false;
	}

	*x = (little[ 1 ] << 8 | little[ 0 ]);

	return true;
}

//-------------------------------------------------------------------------------
int TBitmap::WriteUINT(unsigned int x, FILE* f)
{
	unsigned char little[ 4 ];

	little[ 3 ] = (unsigned char)((x & 0xff000000) >> 24);
	little[ 2 ] = (unsigned char)((x & 0x00ff0000) >> 16);
	little[ 1 ] = (unsigned char)((x & 0x0000ff00) >> 8);
	little[ 0 ] = (unsigned char)((x & 0x000000ff) >> 0);

	return (f && fwrite(little, 4, 1, f) == 1);
}

//-------------------------------------------------------------------------------
int TBitmap::WriteUSHORT(unsigned short x, FILE* f)
{
	unsigned char little[ 2 ];

	little[ 1 ] = (unsigned char)((x & 0xff00) >> 8);
	little[ 0 ] = (unsigned char)((x & 0x00ff) >> 0);

	return (f && fwrite(little, 2, 1, f) == 1);
}

