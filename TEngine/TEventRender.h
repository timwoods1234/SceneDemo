#ifndef __TEVENTRENDER_H__
#define __TEVENTRENDER_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TEVENT_H__
#include "TEvent.h"
#endif

class TEventRender : public TEvent,
					 public TSingleton<TEventRender>
{
public:
	TEventRender();

	~TEventRender();

	void Execute();
};

#endif
