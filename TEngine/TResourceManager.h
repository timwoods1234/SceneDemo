#ifndef __TRESOURCEMANAGER_H__
#define __TRESOURCEMANAGER_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TRESOURCEPOOL_H__
#include "TResourcePool.h"
#endif

#ifndef __TRESOURCETYPE_H__
#include "TResourceType.h"
#endif

class TResourceManager : public TSingleton<TResourceManager>
{
public:
	TResourceManager();

	~TResourceManager();

	TRefCountedObject* Allocate(TResourceType type, const char* id);

	void Release(TResourceType type, TRefCountedObject* resource);

private:
	void SetupPool(TResourceType type, const char* id, LoadResourceCallback loadCallback, UnloadResourceCallback unloadCallback);

	 TResourcePool* m_resourcePools[ResourceType_MAX];
};

#endif
