#include "TRenderableInterface.h"

//-------------------------------------------------------------------------------
TRenderableInterface::TRenderableInterface(TEntity* entity, TPluginDefinition* definition)
:	TPlugin(entity, definition)
{
}

//-------------------------------------------------------------------------------
TRenderableInterface::~TRenderableInterface()
{
}

//-------------------------------------------------------------------------------
void TRenderableInterface::ComputeBounds(TAABB& bounds)
{
}
