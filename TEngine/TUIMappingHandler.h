#ifndef __TUIMAPPINGHANDLER_H__
#define __TUIMAPPINGHANDLER_H__

#ifndef __TUIMAPPING_H__
#include "TUIMapping.h"
#endif

template <class Type>
class TUIMappingHandler : public TUIMapping
{
public:
	typedef void (Type::*TUIMappingFunction)(const TUIVariableParameter* parameters, TUIVariableResult* result);

	~TUIMappingHandler();

	inline void SetupMapping(TUIController* receiver, TUIMappingFunction mapping);

	inline void Execute(const TUIVariableParameter* parameters, TUIVariableResult* result);

protected:
	TUIMappingFunction m_mappingFunction;
};

#include "TUIMappingHandler.inl"

#endif
