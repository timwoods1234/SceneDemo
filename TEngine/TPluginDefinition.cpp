#include "TPluginDefinition.h"
#include "TXMLWriter.h"

//-------------------------------------------------------------------------------
const TString s_nameId = "Name";

//-------------------------------------------------------------------------------
const TString& TPluginDefinition::GetName() const
{
	return m_name;
}

//-------------------------------------------------------------------------------
TXMLObject* TPluginDefinition::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	return NULL;
}

//-------------------------------------------------------------------------------
void TPluginDefinition::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
}

//-------------------------------------------------------------------------------
void TPluginDefinition::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TPluginDefinition::Write(TXMLWriter& writer)
{
	writer.WriteAttribute(s_nameId, m_name.GetPointer());
}
