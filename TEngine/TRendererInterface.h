#ifndef __TRENDERERINTERFACE_H__
#define __TRENDERERINTERFACE_H__

// Interface for the rendering component.

#ifndef __TRENDERSTATE_H__
#include "TRenderState.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

class TMatrix;
class TCamera;
class TShader;
class TMesh;
class TVertexFormat;
class TTexture;
class TRenderQueueManager;
class TEntity;

class TRendererInterface
{
public:
	TRendererInterface();
	virtual ~TRendererInterface();

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void SetDepthBufferMode(TDepthState state) = 0;
	virtual void SetShadeMode(TShadeState smd, float f) = 0;
	virtual void SetAlphaBlending(bool bEnable) = 0;
	virtual void SetZFunc(TZCompareState smd) = 0;
	virtual void SetCullMode(TCullMode mode) = 0;

	virtual void Draw2D(TTexture* texture, const TVector2& position, const TVector4& texCoords, float rotation =0.f, float scaleX =1.f, float scaleY =1.f) = 0;
	virtual void DrawLineList(const TMesh& mesh) = 0;
	virtual void DrawLineStrip(const TMesh& mesh) = 0;
	virtual void DrawMesh(const TMatrix& matWorld, const TMesh& mesh) = 0;

	virtual TVertexFormat* GetVertexFormat(const TString& name) = 0;

	void FlushRenderQueue();
	void AddToRenderQueue(const TEntity* entity, const TMesh* mesh);

	TShadeState GetShadeMode() const;

	void SetCurrentCamera(TCamera* camera);
	TCamera* GetCurrentCamera() const;

protected:
	virtual void ActivateShader(TShader* shader) = 0;

	TCamera* m_currentCamera;
	TShader* m_activeShader;

	TDepthState m_depthState;
	TShadeState m_shadeState;
	TZCompareState m_compareState;
	TCullMode m_cullMode;
};

#endif