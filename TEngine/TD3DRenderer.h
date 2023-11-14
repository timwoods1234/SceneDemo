#ifndef __TD3DRENDERER_H__
#define __TD3DRENDERER_H__

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifndef __TRENDERERINTERFACE_H__
#include "TRendererInterface.h"
#endif

class TD3DDevice;
class TD3DVertexFormatRegister;
class TSurface2DMesh;

class TD3DRenderer : public TRendererInterface
{
public:
	TD3DRenderer(HWND window);

	~TD3DRenderer();

	void BeginFrame();
	void EndFrame();
	void ActivateShader(TShader* shader);

	void SetDepthBufferMode(TDepthState state);
	void SetShadeMode(TShadeState smd, float f);
	void SetAlphaBlending(bool enable);
	void SetZFunc(TZCompareState smd);
	void SetCullMode(TCullMode mode);

	void DrawMesh(const TMatrix& matWorld, const TMesh& mesh);
	void Draw2D(TTexture* texture, const TVector2& position, const TVector4& texCoords, float rotation =0.f, float scaleX =1.f, float scaleY =1.f);
	void DrawLineList(const TMesh& mesh);
	void DrawLineStrip(const TMesh& mesh);

	TVertexFormat* GetVertexFormat(const TString& name);

private:
	TD3DDevice* m_d3dDevice;

	TD3DVertexFormatRegister* m_vertexFormatRegister;

	TSurface2DMesh* m_surfaceMesh;
};

#endif
