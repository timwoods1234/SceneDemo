#include "Collision.h"
#include "TEntity.h"
#include "ColliderPlugin.h"

//-------------------------------------------------------------------------------
ColliderPlugin::ColliderPlugin(TEntity* entity, TPluginDefinition* definition)
:	TPlugin(entity, definition)
{
	m_collisionEvent = TNew TEventParam<ColliderPlugin&>();
}

//-------------------------------------------------------------------------------
ColliderPlugin::~ColliderPlugin()
{
	TSafeDelete(m_collisionEvent);
}

//-------------------------------------------------------------------------------
bool ColliderPlugin::Collides(const ColliderPlugin& other)
{
	return CollisionAt(
				m_entity->GetPosition(), 
				other.GetEntity()->GetPosition(),
				static_cast<ColliderPluginDefinition*>(m_definition)->GetRadius(),
				static_cast<ColliderPluginDefinition*>(other.GetDefinition())->GetRadius()
				);
}

//-------------------------------------------------------------------------------
TEventParam<ColliderPlugin&>& ColliderPlugin::GetCollisionEvent() const
{
	return *m_collisionEvent;
}
