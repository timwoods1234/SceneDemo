#include "TUISlider.h"
#include "TUIMappingContainer.h"
#include "TUIMapping.h"
#include "TCursorManager.h"
#include "TEventUIUpdate.h"
#include "TUIEntity.h"
#include "TMath.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TTexture.h"
#include "TAtlasManager.h"
#include "TAtlasEntry.h"
#include "TUIScene.h"

//-------------------------------------------------------------------------------
TUISlider::TUISlider(TEntity* entity, TPluginDefinition* definition)
:	TRenderableInterface(entity, definition),
	m_clampedPosition(1.f),
	m_callback(NULL),
	m_valueMapping(NULL),
	m_size(0, 0),
	m_relativeValue(0.f),
	m_buttonTexture(NULL),
	m_buttonSize(32, 32)
{
	TEventUIUpdate::Get()->Register(this, &TUISlider::OnUpdate);
}

//-------------------------------------------------------------------------------
TUISlider::~TUISlider()
{
	TEventUIUpdate::Get()->Unregister(this, &TUISlider::OnUpdate);

	TUIScene::Get()->RemoveEntry(this);

	TTexture::Release(m_buttonTexture);
}

//-------------------------------------------------------------------------------
void TUISlider::OnRender()
{
	float fValue = m_relativeValue;

	if (m_valueMapping != NULL)
	{
		m_variableParameter.intValue = static_cast<TUIEntity*>(m_entity)->GetVariableIndex();

		m_valueMapping->Execute(&m_variableParameter, &m_variableResult);

		fValue = m_variableResult.floatValue;
	}

	TVector2 renderPosition(m_size.x * fValue, 0.f);
	renderPosition.x = TClamp(renderPosition.x, 0.f, m_clampedPosition);

	renderPosition.x += m_entity->GetPosition().x;
	renderPosition.y += m_entity->GetPosition().y;

	TLocator::GetRenderer()->Draw2D(m_buttonTexture, renderPosition, m_textureCoords, 0.f, m_buttonSize.x, m_buttonSize.y);
}

//-------------------------------------------------------------------------------
void TUISlider::OnUpdate()
{
	for (unsigned int index = 0; index < TCursorManager::Get()->GetNumCursors(); ++index)
	{
		TCursorEntry currentEntry = TCursorManager::Get()->GetCursorEntry(index);

		if (currentEntry.position.x >= m_entity->GetPosition().x &&
			currentEntry.position.x < m_entity->GetPosition().x + m_size.x &&
			currentEntry.position.y >= m_entity->GetPosition().y && 
			currentEntry.position.y < m_entity->GetPosition().y + m_size.y)
		{
			m_relativeValue = (currentEntry.position.x - m_entity->GetPosition().x) / m_size.x;
			m_relativeValue = TClamp(m_relativeValue, 0.f, 1.f);

			if (m_relativeValue < 0.05f)
			{
				m_relativeValue = 0.f;
			}
			else if (m_relativeValue > 0.95f)
			{
				m_relativeValue = 1.f;
			}

			if (m_callback != NULL)
			{
				m_variableParameter.intValue = static_cast<TUIEntity*>(m_entity)->GetVariableIndex();
				m_variableParameter.floatValue = m_relativeValue;

				m_callback->Execute(&m_variableParameter, &m_variableResult);
			}
		}
	}
}

//-------------------------------------------------------------------------------
float TUISlider::GetRelativeValue() const
{
	return m_relativeValue;
}

//-------------------------------------------------------------------------------
void TUISlider::FinaliseLoad()
{
	if (!m_mappingObject.IsEmpty())
	{
		if (!m_callbackName.IsEmpty())
		{
			m_callback = TUIMappingContainer::Get()->GetMapping(m_mappingObject, m_callbackName);

			if (m_callback == NULL)
			{
				TDebugPrint(("[TUISlider::FinaliseLoad] Failed to find UI callback (%s, %s)", m_mappingObject.GetPointer(), m_callbackName.GetPointer()));
			}
		}

		if (!m_valueName.IsEmpty())
		{
			m_valueMapping = TUIMappingContainer::Get()->GetMapping(m_mappingObject, m_valueName);

			if (m_valueMapping == NULL)
			{
				TDebugPrint(("[TUISlider::FinaliseLoad] Failed to find UI value (%s, %s)", m_mappingObject.GetPointer(), m_valueName.GetPointer()));
			}
		}
	}

	TUIScene::Get()->AddEntry(this);
}

//-------------------------------------------------------------------------------
void TUISlider::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_mappingObject = TDataVariant::Find("UIMapping", objects).GetString();
	m_callbackName = TDataVariant::Find("UICallback", objects).GetString();
	m_valueName = TDataVariant::Find("UIValue", objects).GetString();

	float x = TDataVariant::Find("width", objects).GetFloat();
	float y = TDataVariant::Find("height", objects).GetFloat();
	m_size.Set(x, y);

	TString textureName = TString::Format("Assets/UI/%s.png", TDataVariant::Find("button", objects).GetString());
	
	const TAtlasEntry* atlasEntry = TAtlasManager::Get()->GetEntry(textureName);

	if (atlasEntry != NULL)
	{
		m_buttonTexture = TTexture::Acquire(atlasEntry->GetTexturePage().GetPointer());
		m_textureCoords = atlasEntry->GetTextureCoords();

		m_buttonSize = atlasEntry->GetSize();

		m_clampedPosition = m_size.x - m_buttonSize.x;
	}
	else
	{
		m_buttonTexture = TTexture::Acquire(textureName.GetPointer());

        if (m_buttonTexture != NULL)
        {
            m_buttonSize.Set((float)m_buttonTexture->GetWidth(), (float)m_buttonTexture->GetHeight());
        }

        m_textureCoords.Set(0, 0, 1, 1);

		m_clampedPosition = m_size.x;
	}
}
