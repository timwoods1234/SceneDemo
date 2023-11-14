#include "TUIEntity.h"
#include "TUICursor.h"
#include "TUIButton.h"
#include "TUILabel.h"
#include "TUISlider.h"
#include "TUISprite.h"
#include "TUIGrid.h"
#include "TUIStateVisibility.h"

//-------------------------------------------------------------------------------
static const TString s_stateVisibilityId = "UIStateVisibility";
static const TString s_gridId = "UIGrid";
static const TString s_objectId = "UIObject";
static const TString s_sliderId = "UISlider";
static const TString s_labelId = "UILabel";
static const TString s_cursorId = "UICursor";
static const TString s_buttonId = "UIButton";
static const TString s_spriteId = "UISprite";

//-------------------------------------------------------------------------------
TUIEntity::TUIEntity()
{
	m_name = "";
}

//-------------------------------------------------------------------------------
TUIEntity::~TUIEntity()
{
	for (unsigned int i=0; i<m_children.GetSize(); ++i)
	{
		TSafeDelete(m_children[i]);
	}
}

//-------------------------------------------------------------------------------
const TString& TUIEntity::GetName() const
{
	return m_name;
}

//-------------------------------------------------------------------------------
void TUIEntity::SetVariableIndex(unsigned int index)
{
	m_variableIndex = index;
}

//------------------------------------------------------------------------------- 
float TUIEntity::GetRenderDepth() const
{
	return m_uiDepth;
}

//-------------------------------------------------------------------------------
unsigned int TUIEntity::GetVariableIndex() const
{
	return m_variableIndex;
}

//-------------------------------------------------------------------------------
TUIEntity* TUIEntity::GetChild(const TString& name)
{
	for (unsigned int childIndex = 0; childIndex < m_children.GetSize(); childIndex++)
	{
		if (name == m_children[childIndex]->GetName())
		{
			return m_children[childIndex];
		}
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TUIEntity::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	TEntity::HandleLoadAttributes(objects);

	m_name = TDataVariant::Find("name", objects).GetString();
	m_uiDepth = TDataVariant::Find("depth", objects).GetFloat();

	m_variableIndex = TDataVariant::Find("variableIndex", objects).GetInt();
}

//-------------------------------------------------------------------------------
TXMLObject* TUIEntity::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	if (id == s_spriteId)
	{
		TUISprite* spritePlugin = TNew TUISprite(this, NULL);
		m_plugins.Add(spritePlugin);

		return spritePlugin;
	}
	else if (id == s_buttonId)
	{
		TUIButton* buttonPlugin = TNew TUIButton(this, NULL);
		m_plugins.Add(buttonPlugin);

		return buttonPlugin;
	}
	else if (id == s_cursorId)
	{
		TUICursor* cursorPlugin = TNew TUICursor(this, NULL);
		m_plugins.Add(cursorPlugin);

		return cursorPlugin;
	}
	else if (id == s_labelId)
	{
		TUILabel* labelPlugin = TNew TUILabel(this, NULL);
		m_plugins.Add(labelPlugin);

		return labelPlugin;
	}
	else if (id == s_sliderId)
	{
		TUISlider* sliderPlugin = TNew TUISlider(this, NULL);
		m_plugins.Add(sliderPlugin);

		return sliderPlugin;
	}
	else if (id == s_objectId)
	{
		TUIEntity* newChild = TNew TUIEntity();

		m_children.Add(newChild);

		return newChild;
	}
	else if (id == s_gridId)
	{
		TUIGrid* grid = TNew TUIGrid();

		m_children.Add(grid);

		return grid;
	}
	else if (id == s_stateVisibilityId)
	{
		TUIStateVisibility* stateVisibilityPlugin = TNew TUIStateVisibility(this, NULL);
		m_plugins.Add(stateVisibilityPlugin);

		return stateVisibilityPlugin;
	}

	return NULL;
}
