#ifndef __TSURFACE2DMESH_H__
#define __TSURFACE2DMESH_H__

#ifndef __TSURFACE2D_H__
#include "TSurface2D.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

struct TVertexUI;
class TMesh;
class TUIVertexCache;

class TSurface2DMesh :  public TSurface2D,
						public TEventListener
{
public:
	TSurface2DMesh();

	~TSurface2DMesh();

	void AddSprite(TTexture* texture, const TVector2& position, const TVector4& texCoords, float rotation =0.f, float scaleX =1.f, float scaleY =1.f);
	
	void Render();

private:
	void SetupVertices();

    TUIVertexCache* GetVertexCache(const TString& textureId);

	TVertexUI* m_uiVertices;

	unsigned short* m_uiIndices;

    TMesh* m_mesh;

    TDynamicSet<TUIVertexCache*> m_vertexCaches;
};

#endif