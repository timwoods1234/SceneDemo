#ifndef __TEVENTHANDLERBASE_H__
#define __TEVENTHANDLERBASE_H__

// Wrapper for an event listener

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

class TEventHandlerBase
{
public:
	TEventHandlerBase() : m_object(0) {}
	virtual ~TEventHandlerBase() {}

	virtual void Execute() = 0;

	inline TEventListener* GetListener() const;

protected:
	TEventListener* m_object;
};

#include "TEventHandlerBase.inl"

#endif