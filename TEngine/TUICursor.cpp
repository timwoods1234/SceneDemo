#include "TUICursor.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TAtlasManager.h"
#include "TAtlasEntry.h"
#include "TUIScene.h"
#include "TPlatform.h"
#include "TTexture.h"
#include "TCursorManager.h"

//-------------------------------------------------------------------------------
TUICursor::TUICursor(TEntity* entity, TPluginDefinition* definition)
:	TRenderableInterface(entity, definition),
	m_texture(NULL),
	m_renderSize(0,0)
{
}

//-------------------------------------------------------------------------------
TUICursor::~TUICursor()
{
	TUIScene::Get()->RemoveEntry(this);

	TTexture::Release(m_texture);
}

//-------------------------------------------------------------------------------
void TUICursor::OnRender()
{
	int numCursors = TCursorManager::Get()->GetNumCursors();

	if (numCursors > 0)
	{
		const TCursorEntry& cursorEntry = TCursorManager::Get()->GetCursorEntry(0);

		TLocator::GetRenderer()->Draw2D(m_texture, cursorEntry.position, m_textureCoords, 0.f, m_renderSize.x, m_renderSize.y);
	}
}

//-------------------------------------------------------------------------------
void TUICursor::FinaliseLoad()
{
	TUIScene::Get()->AddEntry(this);
}

//-------------------------------------------------------------------------------
void TUICursor::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	TString textureName = TString::Format("Assets/UI/%s.png", TDataVariant::Find("texture", objects).GetString());
	m_texture = TTexture::Acquire(textureName.GetPointer());
	
	int width = TDataVariant::Find("width", objects).GetInt();
	int height = TDataVariant::Find("height", objects).GetInt();

	if (width == 0 || height == 0)
	{
		if (m_texture != NULL)
		{
			width = m_texture->GetWidth();
			height = m_texture->GetHeight();
		}
		else
		{
			TDebugPrint(("[TUICursor::HandleLoadAttributes] No size for %s", textureName.GetPointer()));
		}
	}

	m_renderSize.Set((float)width, (float)height);
	m_textureCoords.Set(0, 0, 1, 1);
}