#ifndef __TEVENT_H__
#define __TEVENT_H__

// Simple event that has no params

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TEVENTHANDLER_H__
#include "TEventHandler.h"
#endif

#ifndef __TMEMORY_H__
#include "TMemory.h"
#endif

class TEvent
{
public:
	TEvent();
	virtual ~TEvent();

	virtual void Execute();		// send the event to all listeners

	template <class ObjectType>
	inline void		Register(
						ObjectType* object,
						typename TEventHandler<ObjectType>::Handler handler
						);

	template <class ObjectType>
	inline void		Unregister(
						ObjectType* object,
						typename TEventHandler<ObjectType>::Handler handler
						);

	inline void Clear();
protected:
	TDynamicSet<TEventHandlerBase*> m_listeners;
};

#include "TEvent.inl"

#endif //#ifndef __TEVENT_H__
