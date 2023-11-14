#ifndef __COLLIDERPLUGIN_H__
#define __COLLIDERPLUGIN_H__

// Spherical collision bounds
// Attach to the event to be notified when this object collides

#ifndef __TPLUGIN_H__
#include "TPlugin.h"
#endif

#ifndef __ColliderPluginDEFINITION_H__
#include "ColliderPluginDefinition.h"
#endif

#ifndef __TEVENTPARAM_H__
#include "TEventParam.h"
#endif

class ColliderPlugin : public TPlugin
{
public:
	static void Register();

	ColliderPlugin(TEntity* entity, TPluginDefinition* definition);

	~ColliderPlugin();

	bool Collides(const ColliderPlugin& other);

	// TODO: should probably use AddListener/RemoveListener instead of exposing this
	// not like anything should want to clear() it, etc
	TEventParam<ColliderPlugin&>& GetCollisionEvent() const;

private:
	TEventParam<ColliderPlugin&>* m_collisionEvent;
};

#endif
