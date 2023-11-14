#include "TScreenOutputStream.h"
#include "TLocator.h"
#include "TFont.h"
#include "TVector2.h"

//-------------------------------------------------------------------------------
TScreenOutputStream::TScreenOutputStream()
{
	SetPosition(0, 0);
	SetOffset(32);

    m_font = TFont::Acquire("Debug");
}

//-------------------------------------------------------------------------------
TScreenOutputStream::~TScreenOutputStream()
{
    TFont::Release(m_font);
}

//-------------------------------------------------------------------------------
int TScreenOutputStream::Read(int bytes, void* buffer)
{
	return 0;
}

//-------------------------------------------------------------------------------
int TScreenOutputStream::Write(int bytes, const void* buffer)
{
	return 0;
}

//-------------------------------------------------------------------------------
bool TScreenOutputStream::WriteInt(int n)
{
	m_font->PrintText(m_position, "%d", n);

	PostWrite();

	return true;
}

//-------------------------------------------------------------------------------
bool TScreenOutputStream::WriteFloat(float f)
{
    // could put something in for levels of precision (probably an enum)
    m_font->PrintText(m_position, "%.2f", f);

	PostWrite();

	return true;
}

//-------------------------------------------------------------------------------
bool TScreenOutputStream::WriteString(const char* str)
{
    m_font->PrintText(m_position, str);

	PostWrite();

	return true;
}

//-------------------------------------------------------------------------------
void TScreenOutputStream::SetPosition(int x, int y)
{
	m_position.x = (float)x;
	m_position.y = (float)y;
}

//-------------------------------------------------------------------------------
void TScreenOutputStream::SetOffset(int offset)
{
	m_lineSpacing = (float)offset;
}

//-------------------------------------------------------------------------------
void TScreenOutputStream::PostWrite()
{
	m_position.y += m_lineSpacing;
}

//-------------------------------------------------------------------------------
const TVector2& TScreenOutputStream::GetPosition() const
{
    return m_position;
}

//-------------------------------------------------------------------------------
unsigned int TScreenOutputStream::GetLineSpacing() const
{
    return (unsigned int)m_lineSpacing;
}

//-------------------------------------------------------------------------------
const TColor& TScreenOutputStream::GetColor() const
{
	return m_font->GetColor();
}

//-------------------------------------------------------------------------------
void TScreenOutputStream::SetColor(const TColor& color)
{
	m_font->SetColor(color);
}