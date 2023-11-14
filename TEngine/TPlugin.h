#ifndef __TPLUGIN_H__
#define __TPLUGIN_H__

// Base class for a plugin (or component)
// A plugin can be attached to an entity

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

class TEntity;
class TPluginDefinition;

class TPlugin : public TXMLObject
{
public:
	TPlugin(TEntity* entity, TPluginDefinition* definition);

	virtual ~TPlugin();

	TEntity* GetEntity() const;
	TPluginDefinition* GetDefinition() const;

	virtual void SetEnabled(bool enabled);
	virtual bool IsEnabled() const;
	virtual void OnEnabled();
	virtual void OnDisabled();

	virtual TXMLObject*		HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
	{
		return NULL;
	}
	virtual void			HandleLoadAttributes(TDynamicSet<TDataVariant>& objects) {}
	virtual void			FinaliseLoad() {}
	virtual void			Write(TXMLWriter& writer) {}

protected:
	TPluginDefinition* m_definition;
	TEntity* m_entity;
	bool m_enabled;
};

#endif