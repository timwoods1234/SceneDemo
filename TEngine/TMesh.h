#ifndef __TMESH_H__
#define __TMESH_H__

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

#ifndef __TSUBMESHINFO_H__
#include "TSubMeshInfo.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TAABB_H__
#include "TAABB.h"
#endif

class TMeshBufferInterface;
class TShader;
class TMatrix;

class TMesh : public TRefCountedObject
{
public:
	static TMesh* Acquire(const char* id = NULL);

	static void Release(TMesh* mesh);

	~TMesh();

	TShader* GetShader() const;

	unsigned int GetSubMeshCount() const;

	const TSubMeshInfo* GetSubMeshInfo(unsigned int index) const;

	const TMeshBufferInterface* GetMeshBuffer() const;

	const TAABB& GetBoundingBox() const;

	void SetShader(TShader* shader);

	void SetShaderByName(const char* shaderId);

	void SetVertices(const void* vertices, unsigned int numVertices);

	void SetIndices(const unsigned short* indices, unsigned int numIndices);

	void SetIndices(const unsigned short* indices, unsigned int numIndices, const TDynamicSet<TSubMeshInfo>& info);

	void SetSkin(TSkin* skin, unsigned int subMeshIndex = 0);

	TSkin* GetSkin(unsigned int index) const;

	void ComputeBounds(const void* vertices, unsigned int numVertices);

	void MarkDynamic();

	void SetSharedMesh(TMesh* sharedMesh);

	const TMesh* GetSharedMesh() const;

private:
	TMesh();

	friend class TResourceManager;

	static TRefCountedObject* Load(const char* path);

	static void Unload(TRefCountedObject* toDelete);

	void ReziseSubmeshCount(unsigned int count);

	void CopySubsetInfo(const TDynamicSet<TSubMeshInfo>& info);

	void Clear();

	TMesh* m_sharedMesh;

	TDynamicSet<TSubMeshInfo> m_submeshEntries;

	TMeshBufferInterface* m_buffer;

	TShader* m_shader;

	TAABB m_aabb;
};

#endif
