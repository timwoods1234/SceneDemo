#include "TUIVertexCache.h"
#include "TTexture.h"
#include "TSkin.h"
#include "TMaterial.h"

//-------------------------------------------------------------------------------
TUIVertexCache::TUIVertexCache(const char* textureId)
:	m_numIndices(0),
    m_numVertices(0)
{
	TMaterial uiMaterial;

	uiMaterial.diffuseColor.Set(1.f, 1.f, 1.f, 1.f);
	uiMaterial.ambientColor.Set(0.f, 0.f, 0.f, 1.f);
	uiMaterial.specularColor.Set(0.f, 0.f, 0.f, 1.f);
	uiMaterial.emissiveColor.Set(0.f, 0.f, 0.f, 1.f);
	uiMaterial.power = 1.f;

	m_skin = TSkin::Acquire();
	m_skin->SetMaterial(uiMaterial);
	m_skin->AddTexture("gTex", textureId);

	m_id = textureId;
}

//-------------------------------------------------------------------------------
TUIVertexCache::~TUIVertexCache()
{
	TSkin::Release(m_skin);
}

//-------------------------------------------------------------------------------
void TUIVertexCache::AddVertexData(TVertexUI* vertices, unsigned int numVertices, unsigned short* indices, unsigned int numIndices)
{
    for (unsigned int index = 0; index < numVertices; index++)
    {
        m_vertices.Add(vertices[index]);
    }

    for (unsigned int index = 0; index < numIndices; index++)
    {
        m_indices.Add(indices[index] + m_numVertices);
    }

    m_numIndices += numIndices;
    m_numVertices += numVertices;
}

//-------------------------------------------------------------------------------
void TUIVertexCache::Clear()
{
    m_numIndices = 0;
    m_numVertices = 0;

    m_vertices.Clear();
    m_indices.Clear();
}

//-------------------------------------------------------------------------------
const void* TUIVertexCache::GetVertexData() const
{
    return (void*)&(m_vertices[0]);
}

//-------------------------------------------------------------------------------
const unsigned short* TUIVertexCache::GetIndexData() const
{
    return &(m_indices[0]);
}

//-------------------------------------------------------------------------------
unsigned int TUIVertexCache::GetNumIndices() const
{
    return m_numIndices;
}

//-------------------------------------------------------------------------------
unsigned int TUIVertexCache::GetNumVertices() const
{
    return m_numVertices;
}

//-------------------------------------------------------------------------------
const TString& TUIVertexCache::GetId() const
{
	return m_id;
}

//-------------------------------------------------------------------------------
TSkin* TUIVertexCache::GetSkin() const
{
	return m_skin;
}
