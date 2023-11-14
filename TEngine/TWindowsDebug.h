#ifndef __TWINDOWSDEBUG_H__
#define __TWINDOWSDEBUG_H__

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifndef __TDEBUGINTERFACE_H__
#include "TDebugInterface.h"
#endif

#ifdef TPLATFORM_WIN

class TWindowsDebug : public TDebugInterface
{
public:
	TWindowsDebug();

	~TWindowsDebug();

	void Log(const char* message);

	void Print(const char* message);

	void Error(const char* condition, const char* message, const char* file, const char* function, int line);

private:
	FILE* m_file;
};

#endif //#ifdef TPLATFORM_WIN

#endif
