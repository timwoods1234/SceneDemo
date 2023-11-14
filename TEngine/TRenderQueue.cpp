#include "TRenderQueue.h"
#include "TRenderableInterface.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TMatrix.h"
#include "TMesh.h"
#include "TEntity.h"

//-------------------------------------------------------------------------------
TRenderQueue::TRenderQueue(TShader* shader)
:	m_nextQueue(NULL)
{
	m_shader = shader;
}

//-------------------------------------------------------------------------------
TRenderQueue::~TRenderQueue()
{
}

//-------------------------------------------------------------------------------
void TRenderQueue::AddEntry(const TEntity* entity, const TMesh* mesh)
{
	TRenderQueueEntry entry;

	entry.entity = entity;
	entry.mesh = mesh;

	m_renderQueueEntries.Add(entry);
}

//-------------------------------------------------------------------------------
void TRenderQueue::ExecuteRender()
{
	static TMatrix matRotation, matTranslation, matScaling, matTransform;
	unsigned int numEntries = m_renderQueueEntries.GetSize();
	const TEntity* currentEntity = NULL;

	for (unsigned int index = 0; index < numEntries; index++)
	{
		currentEntity = m_renderQueueEntries[index].entity;

		matTransform.SetIdentity();

		TVector3 position = currentEntity->GetPosition();
		TVector3 rotation = currentEntity->GetRotation();
		TVector3 scale = currentEntity->GetScale();

		if (rotation == TVector3::Zero() && scale == TVector3::One())
		{
			matTransform[3][0] = currentEntity->GetPosition().x;
			matTransform[3][1] = currentEntity->GetPosition().y;
			matTransform[3][2] = currentEntity->GetPosition().z;
			matTransform[3][3] = 1.f;
		}
		else
		{
			matRotation.SetIdentity();
			matRotation.RotateXYZ(rotation);

			matTranslation.SetIdentity();
			matTranslation.SetPos(position);

			matScaling.SetIdentity();
			matScaling.Scale(scale);

			matTransform = matRotation * matScaling * matTranslation;
		}
		
		TLocator::GetRenderer()->DrawMesh(matTransform, *(m_renderQueueEntries[index].mesh));
	}
}

//-------------------------------------------------------------------------------
void TRenderQueue::Clear()
{
	m_renderQueueEntries.Clear();
}

//-------------------------------------------------------------------------------
TShader* TRenderQueue::GetShader() const
{
	return m_shader;
}

//-------------------------------------------------------------------------------
void TRenderQueue::SetNextQueue(TRenderQueue* queue)
{
	m_nextQueue = queue;
}

//-------------------------------------------------------------------------------
TRenderQueue* TRenderQueue::GetNext() const
{
	return m_nextQueue;
}
