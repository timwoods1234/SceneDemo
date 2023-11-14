#ifndef __TAIMESHLOADER_H__
#define __TAIMESHLOADER_H__

#if TENGINE_USE_AIMESH

#ifndef __TMESHLOADERINTERFACE_H__
#include "TMeshLoaderInterface.h"
#endif

#ifndef __TMESH_H__
#include "TMesh.h"
#endif

#ifndef __TVERTEX_H__
#include "TVertex.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TMATERIAL_H__
#include "TMaterial.h"
#endif

struct aiMaterial;
struct aiMesh;
struct aiScene;
class TSkin;
class TTexture;

class TAIMeshLoader : public TMeshLoaderInterface
{
public:
	TAIMeshLoader();

	~TAIMeshLoader();

	bool LoadMeshFromFile(const char* filename, TMesh& mesh);

private:
	void InitFromScene(const aiScene* scene, const char* filename, TMesh& mesh);

	TSkin* LoadSkin(aiMaterial* material, const char* filename, unsigned int subMeshIndex);

	TMaterial LoadMaterial(aiMaterial* material);

	TString GetTextureFilename(aiMaterial* material, const char* filename);

	void LoadVertices(TDynamicSet<TVertex>& vertices, const aiMesh* aiMesh);

	void LoadIndices(TDynamicSet<unsigned short>& indices, unsigned int baseVertexIndex, const aiMesh* aiMesh);
};

#endif // #if TENGINE_USE_AIMESH

#endif
