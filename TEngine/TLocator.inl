#include <cstddef>

#include "TError.h"

//-------------------------------------------------------------------------------
inline TAudioInterface* TLocator::GetAudio()
{
	TASSERT((m_audio != NULL), "[TLocator::GetAudio] Audio is NULL");
	return m_audio;
}

//-------------------------------------------------------------------------------
inline TApplicationInterface* TLocator::GetApplication()
{
	TASSERT((m_application != NULL), "[TLocator::GetApplication] Application is NULL");
	return m_application;
}

//-------------------------------------------------------------------------------
inline TInputInterface* TLocator::GetInput()
{
	TASSERT((m_input != NULL), "[TLocator::GetInput] Input is NULL");
	return m_input;
}

//-------------------------------------------------------------------------------
inline TFileSystemInterface* TLocator::GetFileSystem()
{
	TASSERT((m_fileSystem != NULL), "[TLocator::GetFileSystem] File System is NULL");
	return m_fileSystem;
}

//-------------------------------------------------------------------------------
inline TRendererInterface* TLocator::GetRenderer()
{
	TASSERT((m_renderer != NULL), "[TLocator::GetRenderer] Renderer is NULL");
	return m_renderer;
}

//-------------------------------------------------------------------------------
inline TSceneInterface* TLocator::GetScene()
{
	return m_scene;
}

//-------------------------------------------------------------------------------
inline TTimerInterface* TLocator::GetTimer()
{
	TASSERT((m_timer != NULL), "[TLocator::GetTimer] Timer is NULL");
	return m_timer;
}

//-------------------------------------------------------------------------------
inline TDebugInterface* TLocator::GetDebugSystem()
{
	return m_debugSystem;
}

//-------------------------------------------------------------------------------
inline TMeshLoaderInterface* TLocator::GetMeshLoader()
{
	TASSERT((m_meshLoader != NULL), "[TLocator::GetMeshLoader] Mesh Loader is NULL");
	return m_meshLoader;
}

//-------------------------------------------------------------------------------
inline TGraphicsFactoryInterface* TLocator::GetGraphicsFactory()
{
	TASSERT((m_graphicsFactory != NULL), "[TLocator::GetGraphicsFactory] Factory is NULL");
	return m_graphicsFactory;
}