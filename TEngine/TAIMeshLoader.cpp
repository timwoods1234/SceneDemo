#if TENGINE_USE_AIMESH

#pragma comment(lib, "assimp.lib")
#include <Importer.hpp>  // C++ importer interface
#include <scene.h>       // Output data structure
#include <postprocess.h> // Post processing flags

#include "TAIMeshLoader.h"
#include "TUtil.h"
#include "TSkin.h"
#include "TTexture.h"

//-------------------------------------------------------------------------------
TAIMeshLoader::TAIMeshLoader()
{
}

//-------------------------------------------------------------------------------
TAIMeshLoader::~TAIMeshLoader()
{
}

//-------------------------------------------------------------------------------
bool TAIMeshLoader::LoadMeshFromFile(const char* filename, TMesh& mesh)
{
    Assimp::Importer Importer;

	unsigned int pFlags = aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded;

	const aiScene* scene = Importer.ReadFile(filename, pFlags);

	if (scene)
	{
		InitFromScene(scene, filename, mesh);

		return true;
	}
	else
	{
		TDebugPrint(("[TMeshDefinition::LoadMeshFromFile] Failed to load %s", filename));

		return false;
	}
}

//-------------------------------------------------------------------------------
void TAIMeshLoader::InitFromScene(const aiScene* scene, const char* filename, TMesh& mesh)
{
	TString filepath = TUtil::GetFilePath(filename);

	TDynamicSet<TVertex> vertices(0, 1024);
	TDynamicSet<unsigned short> indices(0, 1024);
	TDynamicSet<TSubMeshInfo> subMeshEntries;
	TDynamicSet<TSkin*> skins;

	for (unsigned int entryIndex = 0; entryIndex < scene->mNumMeshes; entryIndex++)
	{
		TSubMeshInfo subMeshInfo;
		const aiMesh* aiMesh = scene->mMeshes[entryIndex];

		int startVertex = vertices.GetSize();
		LoadVertices(vertices, aiMesh);
		int vertexCount = vertices.GetSize() - startVertex;

		int startIndex = indices.GetSize();
		LoadIndices(indices, startVertex, aiMesh);
		int indexCount = indices.GetSize() - startIndex;

		unsigned int sceneMaterialIndex = aiMesh->mMaterialIndex;
		TSkin* skin = LoadSkin(scene->mMaterials[sceneMaterialIndex], filepath.GetPointer(), entryIndex);

		subMeshInfo.numIndices = indexCount;
		subMeshInfo.startIndex = startIndex;
		subMeshEntries.Add(subMeshInfo);

		skins.Add(skin);
	}

	mesh.SetVertices( &(vertices[0]), vertices.GetSize());
	mesh.SetIndices( &(indices[0]), indices.GetSize(), subMeshEntries);
	mesh.ComputeBounds(&(vertices[0]), vertices.GetSize());

	for (unsigned int index = 0; index < skins.GetSize(); index++)
	{
		mesh.SetSkin(skins[index], index);

		TSkin::Release(skins[index]);
	}
}

//-------------------------------------------------------------------------------
TSkin* TAIMeshLoader::LoadSkin(aiMaterial* material, const char* filename, unsigned int subMeshIndex)
{
	TString skinId = TString::Format("%s_%d", filename, subMeshIndex);

	TSkin* result = TSkin::Acquire(skinId.GetPointer());

	result->SetMaterial(LoadMaterial(material));
	result->AddTexture("gTex", GetTextureFilename(material, filename).GetPointer());

	return result;
}

//-------------------------------------------------------------------------------
TMaterial TAIMeshLoader::LoadMaterial(aiMaterial* material)
{
	TMaterial result;

	aiColor3D diffuse(0.f,0.f,0.f);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);

	aiColor3D ambient(0.f,0.f,0.f);
	material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);

	aiColor3D specular(0.f,0.f,0.f);
	material->Get(AI_MATKEY_COLOR_SPECULAR, ambient);

	aiColor3D emissive(0.f,0.f,0.f);
	material->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);

	result.diffuseColor.Set(diffuse.r, diffuse.g, diffuse.b, 1.0f);
	result.ambientColor.Set(ambient.r, ambient.g, ambient.b, 1.0f);
	result.specularColor.Set(specular.r, specular.g, specular.b, 1.0f);
	result.emissiveColor.Set(emissive.r, emissive.g, emissive.b, 1.0f);

	result.power = 1.0f;

	return result;
}

//-------------------------------------------------------------------------------
TString TAIMeshLoader::GetTextureFilename(aiMaterial* material, const char* filename)
{
	TString result;

	if (material->GetTextureCount(aiTextureType_DIFFUSE))
	{
		aiString Path;

		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			result = TString::Format("%s%s", filename, Path.data);
		}
	}
	else
	{
		result = c_defaultTexturePath;
	}

	return result;
}

//-------------------------------------------------------------------------------
void TAIMeshLoader::LoadVertices(TDynamicSet<TVertex>& vertices, const aiMesh* aiMesh)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	unsigned int numVertices = aiMesh->mNumVertices;

	for (unsigned int vertIndex = 0 ; vertIndex < numVertices; vertIndex++)
	{
		const aiVector3D* pos = &(aiMesh->mVertices[vertIndex]);
		const aiVector3D* normal = &(aiMesh->mNormals[vertIndex]);
		const aiVector3D* texCoord = aiMesh->HasTextureCoords(0) ? &(aiMesh->mTextureCoords[0][vertIndex]) : &Zero3D;

		TVertex v(
			TVector3(pos->x, pos->y, pos->z), 
			TVector3(normal->x, normal->y, normal->z), 
			TVector2(texCoord->x, texCoord->y));

		vertices.Add(v);
	}
}

//-------------------------------------------------------------------------------
void TAIMeshLoader::LoadIndices(TDynamicSet<unsigned short>& indices, unsigned int baseVertexIndex, const aiMesh* aiMesh)
{
	unsigned int numFaces = aiMesh->mNumFaces;

	for (unsigned int index = 0; index < numFaces; index++)
	{
		const aiFace& face = aiMesh->mFaces[index];

		TASSERT((face.mNumIndices == 3), "[TMeshDefinition::LoadIndices] Failed to build index buffer");

		indices.Add(face.mIndices[0] + baseVertexIndex);
		indices.Add(face.mIndices[1] + baseVertexIndex);
		indices.Add(face.mIndices[2] + baseVertexIndex);
	}
}

#endif // #if TENGINE_USE_AIMESH