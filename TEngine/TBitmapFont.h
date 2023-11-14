#ifndef __TBITMAPFONT_H__
#define __TBITMAPFONT_H__

#ifndef __TFONT_H__
#include "TFont.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

class TTexture;
class TShader;

class TBitmapFont : public TFont
{
public:
	TBitmapFont(const char* filename);

	~TBitmapFont();

    void PrintText(const TVector2& position, const char* formattedText, ...);

private:
	void LoadTexture(const char* filename);
	void LoadMetrics(const char* filename);

	int m_widths[256];

	float m_characterWidth;
	float m_characterHeight;

	TShader* m_shader;
	
	// TODO: maybe just have a vector 2
	// or work these out from texcoords and texture size
	float m_renderSize;

	TTexture* m_texture;
};

#endif
