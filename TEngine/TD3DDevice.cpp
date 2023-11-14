#include "TD3DDevice.h"
#include "TWindowsApplication.h"
#include "TError.h"
#include "TD3DUtil.h"
#include "TD3DEventDeviceLost.h"
#include "TD3DEventDeviceReset.h"
#include "TConfig.h"
#include "TLocator.h"
#include "TD3DMeshBuffer.h"

//-------------------------------------------------------------------------------
TD3DDevice::TD3DDevice(HWND window)
{
	TD3DEventDeviceLost::Create();
	TD3DEventDeviceReset::Create();

	m_direct3D = NULL;
	m_device = NULL;
	m_clearColor = D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f);

	m_isSceneRunning = false;
	m_running = false;
	m_stencil = false;
	m_windowed = false;

	int width = (int)TConfig::Get()->GetScreenWidth();
	int height = (int)TConfig::Get()->GetScreenHeight();
	bool windowed = TConfig::Get()->IsWindowed();

	if (!InitDevice(window, width, height, 0, windowed))
	{
		TASSERT(false, "Failed to initialise graphics");
		TLocator::GetApplication()->Quit();
	}
}

//-------------------------------------------------------------------------------
TD3DDevice::~TD3DDevice()
{
	Release();

	TD3DEventDeviceLost::Destroy();
	TD3DEventDeviceReset::Destroy();
}

//-------------------------------------------------------------------------------
void TD3DDevice::Release()
{
	SafeRelease(m_device);
	SafeRelease(m_direct3D);
}

//-------------------------------------------------------------------------------
bool TD3DDevice::InitDevice(HWND window, int width, int height, int minDepth, bool windowed, int minStencil)
{
	SafeRelease(m_direct3D);

	m_direct3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!m_direct3D)
	{
		TDebugPrint(("[TD3DDevice::InitDevice] Unable to initialize Direct3D"));
		return false;
	}
	
	if (minStencil > 0)
	{
		m_stencil = true;
	}

	D3DDISPLAYMODE displayMode;
	bool capsAvailable = TD3DUtil::CheckHardwareSupport(m_direct3D, displayMode);

	if (!capsAvailable)
	{
		TDebugPrint(("[TD3DDevice::InitDevice] Device caps unavailable"));
		return false;
	}

	// Set up present parameters
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

	m_d3dpp.BackBufferWidth			= width;
	m_d3dpp.BackBufferHeight		= height;
	m_d3dpp.BackBufferFormat		= displayMode.Format;
	m_d3dpp.BackBufferCount			= 1;
	m_d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;
	m_d3dpp.MultiSampleQuality		= 0;
	m_d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	m_d3dpp.hDeviceWindow			= window;
	m_d3dpp.Windowed				= windowed;
	m_d3dpp.EnableAutoDepthStencil	= TRUE;
	m_d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	m_d3dpp.Flags					= 0;
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dpp.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;	//D3DPRESENT_INTERVAL_IMMEDIATE

	// Check for hardware T&L
	unsigned long flags = TD3DUtil::GetCreateFlags(m_direct3D);

	// Create the Device
	if (FAILED(m_direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, flags, &m_d3dpp, &m_device)))
	{
		TDebugPrint(("[TD3DDevice::InitDevice] Unable to create Device"));
		return false;
	}

    // Store render target surface desc
    LPDIRECT3DSURFACE9 backBuffer;

    m_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
    backBuffer->GetDesc(&m_d3dBackBuffer);

	SafeRelease(backBuffer);

	OneTimeInit();

	m_running = true;
	m_isSceneRunning = false;
	m_windowed = windowed;

	return true;
}

//-------------------------------------------------------------------------------
void TD3DDevice::ResetDevice()
{
	m_device->Reset(&m_d3dpp);
}

//-------------------------------------------------------------------------------
bool TD3DDevice::IsDeviceLost()
{
	HRESULT hr = m_device->TestCooperativeLevel();

	if (hr == D3D_OK)
	{
		return false;
	}

	if (hr == D3DERR_DEVICELOST)
	{	
		// Lost and can't be reset yet
		Sleep(20);
		return true;
	}

	else if (hr == D3DERR_DRIVERINTERNALERROR)
	{
		TASSERT(false, "Internal Driver Error ... Exiting");
		TLocator::GetApplication()->Quit();
		return true;
	}

	else if (hr == D3DERR_DEVICENOTRESET)
	{
		// The device is lost but can be reset and restored.
		OnDeviceLost();

		return false;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------
bool TD3DDevice::BeginRendering(bool clearPixel, bool clearDepth, bool clearStencil)
{
	if (IsDeviceLost())
	{
		OnDeviceLost();
		
		return false;
	}

	DWORD dw = 0;

	if (clearPixel)
	{ 
		dw |= D3DCLEAR_TARGET;
	}

	if (clearDepth) 
	{
		dw |= D3DCLEAR_ZBUFFER;
	}

	if (clearStencil && m_stencil)
	{
		dw |= D3DCLEAR_STENCIL; 
	}

	if (FAILED(m_device->Clear(0, NULL, dw, m_clearColor, 1.0f, 0)))
	{
		return false;
	}

	if (FAILED(m_device->BeginScene()))
	{
		return false;
	}

	m_isSceneRunning = true;

	return true;
}

//-------------------------------------------------------------------------------
bool TD3DDevice::Clear(bool clearPixel, bool clearDepth, bool clearStencil)
{
	DWORD dw = 0;

	if (clearPixel)
	{
		dw |= D3DCLEAR_TARGET; 
	}

	if (clearDepth)
	{ 
		dw |= D3DCLEAR_ZBUFFER; 
	}

	if (clearStencil && m_stencil)
	{
		dw |= D3DCLEAR_STENCIL;
	}

	if (m_isSceneRunning)
	{
		m_device->EndScene();
	}

	if (FAILED(m_device->Clear(0, NULL, dw, m_clearColor, 1.0f, 0)))
	{
		return false;
	}

	if (m_isSceneRunning)
	{
		m_device->BeginScene();
	}

	return true;
}

//-------------------------------------------------------------------------------
void TD3DDevice::EndRendering()
{
	if (FAILED(m_device->EndScene()))
	{
		TDebugPrint(("[TD3DDevice::EndRendering] End Scene failed"));
	}

	if (FAILED(m_device->Present(NULL, NULL, NULL, NULL)))
	{
		TDebugPrint(("[TD3DDevice::EndRendering] Present failed"));
	}

	m_isSceneRunning = false;
}

//-------------------------------------------------------------------------------
void TD3DDevice::SetClearColor(float red, float green, float blue)
{
	m_clearColor = D3DCOLOR_COLORVALUE(red, green, blue, 1.0f);
}

//-------------------------------------------------------------------------------
bool TD3DDevice::OneTimeInit()
{
	//Turn on back face culling
    m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//Turn on Depth Buffering
	m_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	m_device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	m_device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//Lighting, Color and Blending
	m_device->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	SetClearColor(0.35f, 0.35f, 0.35f);

	//Activate texture filtering
	m_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	return true;
}

//-------------------------------------------------------------------------------
void TD3DDevice::OnDeviceLost()
{
	TD3DEventDeviceLost::Get()->Execute();

	ResetDevice();

	TD3DEventDeviceReset::Get()->Execute();
}

//-------------------------------------------------------------------------------
LPDIRECT3DDEVICE9 TD3DDevice::GetDevice() const
{
	return m_device;
}

//-------------------------------------------------------------------------------
void TD3DDevice::SetMeshBuffer(const TD3DMeshBuffer* buffer)
{
	if (FAILED(m_device->SetStreamSource(0, buffer->GetVertexBuffer(), 0, buffer->GetStride())))
	{
		TDebugPrint(("set source failure"));
	}

	if (FAILED(m_device->SetIndices(buffer->GetIndexBuffer())))
	{
		TDebugPrint(("set indices failure"));
	}
}

//-------------------------------------------------------------------------------
void TD3DDevice::DrawIndexedPrimitive(unsigned int numVertices, unsigned int startIndex, unsigned int numIndices)
{
	if (FAILED(m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numVertices, startIndex, numIndices / 3)))
	{
		TDebugPrint(("DIP faliure"));
	}
}

//-------------------------------------------------------------------------------
void TD3DDevice::DrawLineList(unsigned int numVertices)
{
	m_device->DrawPrimitive(D3DPT_LINELIST, 0, numVertices);
}

//-------------------------------------------------------------------------------
void TD3DDevice::DrawLineStrip(unsigned int numVertices)
{
	m_device->DrawPrimitive(D3DPT_LINESTRIP, 0, numVertices);
}