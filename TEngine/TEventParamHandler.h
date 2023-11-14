#ifndef __TEVENTPARAMHANDLER_H__
#define __TEVENTPARAMHANDLER_H__

#ifndef __TEVENTPARAMHANDLERBASE_H__
#include "TEventParamHandlerBase.h"
#endif

template <class Type, typename Param>
class TEventParamHandler : public TEventParamHandlerBase<Param>
{
public:
	typedef void (Type::*Handler)(Param data);

	TEventParamHandler() : m_handler(0) {}
	virtual ~TEventParamHandler() {}

	inline void	Setup(TEventListener* object, Handler handler);

	virtual void Execute(Param data);

	inline Handler	GetHandler() const;
protected:
	Handler m_handler;
};

#include "TEventParamHandler.inl"

#endif
