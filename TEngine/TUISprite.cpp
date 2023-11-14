#include "TUISprite.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TEntity.h"
#include "TTexture.h"
#include "TAtlasManager.h"
#include "TAtlasEntry.h"
#include "TUIScene.h"
#include "TUIMappingContainer.h"
#include "TUIEntity.h"

//-------------------------------------------------------------------------------
TUISprite::TUISprite(TEntity* entity, TPluginDefinition* definition)
:	TRenderableInterface(entity, definition),
	m_renderOffset(0,0),
	m_renderSize(0,0),
	m_texture(NULL),
	m_spriteMapping(NULL)
{
}

//-------------------------------------------------------------------------------
TUISprite::~TUISprite()
{
	TUIScene::Get()->RemoveEntry(this);

	TTexture::Release(m_texture);
}

//-------------------------------------------------------------------------------
void TUISprite::OnRender()
{
	if (m_spriteMapping != NULL)
	{
		m_variableParameter.intValue = static_cast<TUIEntity*>(m_entity)->GetVariableIndex();

		m_spriteMapping->Execute(&m_variableParameter, &m_variableResult);

		TString currentSprite = m_variableResult.stringValue;

		if (currentSprite != m_previousSprite)
		{
			const TAtlasEntry* atlasEntry = TAtlasManager::Get()->GetEntry(currentSprite);

			if (atlasEntry != NULL)
			{
				TTexture::Release(m_texture);

				m_texture = TTexture::Acquire(atlasEntry->GetTexturePage().GetPointer());

				m_textureCoords = atlasEntry->GetTextureCoords();
			}

			m_previousSprite = currentSprite;
		}
	}

	TVector2 renderPosition;

	renderPosition.x = m_entity->GetPosition().x + m_renderOffset.x;
	renderPosition.y = m_entity->GetPosition().y + m_renderOffset.y;

	TLocator::GetRenderer()->Draw2D(m_texture, renderPosition, m_textureCoords, 0.f, m_renderSize.x, m_renderSize.y);
}

//-------------------------------------------------------------------------------
void TUISprite::OnEnabled()
{
	TUIScene::Get()->AddEntry(this);
}

//-------------------------------------------------------------------------------
void TUISprite::OnDisabled()
{
	TUIScene::Get()->RemoveEntry(this);
}

//-------------------------------------------------------------------------------
void TUISprite::FinaliseLoad()
{
    if (!m_mappingObject.IsEmpty() && !m_mappingFunction.IsEmpty())
    {
        m_spriteMapping = TUIMappingContainer::Get()->GetMapping(m_mappingObject, m_mappingFunction);

        if (m_spriteMapping == NULL)
        {
            TDebugPrint(("[TUISprite::FinaliseLoad] Failed to find UI mapping (%s, %s)", m_mappingObject.GetPointer(), m_mappingFunction.GetPointer()));
        }
    }

	TUIScene::Get()->AddEntry(this);
}

//-------------------------------------------------------------------------------
void TUISprite::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	TString textureName = TString::Format("Assets/UI/%s.png", TDataVariant::Find("texture", objects).GetString());

	int width = TDataVariant::Find("width", objects).GetInt();
	int height = TDataVariant::Find("height", objects).GetInt();
	m_renderSize.Set((float)width, (float)height);

	const TAtlasEntry* atlasEntry = TAtlasManager::Get()->GetEntry(textureName);

	if (atlasEntry != NULL)
	{
		m_texture = TTexture::Acquire(atlasEntry->GetTexturePage().GetPointer());
		m_textureCoords = atlasEntry->GetTextureCoords();

		if (width == 0 || height == 0)
		{
			m_renderSize = atlasEntry->GetSize();
		}
	}
    else
    {
		m_texture = TTexture::Acquire(textureName.GetPointer());

        if (m_texture != NULL)
        {
            m_renderSize.Set((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
        }

        m_textureCoords.Set(0, 0, 1, 1);
    }

	m_renderOffset.x = TDataVariant::Find("offsetX", objects).GetFloat();
	m_renderOffset.y = TDataVariant::Find("offsetY", objects).GetFloat();
	
	m_mappingObject = TDataVariant::Find("UIMapping", objects).GetString();
	m_mappingFunction = TDataVariant::Find("UISpriteMapping", objects).GetString();
}
