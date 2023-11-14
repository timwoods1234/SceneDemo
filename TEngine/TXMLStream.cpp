#include "TXMLStream.h"
#include "TStringBuilder.h"

//-------------------------------------------------------------------------------
TXMLStream::TXMLStream()
:	m_indentLevel(0)
{
}

//-------------------------------------------------------------------------------
TXMLStream::~TXMLStream()
{
}

//-------------------------------------------------------------------------------
bool TXMLStream::WriteString(const char* str)
{
	TStringBuilder builder;

	for (int i=0; i<m_indentLevel; ++i)
	{
		builder.Append("\t");
	}

	builder.Append(str);

	const char* result = builder.GetResult();

	int length = TStringHelper::TStrLen(result);

	return (Write(length, result) == length);
}

//-------------------------------------------------------------------------------
const char* TXMLStream::ReadString()
{
	TString result = TString::GetEmptyString();

	if (fgets(m_workingBuffer, c_workingBufferSize, m_file) == NULL)
	{
		m_endOfFile = true;
	}

	if (ferror(m_file))
	{
		m_error = true;
	}

	if (!m_endOfFile)
	{
		return m_workingBuffer;
	}

	return result.GetPointer();
}

//-------------------------------------------------------------------------------
int TXMLStream::GetIndentLevel() const
{
	return m_indentLevel;
}

//-------------------------------------------------------------------------------
void TXMLStream::SetIndentLevel(int level)
{
	m_indentLevel = level;
}
