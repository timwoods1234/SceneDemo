#include "SpritePluginDefinition.h"
#include "SpritePlugin.h"
#include "TPluginRegister.h"

//-------------------------------------------------------------------------------
RegisterPluginType("Sprite", SpritePluginDefinition, SpritePlugin);

//-------------------------------------------------------------------------------
SpritePluginDefinition::SpritePluginDefinition()
:	m_renderOffset(0, 0)
{
	m_name = "Sprite";
}

//-------------------------------------------------------------------------------
void SpritePluginDefinition::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_filename = TDataVariant::Find("filename", objects).GetString();

	float offsetX = TDataVariant::Find("offsetX", objects).GetFloat();
	float offsetY = TDataVariant::Find("offsetY", objects).GetFloat();

	m_renderOffset.Set(offsetX, offsetY);
}

//-------------------------------------------------------------------------------
const TString& SpritePluginDefinition::GetFilename() const
{
	return m_filename;
}

//-------------------------------------------------------------------------------
const TVector2& SpritePluginDefinition::GetRenderOffset() const
{
	return m_renderOffset;
}
