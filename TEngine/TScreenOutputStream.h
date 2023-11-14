#ifndef __TSCREENOUTPUTSTREAM_H__
#define __TSCREENOUTPUTSTREAM_H__

#ifndef __TSTREAMINTERFACE_H__
#include "TStreamInterface.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

struct TColor;
class TFont;

class TScreenOutputStream : public TStreamInterface
{
public:
				TScreenOutputStream();

				~TScreenOutputStream();

    int			Read(int bytes, void* buffer);

    int			Write(int bytes, const void* buffer);
	
	bool		WriteInt(int n);

	bool		WriteFloat(float f);

	bool		WriteString(const char* str);

	void		SetPosition(int x, int y);

	void		SetOffset(int offset);

    const TVector2& GetPosition() const;

    unsigned int GetLineSpacing() const;

	const TColor& GetColor() const;

	void SetColor(const TColor& color);

private:
	void		PostWrite();

    TFont* m_font;

	TVector2 m_position;

	float m_lineSpacing;

	unsigned int m_fontId;
};

#endif
