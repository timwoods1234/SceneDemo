#include "TServiceCreator.h"
#include "TLocator.h"
#include "TMemory.h"
#include "TPlatform.h"
#include "TXMLReader.h"

#include "TEventUpdate.h"
#include "TEventRender.h"
#include "TEventUIRender.h"
#include "TEventUIUpdate.h"
#include "TUIMappingContainer.h"
#include "TCursorManager.h"
#include "TConsole.h"
#include "TCamera.h"
#include "TResourceManager.h"
#include "TSceneInterface.h"
#include "TAtlasManager.h"
#include "TUIScene.h"
#include "TRendererInterface.h"
#include "TInputInterface.h"
#include "TTimerInterface.h"
#include "TRenderQueueManager.h"
#include "TDebugRenderer.h"
#include "TAudioConfig.h"
#include "TAudioInterface.h"
#include "TPluginRegister.h"
#include "TCameraManager.h"
#include "TGameStats.h"
#include "TLightManager.h"

#ifdef TPLATFORM_WIN
#	include "TWindowsApplication.h"
#	include "TWindowsTimer.h"
#	include "TDirectInput.h"
#	include "TDirectSoundSystem.h"
#	include "TD3DRenderer.h"
#	include "TWindowsDebug.h"
#	include "TWindowsFileSystem.h"
#	include "TAIMeshLoader.h"
#endif // #ifdef TPLATFORM_WIN

//-------------------------------------------------------------------------------
void TServiceCreator::CreateServices()
{
	CreatePlatformIndependentServices();

	CreatePlatformServices();

	CreatePlatformDependentServices();
}

//-------------------------------------------------------------------------------
void TServiceCreator::DestroyServices()
{
	DestroyPlatformDependentServices();

	DestroyPlatformServices();

	DestroyPlatformIndependentServices();
}

//-------------------------------------------------------------------------------
void TServiceCreator::CreatePlatformServices()
{
#ifdef TPLATFORM_WIN
	TWindowsApplication* application = static_cast<TWindowsApplication*>(TLocator::GetApplication());

	HWND window = application->GetWindow();
	HINSTANCE instance = application->GetInstance();

	TWindowsFileSystem* fileSystem = TNew TWindowsFileSystem(window);
	TLocator::RegisterFileSystem(fileSystem);

	TWindowsTimer* timer = TNew TWindowsTimer();
	TLocator::RegisterTimer(timer);

	TD3DRenderer* renderer = TNew TD3DRenderer(window);
	TLocator::RegisterRenderer(renderer);

	TDirectInput* input = TNew TDirectInput(window, instance);
	TLocator::RegisterInput(input);

	TDirectSoundSystem* directAudio = TNew TDirectSoundSystem(window);
	TLocator::RegisterAudio(directAudio);

#endif // #ifdef TPLATFORM_WIN
	
#if TENGINE_USE_AIMESH
	TAIMeshLoader* meshLoader = TNew TAIMeshLoader();
	TLocator::RegisterMeshLoader(meshLoader);
#endif // #if TENGINE_USE_AIMESH
}

//-------------------------------------------------------------------------------
void TServiceCreator::DestroyPlatformServices()
{
#ifdef TPLATFORM_WIN
	TAudioInterface* audio = TLocator::GetAudio();
	TSafeDelete(audio);

	TInputInterface* input = TLocator::GetInput();
	TSafeDelete(input);

	TRendererInterface* renderer = TLocator::GetRenderer();
	TSafeDelete(renderer);

	TTimerInterface* timer = TLocator::GetTimer();
	TSafeDelete(timer);

	TFileSystemInterface* fileSystem = TLocator::GetFileSystem();
	TSafeDelete(fileSystem);
#endif // #ifdef TPLATFORM_WIN

#if TENGINE_USE_AIMESH
	TMeshLoaderInterface* meshLoader = TLocator::GetMeshLoader();
	TSafeDelete(meshLoader);
#endif // #if TENGINE_USE_AIMESH
}

//-------------------------------------------------------------------------------
void TServiceCreator::CreatePlatformDependentServices()
{
	TConsole::Create();
	TRenderQueueManager::Create();
	TUIScene::Create();
	TDebugRenderer::Create();
    TCameraManager::Create();
	TLightManager::Create();
	TGameStats::Create();

	if (TLocator::GetAudio()->IsSoundAvailable())
	{
		TAudioConfig audioConfig;

		TXMLReader reader("Assets/Data/Engine/Audio.xml", audioConfig);

		if (reader.WasError())
		{
			TDebugPrint(("Unable to locate Audio.xml"));
		}
	}
}

//-------------------------------------------------------------------------------
void TServiceCreator::CreatePlatformIndependentServices()
{
	TResourceManager::Create();
	TPluginRegister::Create();
	TCursorManager::Create();
	TUIMappingContainer::Create();
	TAtlasManager::Create();
	TEventRender::Create();
	TEventUIUpdate::Create();
	TEventUIRender::Create();
	TEventUpdate::Create();
}

//-------------------------------------------------------------------------------
void TServiceCreator::DestroyPlatformDependentServices()
{
	TGameStats::Destroy();
	TLightManager::Destroy();
    TCameraManager::Destroy();
	TDebugRenderer::Destroy();
	TUIScene::Destroy();
	TRenderQueueManager::Destroy();
	TConsole::Destroy();
}

//-------------------------------------------------------------------------------
void TServiceCreator::DestroyPlatformIndependentServices()
{
	TEventUpdate::Destroy();
	TEventRender::Destroy();
	TEventUIUpdate::Destroy();
	TEventUIRender::Destroy();
	TAtlasManager::Destroy();
	TUIMappingContainer::Destroy();
	TCursorManager::Destroy();
	TPluginRegister::Destroy();
	TResourceManager::Destroy();
}
