#ifndef __TUIMAPPINGCONTAINER_H__
#define __TUIMAPPINGCONTAINER_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TUIMAPPINGHANDLER_H__
#include "TUIMappingHandler.h"
#endif

#ifndef __TMEMORY_H__
#include "TMemory.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

class TUIMappingContainer : public TSingleton<TUIMappingContainer>
{
public:
	~TUIMappingContainer();

	template <class ObjectType>
	inline void		Register(
						const TString& objectName,
						const TString& functionName,
						ObjectType* object,
						typename TUIMappingHandler<ObjectType>::TUIMappingFunction handler
						);

	TUIMapping* GetMapping(const TString& object, const TString& mapping);

	void UnregisterMappings(const TString& object);

private:
	TDynamicSet<TUIMapping*> m_mappings;
};

#include "TUIMappingContainer.inl"

#endif
