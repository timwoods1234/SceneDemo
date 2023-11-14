#include <stdio.h>

#include "TError.h"
#include "TLocator.h"
#include "TDebugInterface.h"

//-------------------------------------------------------------------------------
void _TAssert(const char* condition, const char* message, const char* file, const char* function, int line)
{
	TLocator::GetDebugSystem()->Error(condition, message, file, function, line);
}

//-------------------------------------------------------------------------------
void _TDebugPrint(const char* chString, ...)
{
	static char	buffer[1024];
	char *args;

	args = (char*) &chString + sizeof(chString);
	vsprintf_s(buffer, 1024, chString, args);

	TLocator::GetDebugSystem()->Print(buffer);
}

//-------------------------------------------------------------------------------
void _TDebugLog(const char* chString, ...)
{
	static char	buffer[1024];
	char *args;

	args = (char*) &chString + sizeof(chString);
	vsprintf_s(buffer, 1024, chString, args);

	TLocator::GetDebugSystem()->Log(buffer);
}
