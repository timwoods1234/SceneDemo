#include "Terrain.h"
#include "Heightmap.h"
#include "GridGenerator.h"
#include "TVertex.h"
#include "ModelPlugin.h"

//-------------------------------------------------------------------------------
Terrain::Terrain()
:	m_drawSubgridBounds(false)

{
	TEventRender::Get()->Register(this, &Terrain::Render);

	TXMLReader reader("Assets/Data/Entity/Terrain.xml", *this);
}

//-------------------------------------------------------------------------------
Terrain::~Terrain()
{
	TTexture::Release(m_texture0);
	TTexture::Release(m_texture1);
	TTexture::Release(m_texture2);
	TTexture::Release(m_blendMap);

	for (unsigned int index = 0; index < m_submeshes.GetSize(); index++)
	{
		TMesh::Release(m_submeshes[index]);
	}

	TSafeDelete(m_heightmap);

	TEventRender::Get()->Unregister(this, &Terrain::Render);
}

//-------------------------------------------------------------------------------
void Terrain::Render()
{
	TMatrix identity = TMatrix::GetIdentity();
	unsigned int numSubmeshes = m_submeshes.GetSize();
	TCamera* currentCamera = TLocator::GetRenderer()->GetCurrentCamera();

	int numRendered = 0;

	if (m_drawSubgridBounds)
	{
		TAABB box;

		for (unsigned int index = 0; index < numSubmeshes; index++)
		{
			box = m_submeshes[index]->GetBoundingBox();

			TDebugRenderer::Get()->DrawCube(box.GetMin(), box.GetMax());
		}
	}

	for (unsigned int index = 0; index < numSubmeshes; index++)
	{
		if (currentCamera->IsVisible(m_submeshes[index]->GetBoundingBox()))
		{
			TLocator::GetRenderer()->DrawMesh(identity, *(m_submeshes[index]));
			numRendered++;
		}
	}
}

//-------------------------------------------------------------------------------
float Terrain::GetHeight(float x, float z) const
{
	float localX = (x + 0.5f * m_width) / m_subGridScale;
	float localZ = (z - 0.5f * m_depth) / -m_subGridScale;

	int row = (int)floorf(localX);
	int col = (int)floorf(localZ);

	float a = m_heightmap->GetHeight(row, col);
	float b = m_heightmap->GetHeight(row, col + 1);
	float c = m_heightmap->GetHeight(row + 1, col);
	float d = m_heightmap->GetHeight(row + 1, col + 1);

	float relativeCol = localZ - (float)col;
	float relativeRow = localX - (float)row;

	if (relativeRow < 1.f - relativeCol)
	{
		float uy = b - a;
		float vy = c - a;

		return a + relativeCol * uy + relativeRow * vy;
	}
	else
	{
		float uy = c - d;
		float vy = b - d;

		return d + (1.f - relativeCol) * uy + (1.f - relativeRow) * vy;
	}
}

//-------------------------------------------------------------------------------
void Terrain::BuildGeometry()
{
	int numVerts = m_width * m_depth;

	TDynamicArray<TVertex> verts;
	TDynamicArray<unsigned short> indices;

	GridGenerator::CreateGrid(verts, indices, m_width, m_depth, m_subGridScale, m_subGridScale);

	float totalWidth = m_subGridScale * (m_width - 1);
	float totalDepth = m_subGridScale * (m_depth - 1);

	float texX;
	float texY;

	for (unsigned int index = 0; index < verts.GetSize(); index++)
	{
		int col = index / m_width;
		int row = index % m_width;

		verts[index].position.y = m_heightmap->GetHeight(row, col);

		if (index < verts.GetSize() - m_width)
		{
			TVector3 tangent1 = TVector3(verts[index + 1].position.x, m_heightmap->GetHeight(row, col + 1), verts[index + 1].position.z) - verts[index].position;
			TVector3 tangent2 = TVector3(verts[index + m_width].position.x, m_heightmap->GetHeight(row + 1, col), verts[index + m_width].position.z) - verts[index].position;
			verts[index].normal = CrossProduct(tangent1, tangent2);
		}
		else
		{
			verts[index].normal = TVector3(0.f, 1.f, 0.f);
		}

		texX = verts[index].texture.x = (verts[index].position.x + (0.5f*totalWidth)) / totalWidth;
		texY = verts[index].texture.y = (verts[index].position.z - (0.5f*totalDepth)) / -totalDepth;
	}

	int subGridCount = m_subGridCount - 1;
	int subGridRows = (m_width-1) / subGridCount;
	int subGridCols = (m_depth-1) / subGridCount;

	TMaterial material;
	material.ambientColor.Set(1.0f, 1.0f, 1.0f, 1.0f);
	material.diffuseColor.Set(1.0f, 1.0f, 1.0f, 1.0f);
	material.emissiveColor.Set(1.0f, 1.0f, 1.0f, 1.0f);
	material.specularColor.Set(0.4f, 0.4f, 0.4f, 1.0f);
	material.power = 8.0f;

	TSkin* skin = TSkin::Acquire();
	skin->SetMaterial(material);

	for (int row = 0; row < subGridRows; row++)
	{
		for (int col = 0; col < subGridCols; col++)
		{
			BuildSubMesh(&verts[0], skin, col * subGridCount, (col + 1) * subGridCount, row * subGridCount, (row + 1) * subGridCount);
		}
	}

	TSkin::Release(skin);
}

//-------------------------------------------------------------------------------
void Terrain::BuildSubMesh(const TVertex* vertices, TSkin* skin, int left, int right, int top, int bottom)
{
	TMesh* mesh = TMesh::Acquire();
	mesh->SetShaderByName("Terrain");

	int width = right - left;
	int depth = bottom - top;

	int numVerts = (width+1) * (depth+1);
	TDynamicArray<TVertex> subGridVerts(numVerts);

	int index = 0;

	for (int y = top; y <= bottom; y++)
	{
		for (int x = left; x <= right; x++)
		{
			subGridVerts[index] = vertices[y * m_width + x];

			index++;
		}
	}

	int numSubgridIndices = width * depth * 2 * 3;
	TDynamicArray<unsigned short> subGridIndices(numSubgridIndices);

	index = 0;

	int numVertCols = width + 1;

	for (int y = 0; y < width; ++y)
	{
		for (int x = 0; x < depth; ++x)
		{
			subGridIndices[index]		= y			* numVertCols + x;
			subGridIndices[index + 1]	= y			* numVertCols + x + 1;
			subGridIndices[index + 2]	= (y + 1)	* numVertCols + x;

			subGridIndices[index + 3]	= (y + 1)	* numVertCols + x;
			subGridIndices[index + 4]	= y			* numVertCols + x + 1;
			subGridIndices[index + 5]	= (y + 1)	* numVertCols + x + 1;

			index += 6;
		}
	}

	mesh->SetVertices((void*)&(subGridVerts[0]), subGridVerts.GetSize());
	mesh->SetIndices(&subGridIndices[0], subGridIndices.GetSize());
	mesh->ComputeBounds((void*)&(subGridVerts[0]), subGridVerts.GetSize());
	mesh->SetSkin(skin);

	m_submeshes.Add(mesh);
}

//-------------------------------------------------------------------------------
TXMLObject* Terrain::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
	return NULL;
}

//-------------------------------------------------------------------------------
void Terrain::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_heightScale = TDataVariant::Find("heightScale", objects).GetFloat();

	m_subGridCount = TDataVariant::Find("subGridCount", objects).GetInt();
	m_subGridScale = TDataVariant::Find("subGridScale", objects).GetFloat();

	m_width = TDataVariant::Find("width", objects).GetInt();
	m_depth = TDataVariant::Find("depth", objects).GetInt();

	TString heightmapFilename = TDataVariant::Find("heightmap", objects).GetString();
	m_heightmap = TNew Heightmap(heightmapFilename.GetPointer(), m_heightScale, m_width, m_depth);

	TString tex0 = TDataVariant::Find("tex0", objects).GetString();
	TString tex1 = TDataVariant::Find("tex1", objects).GetString();
	TString tex2 = TDataVariant::Find("tex2", objects).GetString();
	TString blendMap = TDataVariant::Find("blendmap", objects).GetString();

	m_texture0 = TTexture::Acquire(tex0.GetPointer());
	m_texture1 = TTexture::Acquire(tex1.GetPointer());
	m_texture2 = TTexture::Acquire(tex2.GetPointer());

	m_blendMap = TTexture::Acquire(blendMap.GetPointer());
}

//-------------------------------------------------------------------------------
void Terrain::FinaliseLoad()
{
	BuildGeometry();

	TShader* terrainShader = TShader::Acquire("Terrain");
	terrainShader->SetTexture("gTex0", m_texture0);
	terrainShader->SetTexture("gTex1", m_texture1);
	terrainShader->SetTexture("gTex2", m_texture2);
	terrainShader->SetTexture("gBlendMap", m_blendMap);
	TShader::Release(terrainShader);
}

//-------------------------------------------------------------------------------
void Terrain::Write(TXMLWriter& writer)
{
}