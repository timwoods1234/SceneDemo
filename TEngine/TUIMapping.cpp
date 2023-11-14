#include "TUIMapping.h"

//-------------------------------------------------------------------------------
TUIMapping::TUIMapping()
:	m_receiver(NULL)
{
}

//-------------------------------------------------------------------------------
TUIMapping::~TUIMapping()
{
}

//-------------------------------------------------------------------------------
const TString& TUIMapping::GetObjectName() const
{
	return m_objectName;
}

//-------------------------------------------------------------------------------
const TString& TUIMapping::GetMappingName() const
{
	return m_mappingName;
}

//-------------------------------------------------------------------------------
void TUIMapping::SetObjectName(const TString& name)
{
	m_objectName = name;
}

//-------------------------------------------------------------------------------
void TUIMapping::SetMappingName(const TString& name)
{
	m_mappingName = name;
}
