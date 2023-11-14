#ifndef __COLLIDERPLUGINDEFINITION_H__
#define __COLLIDERPLUGINDEFINITION_H__

#ifndef __TPLUGINDEFINITION_H__
#include "TPluginDefinition.h"
#endif

class ColliderPluginDefinition : public TPluginDefinition
{
public:
	ColliderPluginDefinition();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	float GetRadius() const;

private:
	float m_radius;
};

#endif
