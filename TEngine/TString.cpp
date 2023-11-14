#include "TString.h"
#include "TStringHelper.h"

//-------------------------------------------------------------------------------
char s_workingBuffer[1024];

//-------------------------------------------------------------------------------
const TString& TString::GetEmptyString()
{
	static const TString s_emptyString = "";

	return s_emptyString;
}

//-------------------------------------------------------------------------------
TString::TString()
:	m_poolEntry(NULL)
{
}

//-------------------------------------------------------------------------------
TString::TString(const char* data)
:	m_poolEntry(NULL)
{
	*this = data;
}

//-------------------------------------------------------------------------------
TString::TString(const TString& other)
{
	m_poolEntry = other.m_poolEntry;

	if (m_poolEntry != NULL)
	{
		m_poolEntry->refCount++;
	}
}

//-------------------------------------------------------------------------------
TString::~TString()
{
	if (m_poolEntry != NULL)
	{
		TStringPool::Deallocate(m_poolEntry);

		m_poolEntry = NULL;
	}
}

//-------------------------------------------------------------------------------
const char* TString::GetPointer() const
{
	if (m_poolEntry != NULL)
	{
		return TStringPool::GetData(*m_poolEntry);
	}

	return "";
}

//-------------------------------------------------------------------------------
bool TString::operator==(const char* data) const
{
	return TStringHelper::TStrCmp(data, GetPointer()) == 0;
}

//-------------------------------------------------------------------------------
TString& TString::operator=(const TString& other)
{
	if (other.m_poolEntry == m_poolEntry)
	{
		return *this;
	}

	if (m_poolEntry != NULL)
	{
		TStringPool::Deallocate(m_poolEntry);
	}

	m_poolEntry = other.m_poolEntry;

	if (m_poolEntry != NULL)
	{
		m_poolEntry->refCount++;
	}

	return *this;
}

//-------------------------------------------------------------------------------
const TString TString::operator+(const TString& other)
{
	TString result = *this;
	result += other;
	return result;
}

//-------------------------------------------------------------------------------
bool TString::operator!=(const TString& other) const
{
	return !(*this == other);
}

//-------------------------------------------------------------------------------
bool TString::operator!=(const char* data) const
{
	return !(*this == data);
}

//-------------------------------------------------------------------------------
const TString TString::operator+(const char* data)
{
	TString result = *this;
	result += data;
	return result;
}

//-------------------------------------------------------------------------------
TString& TString::operator+=(const char* data)
{
	if (m_poolEntry == NULL)
	{
		m_poolEntry = TStringPool::Allocate(data);
	}
	else
	{
		int otherLength = TStringHelper::TStrLen(data);
		int currentLength = GetLength();
		char* dst = s_workingBuffer + currentLength;

		TStringHelper::TStrNCpy(GetPointer(), s_workingBuffer, currentLength);
		TStringHelper::TStrNCpy(data, dst, otherLength);

		*this = s_workingBuffer;
	}

	return *this;
}

//-------------------------------------------------------------------------------
TString& TString::operator+=(const TString& other)
{
	return (*this += other.GetPointer());
}

//-------------------------------------------------------------------------------
int TString::GetLength() const
{
	if (m_poolEntry != NULL)
	{
		return m_poolEntry->stringLength;
	}

	return 0;
}

//-------------------------------------------------------------------------------
TString TString::Format(const char* format, ...)
{
	TString result;

	char* args = (char*) &format + sizeof(format);

	vsprintf_s(s_workingBuffer, 1024, format, args);

	result = s_workingBuffer;

	return result;
}

//-------------------------------------------------------------------------------
bool TString::IsEmpty() const
{
	return GetLength() == 0;
}

//-------------------------------------------------------------------------------
void TString::Remove(int index, int count)
{
	TStringHelper::TStrNCpy(GetPointer(), s_workingBuffer, index);

	char* dst = s_workingBuffer + index;
	const char* src = GetPointer() + index + count;

	if (count != -1)
	{
		int length = GetLength() - count - index;

		TStringHelper::TStrNCpy(src, dst, length);
	}

	*this = s_workingBuffer;
}

//-------------------------------------------------------------------------------
void TString::Clear()
{
	*this = TString::GetEmptyString();
}

//-------------------------------------------------------------------------------
void TString::Split(char splitter, TDynamicSet<TString>& output) const
{
	output.Clear();

	int length = GetLength();

	if (length > 0)
	{
		const char* src = GetPointer();
		const char* srcPrev = src;
		const char* end = src + length;
		int dstIndex = 0;

		while (src < end)
		{
			if (*src == splitter)
			{
				dstIndex = 0;

				while (srcPrev < src)
				{
					if (*srcPrev != splitter)
					{
						s_workingBuffer[dstIndex] = *srcPrev;
						dstIndex++;
					}

					srcPrev++;
				}

				if (dstIndex > 0)
				{
					s_workingBuffer[dstIndex] = '\0';

					TString subString = s_workingBuffer;
					output.Add(subString);
				}
			}

			src++;
		}

		// copy the remaining string
		dstIndex = 0;
		while (srcPrev < src)
		{

			if (*srcPrev != splitter)
			{
				s_workingBuffer[dstIndex] = *srcPrev;
				dstIndex++;
			}

			srcPrev++;
		}

		if (dstIndex > 0)
		{
			s_workingBuffer[dstIndex] = '\0';

			TString subString = s_workingBuffer;
			output.Add(subString);
		}
	}
}

//-------------------------------------------------------------------------------
void TString::Remove(char c)
{
	const char* src = GetPointer();
	char* dst = s_workingBuffer;

	while (*src)
	{
		if (*src != c)
		{
			*dst++ = *src;
		}

		src++;
	}

	*dst = '\0';

	*this = s_workingBuffer;
}

//-------------------------------------------------------------------------------
int TString::Find(const char* text, int startIndex) const
{
	int textLength = TStringHelper::TStrLen(text);

	if (textLength == 0 || startIndex  < 0)
	{
		return -1;
	}

	int result = -1;

	int index = startIndex;
	int length = GetLength();
	const char* data = GetPointer();

	while (index + textLength <= length)
	{
		if (data[index] == text[0])
		{
			const char* start = data + index;

			if (TStringHelper::TStrNCmp(start, text, textLength) == 0)
			{
				result = index;
				break;
			}
		}

		index++;
	}

	return result;
}

//-------------------------------------------------------------------------------
int TString::IndexOf(char toFind) const
{
	int result = -1;
	int length = GetLength();

	if (length > 0)
	{
		int index = 0;
		const char* data = GetPointer();

		while (*data != toFind && index < length)
		{
			data++;
			index++;
		}

		if (index < length)
		{
			result = index;
		}
	}

	return result;
}

//-------------------------------------------------------------------------------
int TString::LastIndexOf(char toFind) const
{
	return TStringHelper::LastIndexOf(GetPointer(), toFind, GetLength());
}

//-------------------------------------------------------------------------------
TString TString::SubString(int start, int length) const
{
	TString result;

	int endPos = (length == -1) ? GetLength() : (start + length);

	if (start < endPos)
	{
		int count = endPos - start;

		const char* src = GetPointer() + start;

		TStringHelper::TStrNCpy(src, s_workingBuffer, count);

		s_workingBuffer[count] = '\0';

		result = s_workingBuffer;
	}

	return result;
}

//-------------------------------------------------------------------------------
bool TString::Contains(const char* text) const
{
	return (Find(text) != -1);
}
