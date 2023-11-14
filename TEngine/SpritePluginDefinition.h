#ifndef __SPRITEPLUGINDEFINITION_H__
#define __SPRITEPLUGINDEFINITION_H__

#ifndef __TPLUGINDEFINITION_H__
#include "TPluginDefinition.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

class SpritePluginDefinition : public TPluginDefinition
{
public:
	SpritePluginDefinition();

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	const TString& GetFilename() const;
	const TVector2& GetDimensions() const;
	const TVector2& GetRenderOffset() const;

private:
	TString m_filename;
	TVector2 m_dimensions;
	TVector2 m_renderOffset;
};

#endif
