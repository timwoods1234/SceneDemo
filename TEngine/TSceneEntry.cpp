#include "TSceneEntry.h"
#include "ColliderPlugin.h"
#include "TRenderableInterface.h"
#include "TEntity.h"

//-------------------------------------------------------------------------------
static const TString s_colliderID = "Collider";

//-------------------------------------------------------------------------------
TSceneEntry::TSceneEntry(TRenderableInterface* renderable)
{
	m_renderable = renderable;

	TEntity* entity = renderable->GetEntity();

	if (entity != NULL)
	{
		m_collider = static_cast<ColliderPlugin*>(entity->GetPlugin(s_colliderID));
	}
}

//-------------------------------------------------------------------------------
TSceneEntry::~TSceneEntry()
{
}

//-------------------------------------------------------------------------------
TRenderableInterface* TSceneEntry::GetRenderable() const
{
	return m_renderable;
}

//-------------------------------------------------------------------------------
ColliderPlugin* TSceneEntry::GetCollider() const
{
	return m_collider;
}
