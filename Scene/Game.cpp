#include "TEngine.h"
#include "ModelPlugin.h"
#include "LightPlugin.h"

#include "Game.h"
#include "SceneDemo.h"

//-------------------------------------------------------------------------------
Game::Game()
{
	LightPlugin::Register();
	ModelPlugin::Register();

	TSimpleScene* scene = TNew TSimpleScene();
	TLocator::RegisterScene(scene);

	TGameStateManager::Create();
	TGameStateManager::Get()->AddState(TNew SceneDemo());
	TGameStateManager::Get()->SwitchState("SceneDemo");
}

//-------------------------------------------------------------------------------
Game::~Game()
{
	TGameStateManager::Destroy();

	TSimpleScene* scene = static_cast<TSimpleScene*>(TLocator::GetScene());
	TSafeDelete(scene);
}
