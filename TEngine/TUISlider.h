#ifndef __TUISLIDER_H__
#define __TUISLIDER_H__

// TODO: add horizontal/vertical toggle

#ifndef __TRENDERABLEINTERFACE_H__
#include "TRenderableInterface.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

#ifndef __TTEXTURE_H__
#include "TTexture.h"
#endif

#ifndef __TUIVARIABLEPARAMETER_H__
#include "TUIVariableParameter.h"
#endif

#ifndef __TUIVARIABLERESULT_H__
#include "TUIVariableResult.h"
#endif

class TSprite;
class TUIMapping;
class TTexture;

class TUISlider : public TRenderableInterface,
				  public TEventListener
{
public:
	TUISlider(TEntity* entity, TPluginDefinition* definition);
	~TUISlider();

	void OnRender();
	void OnUpdate();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();

	float GetRelativeValue() const;

private:
	TString m_mappingObject;
	TString m_callbackName;
	TString m_valueName;

	TUIMapping* m_callback;
	TUIMapping* m_valueMapping;

	TVector2 m_size;
	TVector2 m_buttonSize;

	TUIVariableParameter m_variableParameter;
	TUIVariableResult m_variableResult;

	TTexture* m_buttonTexture;
	TVector4 m_textureCoords;

	float m_clampedPosition;
	float m_relativeValue;
};

#endif
