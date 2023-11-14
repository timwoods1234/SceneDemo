#ifndef __TUTIL_H__
#define __TUTIL_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

namespace TUtil
{
	// return a file path, minus the leaf (filename & extension)
    // TODO: move this to TString?
	TString GetFilePath(const char* filename);
}

#endif
