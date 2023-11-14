#include "TUIMappingContainer.h"
#include "TUIMappingHandler.h"

//-------------------------------------------------------------------------------
DefineSingleton(TUIMappingContainer);

//-------------------------------------------------------------------------------
TUIMappingContainer::~TUIMappingContainer()
{
	for (unsigned int i=0; i<m_mappings.GetSize(); ++i)
	{
		TSafeDelete(m_mappings[i]);
	}
}

//-------------------------------------------------------------------------------
TUIMapping* TUIMappingContainer::GetMapping(const TString& object, const TString& mapping)
{
	for (unsigned int i=0; i<m_mappings.GetSize(); ++i)
	{
		if (m_mappings[i]->GetObjectName() == object &&
			m_mappings[i]->GetMappingName() == mapping)
		{
			return m_mappings[i];
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TUIMappingContainer::UnregisterMappings(const TString &object)
{
	for (unsigned int i=0; i<m_mappings.GetSize(); ++i)
	{
		if (m_mappings[i]->GetObjectName() == object)
		{
			TSafeDelete(m_mappings[i]);

			m_mappings.RemoveAt(i);

			--i;
		}
	}
}
