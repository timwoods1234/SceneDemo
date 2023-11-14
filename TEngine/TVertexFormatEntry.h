#ifndef __TVERTEXFORMATENTRY_H__
#define __TVERTEXFORMATENTRY_H__

#ifndef __TVERTEXFORMATTYPES_H__
#include "TVertexFormatTypes.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

struct TVertexFormatEntry
{
	TVertexFormatSize size;
	TVertexFormatUsage usage;
	int usageIndex;

	static TVertexFormatSize GetVertexElementSize(const TString& data);
	static TVertexFormatUsage GetVertexElementUsage(const TString& data);
};

#endif
