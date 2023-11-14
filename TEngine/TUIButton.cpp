#include "TUIButton.h"
#include "TUIMappingContainer.h"
#include "TUIMapping.h"
#include "TCursorManager.h"
#include "TEntity.h"
#include "TEventUIUpdate.h"
#include "TUIEntity.h"

//-------------------------------------------------------------------------------
TUIButton::TUIButton(TEntity* entity, TPluginDefinition* definition)
:	TPlugin(entity, definition),
	m_size(0,0),
	m_callback(NULL)
{
	TEventUIUpdate::Get()->Register(this, &TUIButton::OnUpdate);
}

//-------------------------------------------------------------------------------
TUIButton::~TUIButton()
{
	TEventUIUpdate::Get()->Unregister(this, &TUIButton::OnUpdate);
}

//-------------------------------------------------------------------------------
void TUIButton::OnUpdate()
{
	if (m_callback != NULL)
	{
		for (unsigned int index = 0; index < TCursorManager::Get()->GetNumCursors(); ++index)
		{
			TCursorEntry currentEntry = TCursorManager::Get()->GetCursorEntry(index);

			if (currentEntry.position.x >= m_entity->GetPosition().x &&
				currentEntry.position.x < m_entity->GetPosition().x + m_size.x &&
				currentEntry.position.y >= m_entity->GetPosition().y && 
				currentEntry.position.y < m_entity->GetPosition().y + m_size.y)
			{
				if (currentEntry.IsPressed())
				{
					m_parameter.intValue = static_cast<TUIEntity*>(m_entity)->GetVariableIndex();

					m_callback->Execute(&m_parameter, NULL);
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------
void TUIButton::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	float width = TDataVariant::Find("width", objects).GetFloat();
	float height = TDataVariant::Find("height", objects).GetFloat();
	m_size.Set(width, height);

	m_mappingObject = TDataVariant::Find("UIMapping", objects).GetString();
	m_mappingFunction = TDataVariant::Find("UICallback", objects).GetString();
}

//-------------------------------------------------------------------------------
void TUIButton::FinaliseLoad()
{
    if (!m_mappingObject.IsEmpty() && !m_mappingFunction.IsEmpty())
    {
        m_callback = TUIMappingContainer::Get()->GetMapping(m_mappingObject, m_mappingFunction);

        if (m_callback == NULL)
        {
            TDebugPrint(("[TUIButton::FinaliseLoad] Failed to find UI mapping (%s, %s)", m_mappingObject.GetPointer(), m_mappingFunction.GetPointer()));
        }
    }
}
