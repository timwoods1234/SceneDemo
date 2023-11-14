#ifndef __TDEBUGINTERFACE_H__
#define __TDEBUGINTERFACE_H__

class TDebugInterface
{
public:
	TDebugInterface() {}

	virtual ~TDebugInterface() {}

	virtual void Log(const char* message) = 0;

	virtual void Print(const char* message) = 0;

	virtual void Error(const char* condition, const char* message, const char* file, const char* function, int line) = 0;
};

#endif
