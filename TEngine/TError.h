#ifndef __TERROR_H__
#define __TERROR_H__

//-------------------------------------------------------------------------------
void _TAssert(const char* condition, const char* message, const char* file, const char* function, int line);
void _TDebugPrint(const char* chString, ...);
void _TDebugLog(const char* chString, ...);

//-------------------------------------------------------------------------------
#if defined(DEBUG) | defined(_DEBUG)
#	define TASSERT(condition, message)	if ((!condition)) _TAssert(#condition, message, __FILE__, __FUNCTION__, __LINE__)
#else
#	pragma warning (disable : 4390)		// empty control statement, intended
#	define TASSERT(x, y)
#endif

//-------------------------------------------------------------------------------
#if defined(DEBUG) | defined(_DEBUG)
#	define TDebugPrint(x)		  _TDebugPrint x
#else
#	define TDebugPrint(x)
#endif

//-------------------------------------------------------------------------------
#if defined(DEBUG) | defined(_DEBUG)
#	define TDebugLog(x)		  _TDebugLog x
#else
#	define TDebugLog(x)
#endif

#endif
