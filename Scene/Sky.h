#ifndef __SKY_H__
#define __SKY_H__

#ifndef __TENGINEINCLUDED_H__
#include "TEngine.h"
#endif

class Sky : public TEventListener
{
public:
	Sky();

	~Sky();

	void OnRender();

private:
	TMesh* m_sphereMesh;
	TTexture* m_cubeMap;
};

#endif
