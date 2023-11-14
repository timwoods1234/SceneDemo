#include "TError.h"
#include "TMemory.h"
#include "TXMLWriter.h"
#include "TEntity.h"
#include "TEntityDefinition.h"
#include "TPlugin.h"
#include "TPluginDefinition.h"
#include "TPluginRegister.h"

//-------------------------------------------------------------------------------
const TString s_definitionID = "EntityDefinitionID";

//-------------------------------------------------------------------------------
TEntity::TEntity()
:	m_definition(NULL),
	m_position(0,0,0),
	m_rotation(0,0,0),
	m_scale(1,1,1),
	m_active(true)
{
}

//-------------------------------------------------------------------------------
TEntity::~TEntity()
{
	for (unsigned int index = 0; index < m_plugins.GetSize(); ++index)
	{
		TSafeDelete(m_plugins[index]);
	}

	if (m_definition != NULL)
	{
		TEntityDefinition::Release(m_definition);

		m_definition = NULL;
	}
}

//-------------------------------------------------------------------------------
TEntity::TEntity(TEntityDefinition *definition)
:	m_definition(definition),
	m_position(0,0,0),
	m_rotation(0,0,0),
	m_scale(1,1,1),
	m_active(true)
{
	if (definition != NULL)
	{
		definition->CreatePlugins(this);

		definition->AddRef();
	}
}

//-------------------------------------------------------------------------------
TEntityDefinition* TEntity::GetDefinition() const
{
	return m_definition;
}

//-------------------------------------------------------------------------------
TPlugin* TEntity::AddPlugin(const TString &name, TPluginDefinition *definition)
{
	TPlugin* result = NULL;

	// does it already exist?
	result = GetPlugin(name);

	if (result != NULL)
	{
		return result;
	}

	if (definition != NULL)
	{
		result = TPluginRegister::Get()->CreatePlugin(name.GetPointer(), this, definition);
	}
	else
	{
		// see if our definition can be used
		definition = m_definition->GetPluginDefinition(name);

		if (definition != NULL)
		{
			result = TPluginRegister::Get()->CreatePlugin(name.GetPointer(), this, definition);
		}
		else
		{
			TDebugPrint(("[TEntity::AddPlugin] There is no definition for %s", name.GetPointer()));
		}
	}

	if (result != NULL)
	{
		m_plugins.Add(result);
	}

	return result;
}

//-------------------------------------------------------------------------------
TPlugin* TEntity::GetPlugin(const TString &strName) const
{
	for (unsigned int index = 0; index < m_plugins.GetSize(); ++index)
	{
		if (strName == m_plugins[index]->GetDefinition()->GetName())
		{
			return m_plugins[index];
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
bool TEntity::IsActive() const
{
	return m_active;
}

//-------------------------------------------------------------------------------
void TEntity::SetActive(bool active)
{
	if (m_active != active)
	{
		for (unsigned int pluginIndex = 0; pluginIndex < m_plugins.GetSize(); pluginIndex++)
		{
			m_plugins[pluginIndex]->SetEnabled(active);
		}

		m_active = active;
	}
}

//-------------------------------------------------------------------------------
const TVector3& TEntity::GetPosition() const
{
	return m_position;
}

//-------------------------------------------------------------------------------
void TEntity::SetPosition(const TVector3& position)
{
	m_position = position;
}

//-------------------------------------------------------------------------------
const TVector3& TEntity::GetScale() const
{
	return m_scale;
}

//-------------------------------------------------------------------------------
void TEntity::SetScale(const TVector3& scale)
{
	m_scale = scale;
}

//-------------------------------------------------------------------------------
const TVector3& TEntity::GetRotation() const
{
	return m_rotation;
}

//-------------------------------------------------------------------------------
void TEntity::SetRotation(const TVector3& rotation)
{
	m_rotation = rotation;
}

//-------------------------------------------------------------------------------
TXMLObject* TEntity::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	for (unsigned int i = 0; i < m_plugins.GetSize(); ++i)
	{
		if (m_plugins[i]->GetDefinition()->GetName() == strID)
		{
			return m_plugins[i];
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TEntity::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_position.x = TDataVariant::Find("x", objects).GetFloat();
	m_position.y = TDataVariant::Find("y", objects).GetFloat();
	m_position.z = TDataVariant::Find("z", objects).GetFloat();

	m_rotation.x = TDataVariant::Find("rotX", objects).GetFloat();
	m_rotation.y = TDataVariant::Find("rotY", objects).GetFloat();
	m_rotation.z = TDataVariant::Find("rotZ", objects).GetFloat(); 

	m_scale.x = TDataVariant::Find("scaleX", objects).GetFloat(1.f);
	m_scale.y = TDataVariant::Find("scaleY", objects).GetFloat(1.f);
	m_scale.z = TDataVariant::Find("scaleZ", objects).GetFloat(1.f);
}

//-------------------------------------------------------------------------------
void TEntity::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TEntity::Write(TXMLWriter& writer)
{
	if (m_definition != NULL)
	{
		writer.WriteAttribute(s_definitionID, m_definition->GetName().GetPointer());
	}

	writer.WriteAttribute("x", m_position.x);
	writer.WriteAttribute("y", m_position.y);
	writer.WriteAttribute("z", m_position.z);

	writer.WriteAttribute("rotX", m_rotation.x);
	writer.WriteAttribute("rotY", m_rotation.y);
	writer.WriteAttribute("rotZ", m_rotation.z);

	for (unsigned int i = 0; i < m_plugins.GetSize(); ++i)
	{
		writer.WriteElement(m_plugins[i]->GetDefinition()->GetName(), *m_plugins[i]);
	}
}
