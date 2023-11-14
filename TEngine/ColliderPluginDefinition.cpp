#include "ColliderPluginDefinition.h"
#include "ColliderPlugin.h"
#include "TPluginRegister.h"

//-------------------------------------------------------------------------------
RegisterPluginType("Collider", ColliderPluginDefinition, ColliderPlugin);

//-------------------------------------------------------------------------------
ColliderPluginDefinition::ColliderPluginDefinition()
:	m_radius(0.f)
{
	m_name = "Collider";
}

//-------------------------------------------------------------------------------
void ColliderPluginDefinition::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_radius = TDataVariant::Find("radius", objects).GetFloat();
}

//-------------------------------------------------------------------------------
float ColliderPluginDefinition::GetRadius() const
{
	return m_radius;
}
