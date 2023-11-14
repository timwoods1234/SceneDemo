#include "TRenderQueueManager.h"
#include "TRenderQueue.h"
#include "TShader.h"

//-------------------------------------------------------------------------------
DefineSingleton(TRenderQueueManager);

//-------------------------------------------------------------------------------
TRenderQueueManager::TRenderQueueManager()
:	m_headQueue(NULL)
{
}

//-------------------------------------------------------------------------------
TRenderQueueManager::~TRenderQueueManager()
{
	TRenderQueue* currentQueue = NULL;
	TRenderQueue* nextQueue = m_headQueue;

	while (nextQueue != NULL)
	{
		currentQueue = nextQueue;

		nextQueue = currentQueue->GetNext();

		TShader* shader = currentQueue->GetShader();
		TShader::Release(shader);

		TSafeDelete(currentQueue);
	}
}

//-------------------------------------------------------------------------------
TRenderQueue* TRenderQueueManager::GetRenderQueue(const TString& id)
{
	TRenderQueue* currentQueue = m_headQueue;

	while (currentQueue != NULL)
	{
		if (currentQueue->GetShader()->GetId() == id)
		{
			return currentQueue;
		}

		currentQueue = currentQueue->GetNext();
	}

	return CreateRenderQueue(id);
}

//-------------------------------------------------------------------------------
TRenderQueue* TRenderQueueManager::CreateRenderQueue(const TString& id)
{
	TShader* shader = TShader::Acquire(id.GetPointer());
	TRenderQueue* result = NULL;

	if (shader != NULL)
	{
		result = TNew TRenderQueue(shader);

		if (m_headQueue == NULL)
		{
			m_headQueue = result;
		}
		else
		{
			// insert according to render order
			TRenderQueue* currentQueue = m_headQueue;
			TRenderQueue* previousQueue = NULL;

			while (currentQueue != NULL)
			{
				if (currentQueue->GetShader()->GetRenderOrder() > shader->GetRenderOrder())
				{
					result->SetNextQueue(currentQueue);
					
					if (previousQueue != NULL)
					{
						previousQueue->SetNextQueue(result);
					}
					else
					{
						m_headQueue = result;
					}

					break;
				}

				previousQueue = currentQueue;
				currentQueue = currentQueue->GetNext();
			}

			if (currentQueue == NULL)
			{
				previousQueue->SetNextQueue(result);

				if (m_headQueue == result)
				{
					m_headQueue = previousQueue;
				}
			}
		}
	}

	return result;
}

//-------------------------------------------------------------------------------
void TRenderQueueManager::ProcessRenderQueue()
{
	TRenderQueue* currentQueue = m_headQueue;

	while (currentQueue != NULL)
	{
		currentQueue->ExecuteRender();
		currentQueue->Clear();

		currentQueue = currentQueue->GetNext();
	}
}
