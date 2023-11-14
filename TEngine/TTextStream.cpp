#include <stdio.h>
#include <memory.h>

#include "TTextStream.h"
#include "TStringHelper.h"

//-------------------------------------------------------------------------------
TTextStream::TTextStream()
{
	memset(m_workingBuffer, 0, c_workingBufferSize);
}

//-------------------------------------------------------------------------------
TTextStream::~TTextStream()
{
}

//-------------------------------------------------------------------------------
int TTextStream::ReadInt()
{
	TString nextLine = ReadString();

	return TStringHelper::ConvertToInt(nextLine.GetPointer());
}

//-------------------------------------------------------------------------------
float TTextStream::ReadFloat()
{
	TString nextLine = ReadString();

	return TStringHelper::ConvertToFloat(nextLine.GetPointer());
}

//-------------------------------------------------------------------------------
const char* TTextStream::ReadString()
{
	TString result = TString::GetEmptyString();

	if (fgets(m_workingBuffer, c_workingBufferSize, m_file) == NULL)
	{
		m_endOfFile = true;
	}
	else
	{
		result = m_workingBuffer;

		result.Remove('\n');
	}

	if (ferror(m_file))
	{
		m_error = true;
	}

	return result.GetPointer();
}

//-------------------------------------------------------------------------------
bool TTextStream::WriteInt(int n)
{
	int result = sprintf_s(m_workingBuffer, sizeof(int), "%d", n);

	if (result != -1)
	{
		return WriteString(m_workingBuffer);
	}

	return false;
}

//-------------------------------------------------------------------------------
bool TTextStream::WriteFloat(float f)
{
	int result = sprintf_s(m_workingBuffer, sizeof(int), "%.1f", f);

	if (result != -1)
	{
		return WriteString(m_workingBuffer);
	}

	return false;
}

//-------------------------------------------------------------------------------
bool TTextStream::WriteString(const char* str)
{
	int length = TStringHelper::TStrLen(str);

	return (Write(length, str) == length);
}