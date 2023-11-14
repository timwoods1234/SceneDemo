#include "SpritePlugin.h"
#include "TSprite.h"
#include "TMemory.h"
#include "TLocator.h"
#include "TSceneInterface.h"
#include "TEntity.h"
#include "TShader.h"
#include "TSpriteDefinition.h"

//-------------------------------------------------------------------------------
SpritePlugin::SpritePlugin(TEntity* entity, TPluginDefinition* definition)
:	TRenderableInterface(entity, definition),
	m_renderOffset(0, 0),
	m_rotation(0.0f),
	m_sprite(NULL)
{
	SpritePluginDefinition* spriteDefinition = static_cast<SpritePluginDefinition*>(definition);

	if (spriteDefinition != NULL && !spriteDefinition->GetFilename().IsEmpty())
	{
		TLocator::GetScene()->AddEntry(this);

		m_sprite = TSprite::Load(spriteDefinition->GetFilename().GetPointer());

		m_renderOffset = spriteDefinition->GetRenderOffset();
	}
}

//-------------------------------------------------------------------------------
SpritePlugin::~SpritePlugin()
{
	TLocator::GetScene()->RemoveEntry(this);

	TSprite::Unload(m_sprite);
}

//-------------------------------------------------------------------------------
const TString& SpritePlugin::GetCurrentAnimation() const
{
	return m_sprite->GetCurrentAnimation();
}

//-------------------------------------------------------------------------------
void SpritePlugin::SetAnimation(const TString& animationName)
{
	m_sprite->SetAnimation(animationName);
}

//-------------------------------------------------------------------------------
bool SpritePlugin::IsAnimationPlaying() const
{
	return m_sprite->IsAnimationPlaying();
}

//-------------------------------------------------------------------------------
void SpritePlugin::OnRender()
{
	TVector2 renderPosition;

	renderPosition.x = m_entity->GetPosition().x + m_renderOffset.x;
	renderPosition.y = m_entity->GetPosition().y + m_renderOffset.y;

	m_sprite->Render(renderPosition, m_rotation);
}

//-------------------------------------------------------------------------------
const TVector2& SpritePlugin::GetRenderOffset() const
{
	return m_renderOffset;
}

//-------------------------------------------------------------------------------
void SpritePlugin::SetRenderOffset(const TVector2& offset)
{
	m_renderOffset = offset;
}

//-------------------------------------------------------------------------------
float SpritePlugin::GetRotation() const
{
	return m_rotation;
}

//-------------------------------------------------------------------------------
void SpritePlugin::SetRotation(float rotation)
{
	m_rotation = rotation;
}

//-------------------------------------------------------------------------------
void SpritePlugin::ComputeBounds(TAABB &box)
{
	TDebugPrint(("todo: implement 2D bounds check"));
}
