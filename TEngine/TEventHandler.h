#ifndef __TEVENTHANDLER_H__
#define __TEVENTHANDLER_H__

// Stores an object/callback pair

#ifndef __TEVENTHANDLERBASE_H__
#include "TEventHandlerBase.h"
#endif

template <class Type>
class TEventHandler : public TEventHandlerBase
{
public:
	typedef void (Type::*Handler)();

	TEventHandler() : m_handler(0) {}
	virtual ~TEventHandler() {}

	inline void	Setup(TEventListener* object, Handler handler);

	virtual void Execute();

	inline Handler	GetHandler() const;

protected:
	Handler m_handler;
};

#include "TEventHandler.inl"

#endif
