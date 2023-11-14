#ifndef __TLOCATOR_H__
#define __TLOCATOR_H__

// service locator
// provides a global lookup for engine systems (input/etc)

class TAudioInterface;
class TInputInterface;
class TRendererInterface;
class TSceneInterface;
class TTimerInterface;
class TApplicationInterface;
class TDebugInterface;
class TFileSystemInterface;
class TMeshLoaderInterface;
class TGraphicsFactoryInterface;

class TLocator
{
public:
	static void	RegisterAudio(TAudioInterface* audio);
	static void	RegisterInput(TInputInterface* input);
	static void	RegisterRenderer(TRendererInterface* renderer);
	static void	RegisterScene(TSceneInterface* scene);
	static void	RegisterTimer(TTimerInterface* timer);
	static void	RegisterApplication(TApplicationInterface* application);
	static void	RegisterDebugSystem(TDebugInterface* debugSystem);
	static void RegisterFileSystem(TFileSystemInterface* fileSystem);
	static void RegisterMeshLoader(TMeshLoaderInterface* meshLoader);
	static void RegisterGraphicsFactory(TGraphicsFactoryInterface* factory);

	static inline TAudioInterface *			GetAudio();
	static inline TInputInterface *			GetInput();
	static inline TRendererInterface *		GetRenderer();
	static inline TSceneInterface*			GetScene();
	static inline TTimerInterface*			GetTimer();
	static inline TApplicationInterface*	GetApplication();
	static inline TDebugInterface*			GetDebugSystem();
	static inline TFileSystemInterface*		GetFileSystem();
	static inline TMeshLoaderInterface*		GetMeshLoader();
	static inline TGraphicsFactoryInterface* GetGraphicsFactory();

protected:
	static TAudioInterface* m_audio;
	static TInputInterface* m_input;
	static TRendererInterface* m_renderer;
	static TSceneInterface* m_scene;
	static TTimerInterface* m_timer;
	static TApplicationInterface* m_application;
	static TDebugInterface* m_debugSystem;
	static TFileSystemInterface* m_fileSystem;
	static TMeshLoaderInterface* m_meshLoader;
	static TGraphicsFactoryInterface* m_graphicsFactory;
};

#include "TLocator.inl"

#endif
