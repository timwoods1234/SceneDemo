#include "TCameraManager.h"
#include "TCamera.h"
#include "TMemory.h"
#include "TLocator.h"
#include "TSceneInterface.h"
#include "TUIScene.h"
#include "TFileSystemInterface.h"
#include "TRenderQueueManager.h"
#include "TRendererInterface.h"
#include "TEventRender.h"
#include "TEventUIRender.h"

//-------------------------------------------------------------------------------
DefineSingleton(TCameraManager);

//-------------------------------------------------------------------------------
TCameraManager::TCameraManager()
{
    LoadCameras();
}

//-------------------------------------------------------------------------------
TCameraManager::~TCameraManager()
{
    for (unsigned int index = 0; index < m_cameras.GetSize(); index++)
    {
        TSafeDelete(m_cameras[index]);
    }
}

//-------------------------------------------------------------------------------
void TCameraManager::LoadCameras()
{
    TDynamicSet<TString> filenames;
    TLocator::GetFileSystem()->GetFileList("Assets/Data/Camera", "xml", filenames);

    int numCameras = filenames.GetSize();

    for (int index = 0; index < numCameras; index++)
    {
        TCamera* camera = TNew TCamera(filenames[index].GetPointer());

        m_cameras.Add(camera);
    }
}

//-------------------------------------------------------------------------------
TCamera* TCameraManager::GetCamera(const char* name)
{
	TCamera* result = NULL;

	for (unsigned int index = 0; index < m_cameras.GetSize(); index++)
	{
		if (m_cameras[index]->GetName() == name)
		{
			result = m_cameras[index];

			break;
		}
	}

	if (result == NULL)
	{
		TDebugPrint(("[TCameraManager::GetCamera] Camera not found: %s", name));
	}

	return result;
}

//-------------------------------------------------------------------------------
void TCameraManager::OnRender()
{
	TSceneInterface* scene = TLocator::GetScene();

    for (unsigned int index = 0; index < m_cameras.GetSize(); index++)
    {
        TLocator::GetRenderer()->SetCurrentCamera(m_cameras[index]);

        if (m_cameras[index]->UICamera())
        {
            TUIScene::Get()->OnRender();

            TEventUIRender::Get()->Execute();
        }
        else
        {
			if (scene != NULL)
			{
				scene->OnRender(m_cameras[index]);
			}

            if (m_cameras[index]->MainCamera())
            {
                TEventRender::Get()->Execute();
            }
        }

		TLocator::GetRenderer()->FlushRenderQueue();
    }
}
