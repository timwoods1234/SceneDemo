#include "TMesh.h"
#include "TLocator.h"
#include "TGraphicsFactoryInterface.h"
#include "TShader.h"
#include "TVertexFormat.h"
#include "TResourceManager.h"
#include "TMeshBufferInterface.h"
#include "TMeshLoaderInterface.h"
#include "TRendererInterface.h"
#include "TSkin.h"

//-------------------------------------------------------------------------------
TMesh* TMesh::Acquire(const char* id)
{
	if (id == NULL)
	{
		TMesh* mesh = TNew TMesh();
		mesh->AddRef();

		return mesh;
	}

	TString idLeaf = id;

	int indexOfSlash = idLeaf.IndexOf('/');

	if (indexOfSlash != -1)
	{
		idLeaf = idLeaf.SubString(indexOfSlash + 1);
	}

	TString filename = TString::Format("Assets/3D/%s/%s.x", id, idLeaf.GetPointer());

	TMesh* result = TNew TMesh();
	result->SetShaderByName("StandardTex");

	TMesh* sharedMesh = (TMesh*)TResourceManager::Get()->Allocate(ResourceType_Mesh, filename.GetPointer());
	result->SetSharedMesh(sharedMesh);

	return result;
}

//-------------------------------------------------------------------------------
void TMesh::Release(TMesh* mesh)
{
	if (mesh != NULL)
	{
		TMesh* sharedMesh = mesh->m_sharedMesh;

		if (sharedMesh != NULL)
		{
			TResourceManager::Get()->Release(ResourceType_Mesh, sharedMesh);

			TSafeDelete(mesh);
		}
		else
		{
			TResourceManager::Get()->Release(ResourceType_Mesh, mesh);
		}
	}
}

//-------------------------------------------------------------------------------
TMesh::TMesh()
:	m_sharedMesh(NULL),
	m_shader(NULL),
	m_buffer(NULL)
{
}

//-------------------------------------------------------------------------------
TMesh::~TMesh()
{
	Clear();

	SetSharedMesh(NULL);

	SetShader(NULL);
}

//-------------------------------------------------------------------------------
TShader* TMesh::GetShader() const
{
	return m_shader;
}

//-------------------------------------------------------------------------------
const TMeshBufferInterface* TMesh::GetMeshBuffer() const
{
	return m_buffer;
}

//-------------------------------------------------------------------------------
const TAABB& TMesh::GetBoundingBox() const
{
	return m_aabb;
}

//-------------------------------------------------------------------------------
unsigned int TMesh::GetSubMeshCount() const
{
	return m_submeshEntries.GetSize();
}

//-------------------------------------------------------------------------------
const TSubMeshInfo* TMesh::GetSubMeshInfo(unsigned int index) const
{
	if (index >= 0 && index < m_submeshEntries.GetSize())
	{
		return &m_submeshEntries[index];
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TMesh::ComputeBounds(const void* vertices, unsigned int numVertices)
{
	m_aabb.Clear();

	if (m_shader != NULL)
	{
		unsigned int stride = m_shader->GetVertexFormat()->GetStride();
		TVector3 point;
		float* position;

		for (unsigned int index = 0; index < numVertices; index++)
		{
			position = (float*)vertices;
			position += index * (stride / 4);

			point.Set(position[0], position[1], position[2]);

			m_aabb.AddPoint(point);
		}
	}
}

//-------------------------------------------------------------------------------
void TMesh::SetVertices(const void* vertices, unsigned int numVertices)
{
	m_buffer->SetVertices(vertices, numVertices);
	
	ReziseSubmeshCount(1);
}

//-------------------------------------------------------------------------------
void TMesh::SetIndices(const unsigned short* indices, unsigned int numIndices)
{
	m_buffer->SetIndices(indices, numIndices);

	ReziseSubmeshCount(1);

	m_submeshEntries[0].startIndex = 0;
	m_submeshEntries[0].numIndices = numIndices;
}

//-------------------------------------------------------------------------------
void TMesh::SetIndices(const unsigned short* indices, unsigned int numIndices, const TDynamicSet<TSubMeshInfo>& info)
{
	m_buffer->SetIndices(indices, numIndices);

	CopySubsetInfo(info);
}

//-------------------------------------------------------------------------------
void TMesh::MarkDynamic()
{
	m_buffer->MarkDynamic();
}

//-------------------------------------------------------------------------------
TRefCountedObject* TMesh::Load(const char* path)
{
	TMesh* result = TNew TMesh();
	result->SetShaderByName("StandardTex");

	if (!TLocator::GetMeshLoader()->LoadMeshFromFile(path, *result))
	{
		TDebugPrint(("[TMesh::Load] Failed to load %s", path));

		TSafeDelete(result);
	}

	return result;
}

//-------------------------------------------------------------------------------
void TMesh::Unload(TRefCountedObject* toDelete)
{
	TMesh* mesh = static_cast<TMesh*>(toDelete);

	TSafeDelete(mesh);
}

//-------------------------------------------------------------------------------
const TMesh* TMesh::GetSharedMesh() const
{
	return m_sharedMesh;
}

//-------------------------------------------------------------------------------
void TMesh::SetSharedMesh(TMesh* sharedMesh)
{
	m_sharedMesh = sharedMesh;

	if (sharedMesh != NULL)
	{
		CopySubsetInfo(sharedMesh->m_submeshEntries);

		m_id = sharedMesh->m_id;

		m_aabb = sharedMesh->m_aabb;
	}
}

//-------------------------------------------------------------------------------
void TMesh::SetSkin(TSkin* skin, unsigned int subMeshIndex)
{
	if (subMeshIndex >= m_submeshEntries.GetSize())
	{
		ReziseSubmeshCount(subMeshIndex + 1);
	}

	if (m_submeshEntries[subMeshIndex].skin != NULL)
	{
		TSkin::Release(m_submeshEntries[subMeshIndex].skin);
	}

	m_submeshEntries[subMeshIndex].skin = skin;

	if (m_submeshEntries[subMeshIndex].skin != NULL)
	{
		m_submeshEntries[subMeshIndex].skin->AddRef();
	}
}

//-------------------------------------------------------------------------------
void TMesh::ReziseSubmeshCount(unsigned int count)
{
	while (m_submeshEntries.GetSize() < count)
	{
		TSubMeshInfo info;
		m_submeshEntries.Add(info);
	}
}

//-------------------------------------------------------------------------------
void TMesh::CopySubsetInfo(const TDynamicSet<TSubMeshInfo>& info)
{
	unsigned int subMeshCount = info.GetSize();
	const TSubMeshInfo* existingInfo = NULL;

	ReziseSubmeshCount(subMeshCount);

	for (unsigned int index = 0; index < subMeshCount; index++)
	{
		existingInfo = &(info[index]);

		m_submeshEntries[index].numIndices = existingInfo->numIndices;
		m_submeshEntries[index].startIndex = existingInfo->startIndex;

		m_submeshEntries[index].skin = existingInfo->skin;

		if (m_submeshEntries[index].skin != NULL)
		{
			m_submeshEntries[index].skin->AddRef();
		}
	}
}

//-------------------------------------------------------------------------------
void TMesh::Clear()
{
	for (unsigned int index = 0; index < m_submeshEntries.GetSize(); index++)
	{
		TSkin::Release(m_submeshEntries[index].skin);
	}
}

//-------------------------------------------------------------------------------
TSkin* TMesh::GetSkin(unsigned int index) const
{
	if (index >= 0 && index < m_submeshEntries.GetSize())
	{
		return m_submeshEntries[index].skin;
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TMesh::SetShader(TShader* shader)
{
	if (shader == NULL || (m_shader != NULL && shader->GetVertexFormat()->GetId() != m_shader->GetVertexFormat()->GetId()))
	{
		// TODO: convert to vertex format instead, to preserve vertex data
		TLocator::GetGraphicsFactory()->UnloadMeshBuffer(m_buffer);

		m_buffer = NULL;
	}

	if (m_shader != NULL)
	{
		TShader::Release(m_shader);
	}

	m_shader = shader;

	if (m_shader != NULL)
	{
		m_shader->AddRef();

		if (m_buffer == NULL)
		{
			if (m_shader->GetVertexFormat() != NULL)
			{
				m_buffer = TLocator::GetGraphicsFactory()->CreateMeshBuffer(m_shader->GetVertexFormat()->GetId().GetPointer());
			}
		}
	}
}

//-------------------------------------------------------------------------------
void TMesh::SetShaderByName(const char* shaderId)
{
	TShader* shader = TShader::Acquire(shaderId);

	if (shader != NULL)
	{
		SetShader(shader);
	}

	TShader::Release(shader);
}
