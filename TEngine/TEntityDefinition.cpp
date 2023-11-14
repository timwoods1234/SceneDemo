#include "TMemory.h"
#include "TXMLReader.h"
#include "TEntityDefinition.h"
#include "TEntity.h"
#include "TPluginDefinition.h"
#include "TLocator.h"
#include "TFileSystemInterface.h"
#include "TPluginRegister.h"
#include "TResourceManager.h"

//-------------------------------------------------------------------------------
static const TString s_nameID = "name";

//-------------------------------------------------------------------------------
TEntityDefinition* TEntityDefinition::Acquire(const char* id)
{
	TString filepath = TString::Format("Assets/Data/Entity/%s.xml", id);

	TEntityDefinition* result = (TEntityDefinition*)TResourceManager::Get()->Allocate(ResourceType_EntityDefinition, filepath.GetPointer());

	return result;
}

//-------------------------------------------------------------------------------
void TEntityDefinition::Release(TEntityDefinition* definition)
{
	TResourceManager::Get()->Release(ResourceType_EntityDefinition, definition);
}

//-------------------------------------------------------------------------------
TRefCountedObject* TEntityDefinition::Load(const char* filename)
{
	TEntityDefinition* definition = TNew TEntityDefinition();

	TXMLReader reader(filename, *definition);

	if (reader.WasError())
	{
		TDebugPrint(("[TEntityDefinition::Load] Failed to load %s", filename));

		TSafeDelete(definition);
	}

	return definition;
}

//-------------------------------------------------------------------------------
void TEntityDefinition::Unload(TRefCountedObject* toUnload)
{
	TEntityDefinition* definition = static_cast<TEntityDefinition*>(toUnload);

	TSafeDelete(definition);
}

//-------------------------------------------------------------------------------
void TEntityDefinition::AcquireFolder(const char* filename, TDynamicSet<TEntityDefinition*>& results)
{
	TString fullPath = TString::Format("Assets/Data/Entity/%s", filename);

	TDynamicSet<TString> definitionNames;
	TLocator::GetFileSystem()->GetFileList(fullPath.GetPointer(), "xml", definitionNames);

	unsigned int numDefinitions = definitionNames.GetSize();
	for (unsigned int index = 0; index < numDefinitions; index++)
	{
		TEntityDefinition* definition = (TEntityDefinition*)TResourceManager::Get()->Allocate(ResourceType_EntityDefinition, definitionNames[index].GetPointer());

		if (definition != NULL)
		{
			results.Add(definition);
		}
	}
}

//-------------------------------------------------------------------------------
TEntityDefinition::TEntityDefinition()
{
}

//-------------------------------------------------------------------------------
TEntityDefinition::~TEntityDefinition()
{
	for (unsigned int index = 0; index < m_pluginDefinitions.GetSize(); ++index)
	{
		TSafeDelete(m_pluginDefinitions[index]);
	}
}

//-------------------------------------------------------------------------------
void TEntityDefinition::AddPluginDefinition(TPluginDefinition* definition)
{
	m_pluginDefinitions.Add(definition);
}

//-------------------------------------------------------------------------------
bool TEntityDefinition::HasPlugin(const TString& pluginName) const
{
	for (unsigned int index = 0; index < m_pluginDefinitions.GetSize(); ++index)
	{
		if (pluginName == m_pluginDefinitions[index]->GetName())
		{
			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------------------
const TString& TEntityDefinition::GetName() const
{
	return m_name;
}

//-------------------------------------------------------------------------------
TPluginDefinition* TEntityDefinition::GetPluginDefinition(const TString& name) const
{
	for (unsigned int index = 0; index < m_pluginDefinitions.GetSize(); ++index)
	{
		if (m_pluginDefinitions[index]->GetName() == name)
		{
			return m_pluginDefinitions[index];
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TEntityDefinition::CreatePlugins(TEntity* entity)
{
	for (unsigned int index = 0; index < m_pluginDefinitions.GetSize(); ++index)
	{
		entity->AddPlugin(m_pluginDefinitions[index]->GetName(), m_pluginDefinitions[index]);
	}
}

//-------------------------------------------------------------------------------
TXMLObject* TEntityDefinition::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	TPluginDefinition* definition = TPluginRegister::Get()->CreateDefinition(strID.GetPointer());

	if (definition != NULL)
	{
		AddPluginDefinition(definition);

		return definition;
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TEntityDefinition::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_name = TDataVariant::Find(s_nameID, objects).GetString();
}

//-------------------------------------------------------------------------------
void TEntityDefinition::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TEntityDefinition::Write(TXMLWriter& writer)
{
}
