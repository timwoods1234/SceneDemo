#ifndef __TENTITY_H__
#define __TENTITY_H__

// Container for plugin instances

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

class TEntityDefinition;
class TPlugin;
class TPluginDefinition;

class TEntity : public TXMLObject
{
public:
	TEntity();
	TEntity(TEntityDefinition* definition);
	
	virtual ~TEntity();

	TEntityDefinition* GetDefinition() const;

	TPlugin* AddPlugin(const TString& name, TPluginDefinition* definition);
	TPlugin* GetPlugin(const TString& strName) const;

	const TVector3& GetPosition() const;
	void SetPosition(const TVector3& position);

	const TVector3& GetScale() const;
	void SetScale(const TVector3& scale);

	const TVector3& GetRotation() const;
	void SetRotation(const TVector3& rotation);

	bool IsActive() const;
	void SetActive(bool active);

	virtual TXMLObject*	HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);
	virtual void		HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	virtual void		FinaliseLoad();
	void				Write(TXMLWriter& writer);

protected:
	TDynamicSet<TPlugin*> m_plugins;

	TEntityDefinition* m_definition;

	TVector3 m_position;
	TVector3 m_rotation; // TODO: make sprite and sprite plugin use this instead of their old values
	TVector3 m_scale;

	bool m_active;
};

#endif