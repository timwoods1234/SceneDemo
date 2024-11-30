#ifndef __TERRAIN_H__
#define __TERRAIN_H__

// TODO: rename height to depth

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

#ifndef __FRACTALDATA_H__
#include "FractalData.h"
#endif 

struct TVertex;

class Terrain : public TEventListener, public TXMLObject
{
public:
	Terrain();

	~Terrain();

	void Render();

	float GetHeight(float x, float z) const;

	TXMLObject* HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);

	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);

	void FinaliseLoad();

	void Write(TXMLWriter& writer);

private:
	void BuildGeometry();

	void BuildSubMesh(const TVertex* vertices, TSkin* skin, int left, int right, int top, int bottom);

	TDynamicSet<TMesh*> m_submeshes;

	FractalData m_mapData;

	bool m_drawSubgridBounds;

	int m_width;
	int m_depth;
	int m_subGridCount;
	float m_subGridScale;
	float m_heightScale;

	TTexture* m_texture0;
	TTexture* m_texture1;
	TTexture* m_texture2;
	TTexture* m_blendMap;
};

#endif
