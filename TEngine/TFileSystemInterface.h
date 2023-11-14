#ifndef __TFILESYSTEMINTERFACE_H__
#define __TFILESYSTEMINTERFACE_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TString;

class TFileSystemInterface
{
public:
	TFileSystemInterface() {}

	virtual ~TFileSystemInterface() {}

	// returns the filename selected/entered
	virtual void OpenFileBrowser(bool fileMustExist, class TString& result) = 0;

	virtual void GetFileList(const char* path, const char* extension, TDynamicSet<TString>& filenames) = 0;

	virtual bool FileExists(const char* filepath) = 0;
};

#endif
