#include "TEventUpdate.h"

//-------------------------------------------------------------------------------
DefineSingleton(TEventUpdate);

//-------------------------------------------------------------------------------
TEventUpdate::TEventUpdate()
{
}

//-------------------------------------------------------------------------------
TEventUpdate::~TEventUpdate()
{
	TASSERT( (m_listeners.GetSize() == 0), "[TEventUpdate] Event still has listeners!");
}