#ifndef __TDEBUGRENDERER_H__
#define __TDEBUGRENDERER_H__

#ifndef __TCOLOR_H__
#include "TColor.h"
#endif

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TVERTEX_H__
#include "TVertex.h"
#endif

#ifndef __TSINGLETON_H__
#include "TSingleton.h"
#endif

#ifndef __TMESH_H__
#include "TMesh.h"
#endif

#ifndef __TDEBUGRENDERENTRIES_H__
#include "TDebugRenderEntries.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

class TShader;
class TScreenOutputStream;

class TDebugRenderer : public TSingleton<TDebugRenderer>,
					   public TEventListener
{
public:
	TDebugRenderer();

	~TDebugRenderer();

	void AddLine(const TVector3& start, const TVector3& end, const TColor& color, float duration);

	void AddCube(const TVector3& min, const TVector3& max, const TColor& color, float duration);

	void AddSphere(const TVector3& middle, float radius, const TColor& color, float duration);

	void AddText(const char* text, const TColor& color, float duration);

	void DrawLine(const TVector3& start, const TVector3& end);

	void DrawCube(const TVector3& min, const TVector3& max);

	void DrawSphere(const TVector3& middle, float radius);

	void DrawTextLine(const char* text, int x, int y, const TColor& color);

	void SetColor(const TColor& color);

protected:

	void OnUpdate();

	void OnRender();

	void OnRenderUI();

private:

	void Initialize();

	TDynamicSet<TDebugRenderEntry> m_renderEntries;

	TDynamicSet<TDebugTextEntry> m_textEntries;

	bool m_initialized;

	TMesh* m_mesh;

	TColor m_color;

	TScreenOutputStream* m_screenOutputStream;
};

#endif
