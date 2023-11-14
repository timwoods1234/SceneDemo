#ifndef __TTEXTSTREAM_H__
#define __TTEXTSTREAM_H__

#ifndef __TFILESTREAM_H__
#include "TFileStream.h"
#endif

class TTextStream : public TFileStream
{
public:
				TTextStream();

				~TTextStream();

	int			ReadInt();

	float		ReadFloat();

	const char*	ReadString();

	bool		WriteInt(int n);

	bool		WriteFloat(float f);

	bool		WriteString(const char* str);
};

#endif
