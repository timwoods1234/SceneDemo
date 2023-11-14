#ifndef __TEVENTUIRENDER_H__
#define __TEVENTUIRENDER_H__

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TEVENT_H__
#include "TEvent.h"
#endif

class TEventUIRender: public TEvent,
					  public TSingleton<TEventUIRender>
{
public:
	TEventUIRender();

	~TEventUIRender();

	void Execute();
};

#endif
