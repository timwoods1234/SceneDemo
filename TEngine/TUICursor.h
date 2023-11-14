#ifndef __TUICURSOR_H__
#define __TUICURSOR_H__

#ifndef __TPLUGIN_H__
#include "TPlugin.h"
#endif

#ifndef __TRENDERABLEINTERFACE_H__
#include "TRenderableInterface.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

class TTexture;

class TUICursor : public TRenderableInterface
{
public:
	TUICursor(TEntity* entity, TPluginDefinition* definition);
	~TUICursor();

	void OnRender();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void FinaliseLoad();

private:
	TTexture* m_texture;
	TVector2 m_renderSize;
	TVector4 m_textureCoords;
};

#endif
