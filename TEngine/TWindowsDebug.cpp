#include "TWindowsDebug.h"
#include "TLocator.h"

//-------------------------------------------------------------------------------
TWindowsDebug::TWindowsDebug()
:	m_file(NULL)
{
}

//-------------------------------------------------------------------------------
TWindowsDebug::~TWindowsDebug()
{
	if (m_file != NULL)
	{
		fclose(m_file);
		m_file = NULL;
	}
}

//-------------------------------------------------------------------------------
void TWindowsDebug::Log(const char *message)
{
	if (m_file == NULL)
	{
		fopen_s(&m_file, "output_log.txt", "a+");	// Open file
	}

	fprintf(m_file, message);
	fprintf(m_file, "\n");

	fflush(m_file);
}

//-------------------------------------------------------------------------------
void TWindowsDebug::Print(const char* message)
{
	OutputDebugString(message);
	OutputDebugString("\n");
}

//-------------------------------------------------------------------------------
void TWindowsDebug::Error(const char* condition, const char* message, const char* file, const char* function, int line)
{
	static char buffer[512];
	sprintf_s(&buffer[0], 512, "%s\n%s\nFile:%s\nFunction:%s\nLine:%d\n", message, condition, file, function, line);
	
	MessageBox(0, message, condition, MB_OK | MB_ICONSTOP);
	Log(("Assertion Failed: %s, %s", condition, message));

	// close the program in release mode
#if defined(DEBUG) | defined(_DEBUG)
	return;
#else
	_flushall();
	TLocator::GetApplication()->Quit();
#endif
}
