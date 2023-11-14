#ifndef __TWINDOWSFILESYSTEM_H__
#define __TWINDOWSFILESYSTEM_H__

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifndef __TFILESYSTEMINTERFACE_H__
#include "TFileSystemInterface.h"
#endif

#ifdef TPLATFORM_WIN

class TWindowsFileSystem : public TFileSystemInterface
{
public:
	TWindowsFileSystem(HWND window);

	~TWindowsFileSystem();

	void OpenFileBrowser(bool fileMustExist, class TString& result);

	void GetFileList(const char* path, const char* extension, TDynamicSet<TString>& filenames);

	bool FileExists(const char* filepath);

private:
	HWND m_window;
};

#endif //#ifdef __TPLATFORM_WIN

#endif
