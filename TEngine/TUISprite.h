#ifndef __TUISPRITE_H__
#define __TUISPRITE_H__

#ifndef __TRENDERABLEINTERFACE_H__
#include "TRenderableInterface.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

#ifndef __TUIVARIABLEPARAMETER_H__
#include "TUIVariableParameter.h"
#endif

#ifndef __TUIVARIABLERESULT_H__
#include "TUIVariableResult.h"
#endif

class TUIMapping;
class TTexture;

class TUISprite : public TRenderableInterface
{
public:
	TUISprite(TEntity* entity, TPluginDefinition* definition);
	~TUISprite();

	void OnRender();

	void OnEnabled();
	void OnDisabled();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();

protected:
	TString m_mappingObject;
	TString m_mappingFunction;
	TUIMapping* m_spriteMapping;
	TString m_previousSprite;

	TUIVariableParameter m_variableParameter;
	TUIVariableResult m_variableResult;

	TTexture* m_texture;
	TVector2 m_renderOffset;
	TVector2 m_renderSize;
	TVector4 m_textureCoords;
};

#endif
