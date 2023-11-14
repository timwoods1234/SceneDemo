#ifndef __TUIGROUP_H__
#define __TUIGROUP_H__

// container for a group of UI items

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

class TUIEntity;

class TUIGroup : public TRefCountedObject
{
public:
    static TUIGroup* Acquire(const char* id);

    static void Release(TUIGroup* group);

	~TUIGroup();

private:
    friend class TResourceManager;
    static void Unload(TRefCountedObject* toDelete);
    static TRefCountedObject* Load(const char* filename);

	TUIGroup();

    TUIEntity* m_entity;
};

#endif
