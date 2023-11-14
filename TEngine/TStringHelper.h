#ifndef __TSTRINGHELPER_H__
#define __TSTRINGHELPER_H__

namespace TStringHelper
{
	unsigned int GetStringHash(const char* data);

	void TStrNCpy(const char* src, char* dst, int length);

	int TStrNCmp(const char *src, const char *dst, unsigned int length);

	int TStrCmp(const char *src, const char *dst);

	size_t TStrLen(const char* data);

	int LastIndexOf(const char* data, char toFind, int length);

	int ConvertToInt(const char* c);

	float ConvertToFloat(const char* c);
}

#endif
