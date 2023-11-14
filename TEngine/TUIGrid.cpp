#include "TUIGrid.h"
#include "TUIMappingContainer.h"

//-------------------------------------------------------------------------------
TUIGrid::TUIGrid()
:	m_countMapping(NULL),
	m_childSpacing(0,0)
{
}

//-------------------------------------------------------------------------------
TUIGrid::~TUIGrid()
{
}

//-------------------------------------------------------------------------------
TXMLObject* TUIGrid::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	if (id == "UIObject")
	{
		if (m_children.GetSize() > 0)
		{
			TDebugPrint(("[TUIGrid::HandleLoadElement] There is already a template element, there should only be one"));

			return NULL;
		}

		TUIEntity* newChild = TNew TUIEntity();

		m_children.Add(newChild);

		return newChild;
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TUIGrid::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_childSpacing.x = TDataVariant::Find("cellSpacingX", objects).GetFloat();
	m_childSpacing.y = TDataVariant::Find("cellSpacingY", objects).GetFloat();

	m_mappingObject = TDataVariant::Find("UIMapping", objects).GetString();
	m_mappingFunction = TDataVariant::Find("UICountMapping", objects).GetString();
}

//-------------------------------------------------------------------------------
void TUIGrid::FinaliseLoad()
{
	m_countMapping = TUIMappingContainer::Get()->GetMapping(m_mappingObject, m_mappingFunction);

	UpdateChildCount();
}

//-------------------------------------------------------------------------------
void TUIGrid::UpdateChildCount()
{
	if (m_children.GetSize() == 0)
	{
		TDebugPrint(("[TUIGrid::UpdateChildCount] Grid has no template to clone"));

		return;
	}

	unsigned int count = 0;

	if (m_countMapping != NULL)
	{
		m_countMapping->Execute(NULL, &m_variableResult);

		count = m_variableResult.intValue;
	}

	if (m_children.GetSize() != count)
	{
		while (m_children.GetSize() > count)
		{
			TSafeDelete(m_children[ m_children.GetSize() - 1]);

			m_children.RemoveAt(m_children.GetSize() - 1);
		}

		for (unsigned int index = m_children.GetSize(); index < count; index++)
		{
			//TUIEntity* newEntity = m_children[0]->Clone();

			//m_pChildren.Add(newEntity);
		}

		for (unsigned int index = 0; index < m_children.GetSize(); index++)
		{
			m_children[index]->SetPosition(m_children[0]->GetPosition() + TVector3(m_childSpacing.x * index, m_childSpacing.y * index, 0.f));
			m_children[index]->SetVariableIndex(index);
		}
	}
}
