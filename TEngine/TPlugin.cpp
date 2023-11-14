#include "TPlugin.h"

//-------------------------------------------------------------------------------
TPlugin::TPlugin(TEntity* entity, TPluginDefinition* definition)
:	m_enabled(true)
{
	m_definition = definition;
	m_entity = entity;
}

//-------------------------------------------------------------------------------
TPlugin::~TPlugin()
{
	m_entity = NULL;
	m_definition = NULL;
}

//-------------------------------------------------------------------------------
TPluginDefinition* TPlugin::GetDefinition() const
{
	return m_definition;
}

//-------------------------------------------------------------------------------
TEntity* TPlugin::GetEntity() const
{
	return m_entity;
}

//-------------------------------------------------------------------------------
void TPlugin::SetEnabled(bool enabled)
{
	if (m_enabled != enabled)
	{
		m_enabled = enabled;

		if (enabled)
		{
			OnEnabled();
		}
		else
		{
			OnDisabled();
		}
	}
}
//-------------------------------------------------------------------------------
void TPlugin::OnEnabled()
{
}

//-------------------------------------------------------------------------------
void TPlugin::OnDisabled()
{
}

//-------------------------------------------------------------------------------
bool TPlugin::IsEnabled() const
{
	return m_enabled;
}
