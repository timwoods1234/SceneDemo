#ifndef __GRASSBATCHER_H__
#define __GRASSBATCHER_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

class GrassBatcher : public TEventListener,
					 public TSingleton<GrassBatcher>
{
public:
	GrassBatcher();

	~GrassBatcher();

	void Clear();

	void RebuildMesh();

	void AddGrassPosition(const TVector3& position);

	void OnRender();

private:
	TMesh* m_grassMesh;

	TDynamicSet<TVector3> m_grassPositions;

	TTexture* m_grassTexture;

	TShader* m_grassShader;

	float m_timer;
};

#endif
