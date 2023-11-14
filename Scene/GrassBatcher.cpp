#include "GrassBatcher.h"
#include "GrassVertex.h"

//-------------------------------------------------------------------------------
DefineSingleton(GrassBatcher);

//-------------------------------------------------------------------------------
GrassBatcher::GrassBatcher()
{
	TEventRender::Get()->Register(this, &GrassBatcher::OnRender);

	// TODO: drive from data
	m_grassTexture = TTexture::Acquire("Assets/2D/grassTexture/grassfin.dds");

	m_grassShader = TShader::Acquire("Grass");
	m_grassShader->SetTexture("gTex", m_grassTexture);

	m_grassMesh = TMesh::Acquire();
	m_grassMesh->SetShader(m_grassShader);

	m_timer = 0.f;
}

//-------------------------------------------------------------------------------
GrassBatcher::~GrassBatcher()
{
	TEventRender::Get()->Unregister(this, &GrassBatcher::OnRender);

	TMesh::Release(m_grassMesh);
	TShader::Release(m_grassShader);
	TTexture::Release(m_grassTexture);
}

//-------------------------------------------------------------------------------
void GrassBatcher::Clear()
{
	m_grassPositions.Clear();
}

//-------------------------------------------------------------------------------
void GrassBatcher::AddGrassPosition(const TVector3& position)
{
	m_grassPositions.Add(position);
}

//-------------------------------------------------------------------------------
void GrassBatcher::RebuildMesh()
{
	TDynamicSet<GrassVertex> grassVertices;
	TDynamicSet<unsigned short> grassIndices;
	unsigned int seed = (unsigned int)TLocator::GetTimer()->GetElapsedTime();

	for (unsigned int index = 0; index < m_grassPositions.GetSize(); index++)
	{
		GrassVertex tempGrassVerts[4];

		float amplitude = FastRandom(&seed, 0.5f, 1.f);

		TVector4 colourOffset = TVector4(0.4f, 0.2f, 0.4f, 0.f);

		tempGrassVerts[0] = GrassVertex(TVector3(-1.f, -0.5f, 0.f), TVector2(0.f, 1.f), 0.f, GetRandomVec4(&seed, TVector4(0.f, 0.f, 0.f, 0.f), colourOffset));
		tempGrassVerts[1] = GrassVertex(TVector3(-1.f, 0.5f, 0.f),  TVector2(0.f, 0.f), amplitude, GetRandomVec4(&seed, TVector4(0.f, 0.f, 0.f, 0.f), colourOffset));
		tempGrassVerts[2] = GrassVertex(TVector3(1.f, 0.5f, 0.f),   TVector2(1.f, 0.f), amplitude, GetRandomVec4(&seed, TVector4(0.f, 0.f, 0.f, 0.f), colourOffset));
		tempGrassVerts[3] = GrassVertex(TVector3(1.f, -0.5f, 0.f),  TVector2(1.f, 1.f), 0.f, GetRandomVec4(&seed, TVector4(0.f, 0.f, 0.f, 0.f), colourOffset));

		TVector3 randomPositionOffset = GetRandomVec3(&seed, TVector3(0.75f, 0.75f, 0.75f), TVector3(1.25f, 1.25f, 1.25f));

		tempGrassVerts[0].position *= randomPositionOffset;
		tempGrassVerts[1].position *= randomPositionOffset;
		tempGrassVerts[2].position *= randomPositionOffset;
		tempGrassVerts[3].position *= randomPositionOffset;

		float halfHeight = (tempGrassVerts[1].position.y - tempGrassVerts[0].position.y) * 0.5f;

		TVector3 worldPosition = m_grassPositions[index];
		worldPosition.y += halfHeight;

		tempGrassVerts[0].billboardPosition = worldPosition;
		tempGrassVerts[1].billboardPosition = worldPosition;
		tempGrassVerts[2].billboardPosition = worldPosition;
		tempGrassVerts[3].billboardPosition = worldPosition;

		grassIndices.Add(0 + grassVertices.GetSize());
		grassIndices.Add(1 + grassVertices.GetSize());
		grassIndices.Add(2 + grassVertices.GetSize());
		grassIndices.Add(0 + grassVertices.GetSize());
		grassIndices.Add(2 + grassVertices.GetSize());
		grassIndices.Add(3 + grassVertices.GetSize());

		grassVertices.Add(tempGrassVerts[0]);
		grassVertices.Add(tempGrassVerts[1]);
		grassVertices.Add(tempGrassVerts[2]);
		grassVertices.Add(tempGrassVerts[3]);
	}

	if (grassVertices.GetSize() > 0)
	{
		m_grassMesh->SetVertices(&grassVertices[0], grassVertices.GetSize());
		m_grassMesh->SetIndices(&grassIndices[0], grassIndices.GetSize());
	}
}

//-------------------------------------------------------------------------------
void GrassBatcher::OnRender()
{
	if (m_grassPositions.GetSize() > 0)
	{
		// camera position is pushed by default when the shader was activated, so just push the ViewProjection
		m_grassShader->SetMatrix("gViewProj", &(TLocator::GetRenderer()->GetCurrentCamera()->GetViewProjectionMatrix()));

		m_timer += TLocator::GetTimer()->GetElapsedTime();
		m_grassShader->SetFloat("gTime", m_timer);

		TLocator::GetRenderer()->DrawMesh(TMatrix::GetIdentity(), *m_grassMesh);
	}
}
