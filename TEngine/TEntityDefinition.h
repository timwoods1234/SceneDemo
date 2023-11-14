#ifndef __TENTITYDEFINITION_H__
#define __TENTITYDEFINITION_H__

// Container for plugin definitions

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

class TPluginDefinition;
class TEntity;

class TEntityDefinition : public TXMLObject,
						  public TRefCountedObject
{
public:
	static TEntityDefinition* Acquire(const char* id);
	static void Release(TEntityDefinition* definition);
	static void AcquireFolder(const char* filename, TDynamicSet<TEntityDefinition*>& results);

	TEntityDefinition();
	~TEntityDefinition();

	void AddPluginDefinition(TPluginDefinition* definition);
	bool HasPlugin(const TString& pluginName) const;

	const TString& GetName() const;

	TPluginDefinition* GetPluginDefinition(const TString& name) const;
	
	void CreatePlugins(TEntity* entity);

	TXMLObject*		HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);
	void			HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void			FinaliseLoad();
	void			Write(TXMLWriter& writer);

private:
	friend class TResourceManager;
	static TRefCountedObject* Load(const char* filename);
	static void Unload(TRefCountedObject* toUnload);

	TString m_name;

	TDynamicSet<class TPluginDefinition*> m_pluginDefinitions;
};

#endif