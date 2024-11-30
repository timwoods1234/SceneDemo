#ifndef __SCENEDEMO_H__
#define __SCENEDEMO_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

class FreeCamera;
class Terrain;
class GameWorld;
class Sky;

class SceneDemo : public TGameState,
				  public TEventListener
{
public:
	SceneDemo();

	~SceneDemo();

	void Update(float elapsedTime);

	void Render();

	void RenderDebug();

private:
	TScreenOutputStream* m_outputStream;

	FreeCamera* m_cameraController;

	Terrain* m_terrain;

	GameWorld* m_gameWorld;

	TDirectionalLight m_light;

	Sky* m_sky;

	TEntity* m_pickedEntity;
};

#endif
