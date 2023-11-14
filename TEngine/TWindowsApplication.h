#ifndef __TWINDOWSAPPLICATION_H__
#define __TWINDOWSAPPLICATION_H__

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifdef TPLATFORM_WIN

#ifndef __TAPPLICATIONINTERFACE_H__
#include "TApplicationInterface.h"
#endif

class TWindowsApplication : public TApplicationInterface
{
public:
	TWindowsApplication(HINSTANCE hInst, const char* title);

	~TWindowsApplication();

	void Run();

	void Quit();

	void OpenFileBrowser(bool fileMustExist, class TString& strResult);

	LRESULT MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	HWND GetWindow() const;

	HINSTANCE GetInstance() const;

protected:
	bool SetupWindow(HINSTANCE hInst, const char* title);

private:
	HWND m_window;

	HINSTANCE m_instance;
};

#endif //#ifdef TPLATFORM_WIN

#endif // #ifndef __TWINDOWSAPPLICATION_H__
