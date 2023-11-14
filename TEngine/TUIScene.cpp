#include "TUIScene.h"
#include "TUISceneEntry.h"
#include "TMemory.h"
#include "TRenderableInterface.h"
#include "TUIEntity.h"

//-------------------------------------------------------------------------------
DefineSingleton(TUIScene);

//-------------------------------------------------------------------------------
TUIScene::TUIScene()
:	m_sceneRoot(NULL)
{
}

//-------------------------------------------------------------------------------
TUIScene::~TUIScene()
{
	TUISceneEntry* entry = NULL;

	while (m_sceneRoot != NULL)
	{
		entry = m_sceneRoot;

		m_sceneRoot = m_sceneRoot->nextEntry;

		TSafeDelete(entry);
	}
}

//-------------------------------------------------------------------------------
void TUIScene::AddEntry(TRenderableInterface* renderable)
{
	TPlugin* plugin = static_cast<TPlugin*>(renderable);
	TUIEntity* entity = static_cast<TUIEntity*>(plugin->GetEntity());
	float depth = entity->GetRenderDepth();

	TUISceneEntry* newEntry = TNew TUISceneEntry();

	newEntry->depth = depth;
	newEntry->renderable = renderable;
	newEntry->nextEntry = NULL;

	if (m_sceneRoot == NULL)
	{
		m_sceneRoot = newEntry;
	}
	else
	{
		TUISceneEntry* entry = m_sceneRoot;
		TUISceneEntry* entryPrevious = NULL;

		while (entry != NULL)
		{
			if (entry->depth > newEntry->depth)
			{
				if (entryPrevious != NULL)
				{
					entryPrevious->nextEntry = newEntry;
				}
				else
				{
					m_sceneRoot = newEntry;
				}

				newEntry->nextEntry = entry;

				break;
			}

			entryPrevious = entry;
			entry = entry->nextEntry;
		}

		if (entry == NULL)
		{
			if (entryPrevious != NULL)
			{
				if (entryPrevious->nextEntry != NULL)
				{
					TDebugPrint(("Last TUIScene Entry has a bad Next ptr"));
				}
				
				entryPrevious->nextEntry = newEntry;
			}
			else
			{
				TDebugPrint(("TUIScene has no entries"));
			}
		}
	}
}

//-------------------------------------------------------------------------------
void TUIScene::RemoveEntry(TRenderableInterface* renderable)
{
	TUISceneEntry* entry = m_sceneRoot;
	TUISceneEntry* entryPrevious = NULL;

	while (entry != NULL)
	{
		if (entry->renderable == renderable)
		{
			if (entryPrevious == NULL)
			{
				// must be the first entry
				m_sceneRoot = entry->nextEntry;
			}
			else
			{
				entryPrevious->nextEntry = entry->nextEntry;
			}

			break;
		}

		entryPrevious = entry;
		entry = entry->nextEntry;
	}

	TSafeDelete(entry);
}

//-------------------------------------------------------------------------------
void TUIScene::OnRender()
{
	TUISceneEntry* entry = m_sceneRoot;

	while (entry != NULL)
	{
		entry->renderable->OnRender();

		entry = entry->nextEntry;
	}
}
