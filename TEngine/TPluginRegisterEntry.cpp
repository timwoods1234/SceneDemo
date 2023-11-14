#include "TPluginRegisterEntry.h"

//-------------------------------------------------------------------------------
TPluginRegisterEntry::TPluginRegisterEntry(const char* typeName, 
										   CreatePluginDefinitionFunction definitionCallback, 
										   CreatePluginFunction instanceCallback)
{
	m_typeName = typeName;

	m_createDefinitionFunction = definitionCallback;

	m_createPluginFunction = instanceCallback;
}

//-------------------------------------------------------------------------------
TPluginRegisterEntry::~TPluginRegisterEntry()
{
}

//-------------------------------------------------------------------------------
const TString& TPluginRegisterEntry::GetTypeName() const
{
	return m_typeName;
}

//-------------------------------------------------------------------------------
CreatePluginDefinitionFunction TPluginRegisterEntry::GetDefinitionFunction() const
{
	return m_createDefinitionFunction;
}

//-------------------------------------------------------------------------------
CreatePluginFunction TPluginRegisterEntry::GetInstanceFunction() const
{
	return m_createPluginFunction;
}