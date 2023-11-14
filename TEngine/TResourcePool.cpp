#include "TResourcePool.h"
#include "TRefCountedObject.h"

//-------------------------------------------------------------------------------
TResourcePool::TResourcePool(const char* id, LoadResourceCallback loadFunction, UnloadResourceCallback unloadFunction)
{
	m_id = id;

	m_loadFunction = loadFunction;

	m_unloadFunction = unloadFunction;
}

//-------------------------------------------------------------------------------
TResourcePool::~TResourcePool()
{
	if (m_resources.GetSize() != 0)
	{
		TDebugPrint(("[TResourcePool::~TResourcePool] Resources allocated in resource pool %s", m_id.GetPointer()));
		
		TASSERT(false, "Resources still allocated!");
	}
}

//-------------------------------------------------------------------------------
TRefCountedObject* TResourcePool::Allocate(const char* id)
{
	TRefCountedObject* result = NULL;

	for (unsigned int index = 0; index < m_resources.GetSize(); index++)
	{
		if (m_resources[index]->GetId() == id)
		{
			m_resources[index]->AddRef();

			result = m_resources[index];
		}
	}

	if (result == NULL)
	{
		result = m_loadFunction(id);

		if (result != NULL)
		{
			result->SetId(id);

			result->AddRef();

			m_resources.Add(result);
		}
	}

	return result;
}

//-------------------------------------------------------------------------------
void TResourcePool::Release(TRefCountedObject* resource)
{
	resource->RemoveRef();

	if (resource->GetRefCount() == 0)
	{
        m_resources.Remove(resource);

		m_unloadFunction(resource);

		if (m_resources.GetSize() == 0)
		{
			m_resources.ReleaseMemory();
		}
	}
}