#include "TSurface2DMesh.h"
#include "TLocator.h"
#include "TGraphicsFactoryInterface.h"
#include "TRendererInterface.h"
#include "TVertexUI.h"
#include "TMaterial.h"
#include "TMatrix.h"
#include "TVector4.h"
#include "TTexture.h"
#include "TMesh.h"
#include "TUIVertexCache.h"
#include "TEventRender.h"
#include "TEventUIRender.h"
#include "TSkin.h"

//-------------------------------------------------------------------------------
TSurface2DMesh::TSurface2DMesh()
:	m_uiVertices(NULL),
    m_uiIndices(NULL),
	m_mesh(NULL)
{
	TEventRender::Get()->Register(this, &TSurface2DMesh::Render);
	TEventUIRender::Get()->Register(this, &TSurface2DMesh::Render);
}

//-------------------------------------------------------------------------------
TSurface2DMesh::~TSurface2DMesh()
{
    TMesh::Release(m_mesh);

	TSafeDeleteArray(m_uiVertices);
	TSafeDeleteArray(m_uiIndices);

	for (unsigned int index = 0; index < m_vertexCaches.GetSize(); index++)
	{
        TSafeDelete(m_vertexCaches[index]);
	}

	TEventRender::Get()->Unregister(this, &TSurface2DMesh::Render);
	TEventUIRender::Get()->Unregister(this, &TSurface2DMesh::Render);
}

//-------------------------------------------------------------------------------
void TSurface2DMesh::SetupVertices()
{
	m_mesh = TMesh::Acquire();

	m_mesh->SetShaderByName("Standard2D");
	m_mesh->MarkDynamic();

	TVertexUI v0( TVector3(-0.5f, 0.5f, 0.f),  TVector2(0.f, 0.f) );
	TVertexUI v1( TVector3(0.5f, 0.5f, 0.f),   TVector2(0.f, 0.f) );
	TVertexUI v2( TVector3(-0.5f, -0.5f, 0.f), TVector2(0.f, 0.f) );
	TVertexUI v3( TVector3(0.5f, -0.5f, 0.f),  TVector2(0.f, 0.f) );
	
	m_uiVertices = TNewArray TVertexUI[4];

	m_uiVertices[0] = v0;
	m_uiVertices[1] = v1;
	m_uiVertices[2] = v2;
	m_uiVertices[3] = v3;

	m_uiIndices = TNewArray unsigned short[6];

	m_uiIndices[0] = 0;
	m_uiIndices[1] = 1;
	m_uiIndices[2] = 2;
	m_uiIndices[3] = 2;
	m_uiIndices[4] = 1;
	m_uiIndices[5] = 3;
}

//-------------------------------------------------------------------------------
void TSurface2DMesh::AddSprite(TTexture* texture, const TVector2& position, const TVector4& texCoords, float rotation, float scaleX, float scaleY)
{
	// TODO: better alternative to this lazy init?
	if (m_mesh == NULL)
	{
		SetupVertices();
	}

	// transform on CPU
	g_matWorld.SetIdentity();

	// insert scale, and rotation if valid
	if (rotation == 0.f)
	{
		g_matWorld[0].Set(scaleX, 0.f, 0.f, 0.f);
		g_matWorld[1].Set(0.f, scaleY, 0.f, 0.f);
		g_matWorld[2].Set(0.f, 0.f, 128.f, 0.f);
	}
	else
	{
		float sinAngle = 1.f;
		float cosAngle = 1.f;

		SinCos(rotation, sinAngle, cosAngle);

		g_matWorld[0].Set(scaleX * cosAngle, scaleX * sinAngle, 0.f, 0.f);
		g_matWorld[1].Set(scaleY * -sinAngle, scaleY * cosAngle, 0.f, 0.f);
		g_matWorld[2].Set(0.f, 0.f, 128.f, 0.f);
	}

	// insert translation
	g_matWorld[3][0] = position.x + scaleX * 0.5f;
	g_matWorld[3][1] = (-1 * position.y) - scaleY * 0.5f;
	g_matWorld[3][2] = 0.f;
	g_matWorld[3][3] = 1.f;

	m_uiVertices[0].position.Set(-0.5f, 0.5f, 0.f);
	m_uiVertices[1].position.Set(0.5f, 0.5f, 0.f);
	m_uiVertices[2].position.Set(-0.5f, -0.5f, 0.f);
	m_uiVertices[3].position.Set(0.5f, -0.5f, 0.f);

	g_matWorld.TransformVector(&m_uiVertices[0].position);
	g_matWorld.TransformVector(&m_uiVertices[1].position);
	g_matWorld.TransformVector(&m_uiVertices[2].position);
	g_matWorld.TransformVector(&m_uiVertices[3].position);

	m_uiVertices[0].texture.Set(texCoords.x, texCoords.y);
	m_uiVertices[1].texture.Set(texCoords.z, texCoords.y);
	m_uiVertices[2].texture.Set(texCoords.x, texCoords.w);
	m_uiVertices[3].texture.Set(texCoords.z, texCoords.w);

    TUIVertexCache* cache = GetVertexCache(texture->GetId());

    cache->AddVertexData(&(m_uiVertices[0]), 4, &(m_uiIndices[0]), 6);
}

//-------------------------------------------------------------------------------
void TSurface2DMesh::Render()
{
	for (unsigned int index = 0; index < m_vertexCaches.GetSize(); index++)
	{
        if (m_vertexCaches[index]->GetNumVertices() > 0)
        {
			m_mesh->SetVertices(m_vertexCaches[index]->GetVertexData(), m_vertexCaches[index]->GetNumVertices());
			m_mesh->SetIndices(m_vertexCaches[index]->GetIndexData(), m_vertexCaches[index]->GetNumIndices());
			m_mesh->SetSkin(m_vertexCaches[index]->GetSkin());

            TLocator::GetRenderer()->DrawMesh(TMatrix::GetIdentity(), *m_mesh);

            m_vertexCaches[index]->Clear();
        }
	}
}

//-------------------------------------------------------------------------------
TUIVertexCache* TSurface2DMesh::GetVertexCache(const TString& textureId)
{
    TUIVertexCache* result = NULL;

    for (unsigned int index = 0; index < m_vertexCaches.GetSize(); index++)
    {
        if (m_vertexCaches[index]->GetId() == textureId)
        {
            result = m_vertexCaches[index];
            break;
        }
    }

    if (result == NULL)
    {
        result = TNew TUIVertexCache(textureId.GetPointer());

        m_vertexCaches.Add(result);
    }

    return result;
}
