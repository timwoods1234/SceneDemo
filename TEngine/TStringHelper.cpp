#include "TStringHelper.h"

//-------------------------------------------------------------------------------
void TStringHelper::TStrNCpy(const char* src, char* dst, int length)
{
	int count = 0;

	while (count < length)
	{
		*dst++ = *src++;
		count++;
	}

	*dst = '\0';
}

//-------------------------------------------------------------------------------
unsigned int TStringHelper::GetStringHash(const char* data)
{
	unsigned int j   = 0;
	unsigned int r   = 0;
	unsigned int len = TStrLen(data);

	for(unsigned int i = 0; i < len; ++i)
	{
		unsigned int x = data[i] - ' ';

		j += ( ( (i & 4) >> 2 ) + (i & 1) ) >> 1;
		j &= 3;
        r += x << ( ( (i & 3) << 3 ) + j );
	}

	return r;
}

//-------------------------------------------------------------------------------
int TStringHelper::TStrNCmp(const char *src, const char *dst, unsigned int length)
{
	for ( ; length--; ++src, ++dst)
	{
		if (*src != *dst)
		{
			return (*src - *dst);
		}
	}

	return 0;
}

//-------------------------------------------------------------------------------
int TStringHelper::TStrCmp(const char *src, const char *dst)
{
    while(*src && (*src == *dst))
	{
        src++;
		dst++;
	}

    return *(const unsigned char*)src - *(const unsigned char*)dst;
}

//-------------------------------------------------------------------------------
size_t TStringHelper::TStrLen(const char* data)
{
	char const *pos;

	for (pos = data; *pos; ++pos)
		;

	return pos - data;
}

//-------------------------------------------------------------------------------
int TStringHelper::LastIndexOf(const char* data, char toFind, int length)
{
	int result = -1;

	if (length > 0)
	{
		int index = length - 1;
		const char* currentData = data + index;

		while (*currentData != toFind && index >= 0)
		{
			currentData--;
			index--;
		}

		if (index >= 0)
		{
			result = index;
		}
	}

	return result;
}

//-------------------------------------------------------------------------------
int TStringHelper::ConvertToInt(const char* c)
{
	int result = 0;
	int sign = 1;

	if (*c == '-')
	{
		sign = -1;
		c++;
	}
	else if (*c == '+')
	{
		c++;
	}

	while ((*c >= '0') && (*c <= '9'))
	{
        result = result * 10 + (*c - '0');
        c++;
	}

	return result * sign;
}

//-------------------------------------------------------------------------------
float TStringHelper::ConvertToFloat(const char* c)
{
	float rez = 0;
	int fact = 1;

	if (*c == '-')
	{
		c++;
		fact = -1;
	}

	for (int point_seen = 0; *c; c++)
	{
		if (*c == '.')
		{
			point_seen = 1;
			continue;
		}

		int d = *c - '0';

		if (d >= 0 && d <= 9)
		{
			if (point_seen)
			{
				fact *= 10;
			}

			rez = rez * 10.0f + (float)d;
		}
	}

	return rez / fact;
}