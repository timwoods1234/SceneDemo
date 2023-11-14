#ifndef __TD3DEVENTDEVICERESET_H__
#define __TD3DEVENTDEVICERESET_H__

#ifndef __TEVENT_H__
#include "TEvent.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

class TD3DEventDeviceReset : public TSingleton<TD3DEventDeviceReset>, 
							 public TEvent
{
public:

	TD3DEventDeviceReset()
	{
	}

	~TD3DEventDeviceReset()
	{
		TASSERT( (m_listeners.GetSize() == 0), "[TD3DEventDeviceReset] Event still has listeners!");
	}
};

DefineSingleton(TD3DEventDeviceReset);

#endif
