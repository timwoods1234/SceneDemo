#ifndef __TUIENTITY_H__
#define __TUIENTITY_H__

#ifndef __TENTITY_H__
#include "TEntity.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TUIEntity : public TEntity
{
public:
	TUIEntity();
	virtual ~TUIEntity();

	const TString& GetName() const;

	void SetVariableIndex(unsigned int index);
	unsigned int GetVariableIndex() const;

	float GetRenderDepth() const;

	TUIEntity* GetChild(const TString& name);

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);

protected:
	TString m_name;

	float m_uiDepth;

	// TODO: make this a plugin, return plugin names (IDs) from the plugin not the definition
	// TUIEntity can be eliminated then
	unsigned int m_variableIndex;

	TDynamicSet<TUIEntity*> m_children;
};

#endif
