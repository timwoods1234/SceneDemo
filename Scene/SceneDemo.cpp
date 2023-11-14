#include "SceneDemo.h"
#include "FreeCamera.h"
#include "Terrain.h"
#include "GameWorld.h"
#include "GrassBatcher.h"
#include "Sky.h"
#include "TGameStats.h"

//-------------------------------------------------------------------------------
SceneDemo::SceneDemo()
{
	m_stateName = "SceneDemo";

	TEventUpdate::Get()->Register(this, &SceneDemo::Update);
	TEventUIRender::Get()->Register(this, &SceneDemo::Render);

	TCamera* mainCamera = TCameraManager::Get()->GetCamera("MainCamera");

	m_cameraController = TNew FreeCamera(mainCamera);
	m_cameraController->SetSpeed(50.f);

	// TODO: the order here shouldn't matter, the Z state should take care of the fill order
	m_sky = TNew Sky();
	m_terrain = TNew Terrain();
	//m_sky = TNew Sky();

	GrassBatcher::Create();

	m_gameWorld = TNew GameWorld(m_terrain);

	TGameStats::Get()->Enable(true);

	m_outputStream = TNew TScreenOutputStream();
}

//-------------------------------------------------------------------------------
SceneDemo::~SceneDemo()
{
	TSafeDelete(m_outputStream);
	TSafeDelete(m_sky);
	TSafeDelete(m_gameWorld);
	TSafeDelete(m_terrain);
	TSafeDelete(m_cameraController);

	GrassBatcher::Destroy();

	TEventUpdate::Get()->Unregister(this, &SceneDemo::Update);
	TEventUIRender::Get()->Unregister(this, &SceneDemo::Render);
}

//-------------------------------------------------------------------------------
void SceneDemo::Update(float elapsedTime)
{
	m_cameraController->Update(elapsedTime);

	TVector3 position = m_cameraController->GetPosition();

	float terrainHeightAtCamera = 1.f + m_terrain->GetHeight(position.x, position.z);

	if (position.y < terrainHeightAtCamera)
	{
		position.y = terrainHeightAtCamera;
		m_cameraController->SetPosition(position);
	}

	if (TLocator::GetInput()->IsPressed(TINPUT_RETURN))
	{
		TVector3 position = m_cameraController->GetPosition();
		TString displayString = TString::Format("<GrassPosition x=\"%.0f\" z=\"%.0f\"/>", position.x, position.z);
		TDebugPrint((displayString.GetPointer()));
	}
	if (TLocator::GetInput()->IsPressed(TINPUT_BACKSPACE))
	{
		TVector3 position = m_cameraController->GetPosition();
		TString displayString = TString::Format("<Entity definition=\"tree0\" x=\"%.0f\" z=\"%.0f\" scaleX=\"0.6\" scaleY=\"0.6\" scaleZ=\"0.6\"/>", position.x, position.z);
		TDebugPrint((displayString.GetPointer()));
	}
}

//-------------------------------------------------------------------------------
void SceneDemo::Render()
{
	m_outputStream->SetPosition(200, 550);
	m_outputStream->WriteString("WASD to move, Q/E to change height, L-Shift for speed");
}