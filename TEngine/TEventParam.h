#ifndef __TEVENTPARAM_H__
#define __TEVENTPARAM_H__

// Event that takes a single param argument.

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TEVENTPARAMHANDLER_H__
#include "TEventParamHandler.h"
#endif

#ifndef __TMEMORY_H__
#include "TMemory.h"
#endif

template <typename Param>
class TEventParam
{
public:
	TEventParam();
	virtual ~TEventParam();

	inline virtual void Execute(Param data);

	template <class ObjectType>
	inline void		Register(
						ObjectType* object, 
						typename TEventParamHandler<ObjectType, Param>::Handler handler
						);

	template <class ObjectType>
	inline void		Unregister(
						ObjectType* object, 
						typename TEventParamHandler<ObjectType, Param>::Handler handler
						);

	inline void Clear();

protected:
	TDynamicSet< TEventParamHandlerBase<Param>* > m_listeners;
};

#include "TEventParam.inl"

#endif
