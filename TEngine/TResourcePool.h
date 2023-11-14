#ifndef __TRESOURCEPOOL_H__
#define __TRESOURCEPOOL_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TRefCountedObject;

typedef TRefCountedObject* (*LoadResourceCallback) (const char* id);
typedef void (*UnloadResourceCallback) (TRefCountedObject* resource);

class TResourcePool
{
public:
	TResourcePool(const char* id, LoadResourceCallback loadFunction, UnloadResourceCallback unloadFunction);

	~TResourcePool();

	TRefCountedObject* Allocate(const char* id);

	void Release(TRefCountedObject* resource);

private:
	TString m_id;

	LoadResourceCallback m_loadFunction;

	UnloadResourceCallback m_unloadFunction;

	TDynamicSet<TRefCountedObject*> m_resources;
};

#endif
