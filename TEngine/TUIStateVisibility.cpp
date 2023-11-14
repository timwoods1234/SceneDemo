#include "TUIStateVisibility.h"
#include "TUIEntity.h"
#include "TEventUIUpdate.h"
#include "TUIMappingContainer.h"

//-------------------------------------------------------------------------------
TUIStateVisibility::TUIStateVisibility(TEntity* entity, TPluginDefinition* definition)
:	TPlugin(entity, definition),
	m_stateMapping(NULL)
{
	m_mappingObject = TString::GetEmptyString();
	m_mappingFunction = TString::GetEmptyString();
	m_currentState = TString::GetEmptyString();
	m_activeState = TString::GetEmptyString();

	TEventUIUpdate::Get()->Register(this, &TUIStateVisibility::Update);
}

//-------------------------------------------------------------------------------
TUIStateVisibility::~TUIStateVisibility()
{
	TEventUIUpdate::Get()->Unregister(this, &TUIStateVisibility::Update);
}

//-------------------------------------------------------------------------------
void TUIStateVisibility::Update()
{
	if (m_stateMapping != NULL)
	{
		m_variableParameter.intValue = static_cast<TUIEntity*>(m_entity)->GetVariableIndex();

		m_stateMapping->Execute(&m_variableParameter, &m_variableResult);

		if (m_variableResult.stringValue != m_currentState)
		{
			m_currentState = m_variableResult.stringValue;

			if (m_currentState == m_activeState)
			{
				ToggleVisibility();
			}
		}
	}
}

//-------------------------------------------------------------------------------
void TUIStateVisibility::OnEnabled()
{
	TEventUIUpdate::Get()->Register(this, &TUIStateVisibility::Update);
}

//-------------------------------------------------------------------------------
void TUIStateVisibility::OnDisabled()
{
	TEventUIUpdate::Get()->Unregister(this, &TUIStateVisibility::Update);
}

//-------------------------------------------------------------------------------
TXMLObject* TUIStateVisibility::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	if (id == "VisibilityToggle")
	{
		TUIVisibilityToggle toggle;

		toggle.strTarget = TDataVariant::Find("target", objects).GetString();
		toggle.bVisible = TDataVariant::Find("visible", objects).GetBool();

		m_visibilityToggles.Add(toggle);
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TUIStateVisibility::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_mappingObject = TDataVariant::Find("UIMapping", objects).GetString();
	m_mappingFunction = TDataVariant::Find("UIStateMapping", objects).GetString();

	m_activeState = TDataVariant::Find("activeState", objects).GetString();
}

//-------------------------------------------------------------------------------
void TUIStateVisibility::FinaliseLoad()
{
	if (!m_mappingObject.IsEmpty() && !m_mappingFunction.IsEmpty())
	{
		m_stateMapping = TUIMappingContainer::Get()->GetMapping(m_mappingObject, m_mappingFunction);

		if (m_stateMapping == NULL)
		{
			TDebugPrint(("[TUIStateVisibility::FinaliseLoad] Failed to find UI mapping (%s, %s)", m_mappingObject.GetPointer(), m_mappingFunction.GetPointer()));
		}
	}
}

//-------------------------------------------------------------------------------
void TUIStateVisibility::Write(TXMLWriter& writer)
{
}

//-------------------------------------------------------------------------------
void TUIStateVisibility::ToggleVisibility()
{
	TUIEntity* uiEntity = static_cast<TUIEntity*>(m_entity);

	for (unsigned int index = 0; index < m_visibilityToggles.GetSize(); index++)
	{
		TUIEntity* target = uiEntity->GetChild(m_visibilityToggles[index].strTarget);

		if (target != NULL)
		{
			target->SetActive(m_visibilityToggles[index].bVisible);
		}
	}
}
