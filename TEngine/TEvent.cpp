#include "TEvent.h"

//-------------------------------------------------------------------------------
TEvent::TEvent()
{
}

//-------------------------------------------------------------------------------
TEvent::~TEvent()
{
	Clear();
}

//-------------------------------------------------------------------------------
void TEvent::Clear()
{
	for (unsigned int index = 0; index < m_listeners.GetSize(); ++index)
	{
		TSafeDelete(m_listeners[index]);
	}
}

//-------------------------------------------------------------------------------
void TEvent::Execute()
{
	for (unsigned int index = 0; index < m_listeners.GetSize(); ++index)
	{
		m_listeners[index]->Execute();
	}
}
