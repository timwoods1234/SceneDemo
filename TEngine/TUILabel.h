#ifndef __TUILABEL_H__
#define __TUILABEL_H__

#ifndef __TRENDERABLEINTERFACE_H__
#include "TRenderableInterface.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TUIVARIABLEPARAMETER_H__
#include "TUIVariableParameter.h"
#endif

#ifndef __TUIVARIABLERESULT_H__
#include "TUIVariableResult.h"
#endif

class TUIMapping;
class TFont;

class TUILabel : public TRenderableInterface
{
public:
	TUILabel(TEntity* entity, TPluginDefinition* definition);
	~TUILabel();

	void OnRender();
	void OnEnabled();
	void OnDisabled();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();

private:
	TString m_mappingObject;
	TString m_mappingFunction;
	TUIMapping* m_textMapping;

	TFont* m_font;
	TString m_text;

	TVector2 m_renderOffset;
	TVector2 m_renderPosition;

	TUIVariableParameter m_variableParameter;
	TUIVariableResult m_variableResult;
};

#endif
