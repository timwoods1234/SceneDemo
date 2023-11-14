#include "TUIGroup.h"
#include "TMemory.h"
#include "TXMLReader.h"
#include "TError.h"
#include "TUIEntity.h"
#include "TResourceManager.h"

//-------------------------------------------------------------------------------
TUIGroup* TUIGroup::Acquire(const char* id)
{
    TString filename = TString::Format("Assets/Data/UI/%s.xml", id);

    return (TUIGroup*)TResourceManager::Get()->Allocate(ResourceType_UIGroup, filename.GetPointer());
}

//-------------------------------------------------------------------------------
void TUIGroup::Release(TUIGroup* group)
{
    TResourceManager::Get()->Release(ResourceType_UIGroup, group);
}

//-------------------------------------------------------------------------------
void TUIGroup::Unload(TRefCountedObject* toDelete)
{
    TUIGroup* group = static_cast<TUIGroup*>(toDelete);

    TSafeDelete(group);
}

//-------------------------------------------------------------------------------
TRefCountedObject* TUIGroup::Load(const char* filename)
{
	TUIGroup* result = TNew TUIGroup();

	TXMLReader reader(filename, *result->m_entity);

	if (reader.WasError())
	{
		TSafeDelete(result);
		TASSERT(false, "[TUIGroup::Load] Failed to load UI Group");
	}

    return result;
}

//-------------------------------------------------------------------------------
TUIGroup::TUIGroup()
{
    m_entity = TNew TUIEntity();
}

//-------------------------------------------------------------------------------
TUIGroup::~TUIGroup()
{
    TSafeDelete(m_entity);
}
