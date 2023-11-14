#ifndef __TGRAPHICSFACTORYINTERFACE_H__
#define __TGRAPHICSFACTORYINTERFACE_H__

class TTexture;
class TShader;
class TFont;
class TMeshBufferInterface;
class TVertexFormat;

class TGraphicsFactoryInterface
{
public:
	TGraphicsFactoryInterface() {}

	virtual ~TGraphicsFactoryInterface() {}

	virtual bool LoadTexture(const char* filename, TTexture* outputTexture) = 0;
	virtual bool LoadCubeTexture(const char* filename, TTexture* outputTexture) = 0;
	virtual void UnloadTexture(TTexture& texture) = 0;
	
	virtual TShader* CreateShader(const char* filename) = 0;
	virtual void UnloadShader(TShader* shader) = 0;

    virtual TFont* CreateTFont(const char* filename) = 0;
    virtual void UnloadFont(TFont* font) = 0;

	virtual TMeshBufferInterface* CreateMeshBuffer(const char* vertexTypeName) = 0;
	virtual void UnloadMeshBuffer(TMeshBufferInterface* entry) = 0;
};

#endif
