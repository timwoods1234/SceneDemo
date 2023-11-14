#ifndef __TEVENTPARAMHANDLERBASE_H__
#define __TEVENTPARAMHANDLERBASE_H__

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

template <typename Param>
class TEventParamHandlerBase
{
public:
	TEventParamHandlerBase() : m_object(0) {}
	virtual ~TEventParamHandlerBase() {}

	virtual void Execute(Param data) = 0;

	TEventListener*	GetListener() const;
protected:
	TEventListener* m_object;
};

#include "TEventParamHandlerBase.inl"

#endif
