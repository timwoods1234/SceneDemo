#ifndef __TD3DGraphicsFactory_H__
#define __TD3DGraphicsFactory_H__

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

#ifndef __TGRAPHICSFACTORYINTERFACE_H__
#include "TGraphicsFactoryInterface.h"
#endif

class TD3DGraphicsFactory : public TGraphicsFactoryInterface
{
public:
	TD3DGraphicsFactory(LPDIRECT3DDEVICE9 device);
	~TD3DGraphicsFactory();

	bool CreateTexture(int width, int height, TTexture* outputTexture);
	bool LoadTexture(const char* filename, TTexture* outputTexture);
	bool LoadCubeTexture(const char* filename, TTexture* outputTexture);
	void UnloadTexture(TTexture& texture);

	TShader* CreateShader(const char* filename);
	void UnloadShader(TShader* shader);

    TFont* CreateTFont(const char* filename);
    void UnloadFont(TFont* font);

	TMeshBufferInterface* CreateMeshBuffer(const char* vertexTypeName);
	void UnloadMeshBuffer(TMeshBufferInterface* entry);

private:
	LPDIRECT3DDEVICE9 m_device;
};

#endif
