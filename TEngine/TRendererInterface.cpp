#include "TRendererInterface.h"
#include "TCamera.h"
#include "TShader.h"
#include "TRenderQueueManager.h"
#include "TMesh.h"
#include "TRenderQueue.h"

//-------------------------------------------------------------------------------
TRendererInterface::TRendererInterface()
:	m_currentCamera(NULL),
	m_activeShader(NULL)
{
	m_depthState = RS_DEPTH_UNSET;
	m_shadeState = RS_SHADE_UNSET;
	m_compareState = RS_ZFUNC_UNSET;
	m_cullMode = RS_CULL_UNSET;
}

//-------------------------------------------------------------------------------
TRendererInterface::~TRendererInterface()
{
}

//-------------------------------------------------------------------------------
void TRendererInterface::SetCurrentCamera(TCamera* camera)
{
	m_currentCamera = camera;
}

//-------------------------------------------------------------------------------
TCamera* TRendererInterface::GetCurrentCamera() const
{
	return m_currentCamera;
}

//-------------------------------------------------------------------------------
TShadeState TRendererInterface::GetShadeMode() const
{
	return m_shadeState;
}

//-------------------------------------------------------------------------------
void TRendererInterface::AddToRenderQueue(const TEntity* entity, const TMesh* mesh)
{
	TShader* shader = mesh->GetShader();

	TRenderQueue* renderQueue = TRenderQueueManager::Get()->GetRenderQueue(shader->GetId());

	if (renderQueue != NULL)
	{
		renderQueue->AddEntry(entity, mesh);
	}
}

//-------------------------------------------------------------------------------
void TRendererInterface::FlushRenderQueue()
{
	TRenderQueueManager::Get()->ProcessRenderQueue();
}
