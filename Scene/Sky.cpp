#include "Sky.h"
#include "SphereCreator.h"
#include "TGraphicsFactoryInterface.h"

//-------------------------------------------------------------------------------
Sky::Sky()
{
	TEventRender::Get()->Register(this, &Sky::OnRender);

	m_sphereMesh = TMesh::Acquire();
	TShader* skyShader = TShader::Acquire("Sky");

	if (skyShader != NULL)
	{
		// TODO: drive from data
		m_cubeMap = TTexture::LoadCubeMap("sky/cubemap.dds");

		skyShader->SetTexture("gEnvironmentMap", m_cubeMap);

		m_sphereMesh->SetShader(skyShader);
		SphereCreator::CreateSphere(*m_sphereMesh);

		TShader::Release(skyShader);
	}
}

//-------------------------------------------------------------------------------
Sky::~Sky()
{
	TTexture::UnloadCubeMap(m_cubeMap);

	TMesh::Release(m_sphereMesh);

	TEventRender::Get()->Unregister(this, &Sky::OnRender);
}

//-------------------------------------------------------------------------------
void Sky::OnRender()
{
	TCamera* currentCamera = TLocator::GetRenderer()->GetCurrentCamera();

	if (currentCamera != NULL)
	{
		TMatrix matDraw;
		matDraw.Translate(currentCamera->GetPosition());

		TLocator::GetRenderer()->DrawMesh(matDraw, *m_sphereMesh);
	}
}
