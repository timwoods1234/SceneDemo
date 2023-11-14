#ifndef __TUIBUTTON_H__
#define __TUIBUTTON_H__

#ifndef __TPLUGIN_H__
#include "TPlugin.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TUIVARIABLEPARAMETER_H__
#include "TUIVariableParameter.h"
#endif

class TUIMapping;

class TUIButton :	public TPlugin, 
					public TEventListener
{
public:
	TUIButton(TEntity* entity, TPluginDefinition* definition);
	~TUIButton();

	void OnUpdate();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();

private:
	TString m_mappingObject;
	TString m_mappingFunction;
	TUIMapping* m_callback;

	TUIVariableParameter m_parameter;

	TVector2 m_size;
};

#endif
