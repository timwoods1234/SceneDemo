#ifndef __TPLUGINDEFINITION_H__
#define __TPLUGINDEFINITION_H__

// Holds data for a single type of plugin.
// Can be shared between multiple plugin instances.

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TMEMORY_H__
#include "TMemory.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

class TEntity;
class TPlugin;
class DataLoader;

class TPluginDefinition : public TXMLObject
{
public:
	virtual ~TPluginDefinition() {}

	const TString& GetName() const;

	virtual TXMLObject*		HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);
	virtual void			HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	virtual void			FinaliseLoad();
	virtual void			Write(TXMLWriter& writer);
	
protected:
	TString m_name;
};

#endif