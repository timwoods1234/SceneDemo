#ifndef __TEVENTUIUPDATE_H__
#define __TEVENTUIUPDATE_H__

// update event for the UI
// which separate from game update
// so the UI can update while the game is paused

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TEVENT_H__
#include "TEvent.h"
#endif

#ifndef __TERROR_H__
#include "TError.h"
#endif

class TEventUIUpdate:	public TEvent,
						public TSingleton<TEventUIUpdate>
{
public:
	TEventUIUpdate()
	{
	}

	~TEventUIUpdate()
	{
		TASSERT( (m_listeners.GetSize() == 0), "[TEventUIUpdate] Event still has listeners!");
	}
};

DefineSingleton(TEventUIUpdate);

#endif
