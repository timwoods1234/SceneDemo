#ifndef __TSINGLETON_H__
#define __TSINGLETON_H__

// Base class for singletons

#ifndef __TMEMORY_H__
#include "TMemory.h"
#endif

#ifndef __TERROR_H__
#include "TError.h"
#endif

template<class C>
class TSingleton
{
public:
	static C* Create()
	{
        TASSERT(ms_currentInstance == NULL, "Singleton has been created twice");

		TSingleton<C>::ms_currentInstance = TNew C;

		return TSingleton<C>::ms_currentInstance;
	}
	static void Destroy()
	{
		if (TSingleton<C>::ms_currentInstance != NULL)
		{
			TSafeDelete(TSingleton<C>::ms_currentInstance);

			TSingleton<C>::ms_currentInstance = NULL;
		}
	}
	static C* Get()
	{
		return ms_currentInstance;
	}

protected:
	static C* ms_currentInstance;
};

#define DefineSingleton(C) C* TSingleton<C>::ms_currentInstance = NULL;

#endif
