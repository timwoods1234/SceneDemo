#include "TLocator.h"

//-------------------------------------------------------------------------------
TAudioInterface*			TLocator::m_audio = NULL;
TInputInterface*			TLocator::m_input = NULL;
TRendererInterface*			TLocator::m_renderer = NULL;
TSceneInterface*			TLocator::m_scene = NULL;
TTimerInterface*			TLocator::m_timer = NULL;
TApplicationInterface*		TLocator::m_application	= NULL;
TDebugInterface*			TLocator::m_debugSystem	= NULL;
TFileSystemInterface*		TLocator::m_fileSystem = NULL;
TMeshLoaderInterface*		TLocator::m_meshLoader = NULL;
TGraphicsFactoryInterface*	TLocator::m_graphicsFactory = NULL;

//-------------------------------------------------------------------------------
void TLocator::RegisterAudio(TAudioInterface* audio)
{
	m_audio = audio;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterInput(TInputInterface* input)
{
	m_input = input;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterFileSystem(TFileSystemInterface* fileSystem)
{
	m_fileSystem = fileSystem;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterRenderer(TRendererInterface* renderer) 
{
	m_renderer = renderer;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterScene(TSceneInterface* scene)
{
	m_scene = scene;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterTimer(TTimerInterface* timer)
{
	m_timer = timer;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterApplication(TApplicationInterface* application)
{
	m_application = application;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterDebugSystem(TDebugInterface* debugSystem)
{
	m_debugSystem = debugSystem;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterMeshLoader(TMeshLoaderInterface *meshLoader)
{
	m_meshLoader = meshLoader;
}

//-------------------------------------------------------------------------------
void TLocator::RegisterGraphicsFactory(TGraphicsFactoryInterface* factory)
{
	m_graphicsFactory = factory;
}
