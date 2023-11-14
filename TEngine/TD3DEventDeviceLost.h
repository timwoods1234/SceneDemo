#ifndef __TD3DDEVICELOST_H__
#define __TD3DDEVICELOST_H__

#ifndef __TEVENT_H__
#include "TEvent.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

class TD3DEventDeviceLost : public TSingleton<TD3DEventDeviceLost>, 
							public TEvent
{
public:

	TD3DEventDeviceLost()
	{
	}

	~TD3DEventDeviceLost()
	{
		TASSERT( (m_listeners.GetSize() == 0), "[TD3DEventDeviceLost] Event still has listeners!");
	}
};

DefineSingleton(TD3DEventDeviceLost);

#endif
