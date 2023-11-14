#ifndef __TUISTATEVISIBILITY_H__
#define __TUISTATEVISIBILITY_H__

#ifndef __TPLUGIN_H__
#include "TPlugin.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TUIMAPPING_H__
#include "TUIMapping.h"
#endif

#ifndef __TUIVARIABLEPARAMETER_H__
#include "TUIVariableParameter.h"
#endif

#ifndef __TUIVARIABLERESULT_H__
#include "TUIVariableResult.h"
#endif

class TUIStateVisibility : public TPlugin,
						  public TEventListener
{
public:
	TUIStateVisibility(TEntity* entity, TPluginDefinition* definition);
	~TUIStateVisibility();

	void Update();

	void OnEnabled();
	void OnDisabled();

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();
	void Write(TXMLWriter& writer);

private:
	struct TUIVisibilityToggle
	{
		TString strTarget;
		bool bVisible;
	};

	void ToggleVisibility();

	TDynamicSet<TUIVisibilityToggle> m_visibilityToggles;

	TString m_mappingObject;
	TString m_mappingFunction;
	TUIMapping* m_stateMapping;

	TUIVariableParameter m_variableParameter;
	TUIVariableResult m_variableResult;

	TString m_currentState;
	TString m_activeState;
};

#endif
