#include "TEventUIRender.h"
#include "TLocator.h"
#include "TRendererInterface.h"

//-------------------------------------------------------------------------------
DefineSingleton(TEventUIRender);

//-------------------------------------------------------------------------------
TEventUIRender::TEventUIRender()
{
}

//-------------------------------------------------------------------------------
TEventUIRender::~TEventUIRender()
{
	TASSERT( (m_listeners.GetSize() == 0), "[TEventUIRender] Event still has listeners!");
}

//-------------------------------------------------------------------------------
void TEventUIRender::Execute()
{
	TEvent::Execute();
}