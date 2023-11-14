#include "TUILabel.h"
#include "TLocator.h"
#include "TFont.h"
#include "TUIMapping.h"
#include "TUIMappingContainer.h"
#include "TEntity.h"
#include "TUIEntity.h"
#include "TUIScene.h"

//-------------------------------------------------------------------------------
TUILabel::TUILabel(TEntity* entity, TPluginDefinition* definition)
:	TRenderableInterface(entity, definition),
	m_font(NULL),
	m_textMapping(NULL),
	m_renderPosition(0.f, 0.f)
{
    m_text = TString::GetEmptyString();
}

//-------------------------------------------------------------------------------
TUILabel::~TUILabel()
{
	TUIScene::Get()->RemoveEntry(this);

    TFont::Release(m_font);
}

//-------------------------------------------------------------------------------
void TUILabel::OnEnabled()
{
	TUIScene::Get()->AddEntry(this);
}

//-------------------------------------------------------------------------------
void TUILabel::OnDisabled()
{
	TUIScene::Get()->RemoveEntry(this);
}

//-------------------------------------------------------------------------------
void TUILabel::OnRender()
{
	if (m_textMapping != NULL)
	{
		m_variableParameter.intValue = static_cast<TUIEntity*>(m_entity)->GetVariableIndex();

		m_textMapping->Execute(&m_variableParameter, &m_variableResult);

		m_text = m_variableResult.stringValue;
	}

	m_renderPosition.Set(m_entity->GetPosition().x, m_entity->GetPosition().y);

	m_renderPosition += m_renderOffset;

	m_font->PrintText(m_renderPosition, m_text.GetPointer());
}

//-------------------------------------------------------------------------------
void TUILabel::FinaliseLoad()
{
    if (!m_mappingObject.IsEmpty() && !m_mappingFunction.IsEmpty())
    {
        m_textMapping = TUIMappingContainer::Get()->GetMapping(m_mappingObject, m_mappingFunction);

        if (m_textMapping == NULL)
        {
            TDebugPrint(("[TUILabel::FinaliseLoad] Failed to find UI mapping (%s, %s)", m_mappingObject.GetPointer(), m_mappingFunction.GetPointer()));
        }
    }

	TUIScene::Get()->AddEntry(this);
}

//-------------------------------------------------------------------------------
void TUILabel::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_mappingObject = TDataVariant::Find("UIMapping", objects).GetString();
	m_mappingFunction = TDataVariant::Find("UIStringMapping", objects).GetString();

	m_text = TDataVariant::Find("defaultText", objects).GetString();

    // TODO: should probably have a default font if one wasn't found
	TString fontName = TDataVariant::Find("font", objects).GetString();
	m_font = TFont::Acquire(fontName.GetPointer());

	m_renderOffset.x = TDataVariant::Find("offsetX", objects).GetFloat();
	m_renderOffset.y = TDataVariant::Find("offsetY", objects).GetFloat();
}
