#include "TStringHelper.h"
#include "TStreamInterface.h"

//-------------------------------------------------------------------------------
TStreamInterface::~TStreamInterface()
{
	m_error = false;
}

//-------------------------------------------------------------------------------
int TStreamInterface::ReadInt()
{
	int n = 0;

	Read(sizeof(int), (void *)&n);

	return n;
}

//-------------------------------------------------------------------------------
float TStreamInterface::ReadFloat()
{
	float f = 0;
	
	Read(sizeof(float), (void *)&f);

	return f;
}

//-------------------------------------------------------------------------------
const char* TStreamInterface::ReadString()
{
	int length = ReadInt();

	Read(length, m_workingBuffer);

	return m_workingBuffer;
}

//-------------------------------------------------------------------------------
bool TStreamInterface::WriteInt(int n)
{
	int numWritten = Write(sizeof(int), &n);
	return (numWritten == sizeof(int));
}

//-------------------------------------------------------------------------------
bool TStreamInterface::WriteFloat(float f)
{
	int numWritten = Write(sizeof(float), &f);
	return (numWritten == sizeof(float));
}

//-------------------------------------------------------------------------------
bool TStreamInterface::WriteString(const char* str)
{
	int length = TStringHelper::TStrLen(str) + 1;

	if (!WriteInt(length))
	{
		return false;
	}

	return (Write(length, str) == length);
}

//-------------------------------------------------------------------------------
bool TStreamInterface::WasError() const
{
	return m_error;
}