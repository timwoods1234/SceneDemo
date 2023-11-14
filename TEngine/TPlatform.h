#ifndef __TPLATFORM_H__
#define __TPLATFORM_H__

#if defined(WIN32) || defined(_WIN32) || defined(WINDOWS) || defined(_WINDOWS)
#	define TPLATFORM_WIN
#	pragma comment(lib, "winmm.lib")
#	include <windows.h>
#	include <stdio.h>
#endif

#endif
