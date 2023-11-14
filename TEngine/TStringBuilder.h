#ifndef __TSTRINGBUILDER_H__
#define __TSTRINGBUILDER_H__

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#define TSTRING_BUILDER_MAX_LENGTH 512

class TStringBuilder
{
public:
	TStringBuilder();

	~TStringBuilder();

	void Append(const char* text);

	void Append(const char c);

	void Clear();

	void Remove(int start, int count);

	const char* GetResult() const;

	int GetLength() const;

private:
	char m_workingBuffer[TSTRING_BUILDER_MAX_LENGTH];

	int m_currentLength;
};

#endif
