#include "TEventRender.h"
#include "TError.h"
#include "TLocator.h"
#include "TRendererInterface.h"

//-------------------------------------------------------------------------------
DefineSingleton(TEventRender);

//-------------------------------------------------------------------------------
TEventRender::TEventRender()
{
}

//-------------------------------------------------------------------------------
TEventRender::~TEventRender()
{
	TASSERT( (m_listeners.GetSize() == 0), "[TEventRender] Event still has listeners!");
}

//-------------------------------------------------------------------------------
void TEventRender::Execute()
{
	TEvent::Execute();
}