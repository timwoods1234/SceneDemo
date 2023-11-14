#include <memory.h>

#include "TStringBuilder.h"
#include "TStringHelper.h"

//-------------------------------------------------------------------------------
TStringBuilder::TStringBuilder()
:	m_currentLength(0)
{
	Clear();
}

//-------------------------------------------------------------------------------
TStringBuilder::~TStringBuilder()
{
}

//-------------------------------------------------------------------------------
void TStringBuilder::Clear()
{
	memset(m_workingBuffer, 0, TSTRING_BUILDER_MAX_LENGTH);

	m_currentLength = 0;
}

//-------------------------------------------------------------------------------
void TStringBuilder::Append(const char c)
{
	TASSERT((m_currentLength + 1 < TSTRING_BUILDER_MAX_LENGTH), "[TStringBuilder::Append(c)] Not enough space in the buffer");

	m_workingBuffer[m_currentLength] = c;

	m_currentLength++;
	m_workingBuffer[m_currentLength] = '\0';
}

//-------------------------------------------------------------------------------
void TStringBuilder::Append(const char* text)
{
	int length = TStringHelper::TStrLen(text);

	TASSERT((m_currentLength + length < TSTRING_BUILDER_MAX_LENGTH), "[TStringBuilder::Append(text)] Not enough space in the buffer");

	char* dst = m_workingBuffer + m_currentLength;

	TStringHelper::TStrNCpy(text, dst, length);

	m_currentLength += length;
}

//-------------------------------------------------------------------------------
const char* TStringBuilder::GetResult() const
{
	return m_workingBuffer;
}

//-------------------------------------------------------------------------------
void TStringBuilder::Remove(int start, int count)
{
	char* dst = m_workingBuffer + start;
	const char* src = m_workingBuffer + start + count;

	int length = m_currentLength - count - start;

	TStringHelper::TStrNCpy(src, dst, length);

	m_currentLength -= count;
	m_workingBuffer[m_currentLength] = '\0';
}

//-------------------------------------------------------------------------------
int TStringBuilder::GetLength() const
{
	return m_currentLength;
}
