#ifndef __TD3DDEVICE_H__
#define __TD3DDEVICE_H__

// Wrapper for Direct3D Device

#ifndef __TPLATFORM_H__
#include "TPlatform.h"
#endif

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

class TD3DMeshBuffer;

class TD3DDevice
{
public:
	TD3DDevice(HWND window);

	~TD3DDevice();

	LPDIRECT3DDEVICE9 GetDevice() const;

	bool BeginRendering(bool clearPixel, bool clearDepth, bool clearStencil);

	void EndRendering();

	void SetMeshBuffer(const TD3DMeshBuffer* buffer);

	void DrawIndexedPrimitive(unsigned int numVertices, unsigned int startIndex, unsigned int numIndices);

	void DrawLineList(unsigned int numVertices);

	void DrawLineStrip(unsigned int numVertices);

private:
	bool InitDevice(HWND window, int width, int height, int minDepth = 1, bool windowed = true, int minStencil = 0);

	bool OneTimeInit();

	void Release();

	void SetClearColor(float red, float green, float blue);

	bool Clear(bool clearPixel, bool clearDepth, bool clearStencil);

	void OnDeviceLost();
	bool IsDeviceLost();
	void ResetDevice();

	bool m_running;
	bool m_windowed;
	bool m_isSceneRunning;
	bool m_stencil;

	LPDIRECT3DDEVICE9		m_device;
	LPDIRECT3D9				m_direct3D;
	D3DPRESENT_PARAMETERS	m_d3dpp;
	D3DSURFACE_DESC			m_d3dBackBuffer;
	D3DCOLOR				m_clearColor;
};

#endif
