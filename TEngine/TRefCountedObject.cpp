#include "TRefCountedObject.h"
#include "TError.h"

//-------------------------------------------------------------------------------
TRefCountedObject::TRefCountedObject()
:	m_refCount(0)
{
}

//-------------------------------------------------------------------------------
TRefCountedObject::~TRefCountedObject()
{
	TASSERT((m_refCount == 0), "[TRefCountedObject::~TRefCountedObject] Object is still referenced");
}

//-------------------------------------------------------------------------------
void TRefCountedObject::AddRef()
{
	m_refCount++;
}

//-------------------------------------------------------------------------------
void TRefCountedObject::RemoveRef()
{
	m_refCount--;

	TASSERT((m_refCount >= 0), "[TRefCountedObject::Deallocate] Negative ref count detected");
}

//-------------------------------------------------------------------------------
int TRefCountedObject::GetRefCount() const
{
	return m_refCount;
}

//-------------------------------------------------------------------------------
const TString& TRefCountedObject::GetId() const
{
	return m_id;
}

//-------------------------------------------------------------------------------
void TRefCountedObject::SetId(const char* id)
{
	m_id = id;
}