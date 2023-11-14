#include "TSimpleScene.h"
#include "TSceneEntry.h"
#include "TRenderableInterface.h"
#include "ColliderPlugin.h"
#include "TEntity.h"
#include "TMemory.h"
#include "TLocator.h"
#include "TCamera.h"
#include "TLocator.h"
#include "TAABB.h"
#include "TRendererInterface.h"
#include "TEventRender.h"
#include "TConfig.h"

//-------------------------------------------------------------------------------
TSimpleScene::TSimpleScene()
{
}

//-------------------------------------------------------------------------------
TSimpleScene::~TSimpleScene()
{
	Clear();
}

//-------------------------------------------------------------------------------
void TSimpleScene::Clear()
{
	for (unsigned int index = 0; index < m_sceneEntries.GetSize(); index++)
	{
		TSafeDelete(m_sceneEntries[index]);
	}

	m_sceneEntries.Clear();
}

//-------------------------------------------------------------------------------
void TSimpleScene::OnRender(TCamera* camera)
{
	PerformCleanup();

	TAABB box;
	unsigned int numEntries = m_sceneEntries.GetSize();

	for (unsigned int index = 0; index < numEntries; index++)
	{
        m_sceneEntries[index]->GetRenderable()->ComputeBounds(box);

        if (camera->IsVisible(box))
        {
            m_sceneEntries[index]->GetRenderable()->OnRender();
        }
	}
}

//-------------------------------------------------------------------------------
void TSimpleScene::PerformCollisionDetection()
{
	ColliderPlugin* a;
	ColliderPlugin* b;
	unsigned int numEntries = m_sceneEntries.GetSize();

	for (unsigned int row = 0; row < numEntries; row++)
	{
		for (unsigned int column = row + 1; column < numEntries; column++)
		{
			a = m_sceneEntries[row]->GetCollider();
			b = m_sceneEntries[column]->GetCollider();

			if (a != NULL && b != NULL && a->Collides(*b))
			{
				a->GetCollisionEvent().Execute(*b);
				b->GetCollisionEvent().Execute(*a);
			}
		}
	}

	PerformCleanup();
}

//-------------------------------------------------------------------------------
void TSimpleScene::PerformCleanup()
{
	while (m_removeEntries.GetSize() > 0)
	{
		for (unsigned int index = 0; index < m_sceneEntries.GetSize(); index++)
		{
			if (m_sceneEntries[index]->GetRenderable() == m_removeEntries[0]->GetRenderable())
			{
				TSafeDelete(m_sceneEntries[index]);

				m_sceneEntries.RemoveAt(index);

				break;
			}
		}

		m_removeEntries.RemoveAt(0);
	}
}

//-------------------------------------------------------------------------------
void TSimpleScene::AddEntry(TRenderableInterface* renderable)
{
	TSceneEntry* newSceneEntry = TNew TSceneEntry(renderable);

	m_sceneEntries.Add(newSceneEntry);
}

//-------------------------------------------------------------------------------
void TSimpleScene::RemoveEntry(TRenderableInterface* renderable)
{
	unsigned int numEntries = m_sceneEntries.GetSize();

	for (unsigned int index = 0; index < numEntries; index++)
	{
		if (m_sceneEntries[index]->GetRenderable() == renderable)
		{
			m_removeEntries.Add(m_sceneEntries[index]);

			break;
		}
	}
}
