#include "TPluginRegister.h"

//-------------------------------------------------------------------------------
DefineSingleton(TPluginRegister);

//-------------------------------------------------------------------------------
TPluginRegister::TPluginRegister()
{
}

//-------------------------------------------------------------------------------
TPluginRegister::~TPluginRegister()
{
	unsigned int numEntries = m_registerEntries.GetSize();

	for (unsigned int index = 0; index < numEntries; index++)
	{
		TSafeDelete(m_registerEntries[index]);
	}
}

//-------------------------------------------------------------------------------
void TPluginRegister::Register(const char* typeName, CreatePluginDefinitionFunction definitionCallback, CreatePluginFunction instanceCallback)
{
	TPluginRegisterEntry* entry = TNew TPluginRegisterEntry(typeName, definitionCallback, instanceCallback);

	m_registerEntries.Add(entry);
}

//-------------------------------------------------------------------------------
TPluginDefinition* TPluginRegister::CreateDefinition(const char* typeName)
{
	TString id = typeName;

	unsigned int numEntries = m_registerEntries.GetSize();

	for (unsigned int index = 0; index < numEntries; index++)
	{
		if (id == m_registerEntries[index]->GetTypeName())
		{
			return (m_registerEntries[index]->GetDefinitionFunction())();
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
TPlugin* TPluginRegister::CreatePlugin(const char* typeName, TEntity* entity, TPluginDefinition* definition)
{
	TString id = typeName;

	unsigned int numEntries = m_registerEntries.GetSize();

	for (unsigned int index = 0; index < numEntries; index++)
	{
		if (id == m_registerEntries[index]->GetTypeName())
		{
			return (m_registerEntries[index]->GetInstanceFunction())(entity, definition);
		}
	}

	return NULL;
}