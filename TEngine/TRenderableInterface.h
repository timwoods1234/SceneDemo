#ifndef __TRENDERABLEINTERFACE_H__
#define __TRENDERABLEINTERFACE_H__

// base class for sprite/model plugin so that Scene works with both

#ifndef __TPLUGIN_H__
#include "TPlugin.h"
#endif

class TAABB;

class TRenderableInterface : public TPlugin
{
public:
	TRenderableInterface(TEntity* entity, TPluginDefinition* definition);

	virtual ~TRenderableInterface();

	virtual void OnRender() = 0;

	virtual void ComputeBounds(TAABB& bounds);
};

#endif
