#include "TD3DUtil.h"

//-------------------------------------------------------------------------------
bool TD3DUtil::CheckHardwareSupport(LPDIRECT3D9 direct3D, D3DDISPLAYMODE& displayMode)
{
    if(FAILED(direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
	{
        return false;
	}

	// Check hardware support for current format (windowed mode)
	if(FAILED(direct3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displayMode.Format, displayMode.Format, true)))
	{
		return false;
	}

	// Check support for fullscreen
	if(FAILED(direct3D->CheckDeviceType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false)))
	{
		return false;
	}

	// Check Render Target Support (windowed mode) - should really enumerate through values here
	if(FAILED(direct3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displayMode.Format, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, D3DFMT_R32F)))
	{
		return false;
	}

	if(FAILED(direct3D->CheckDepthStencilMatch(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, displayMode.Format, D3DFMT_R32F, D3DFMT_D24X8)))
	{
		return false;
	}

	// Check Render Target Support (fullscreen)
	if(FAILED(direct3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, D3DFMT_R32F)))
	{
		return false;
	}

	if(FAILED(direct3D->CheckDepthStencilMatch(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_R32F, D3DFMT_D24X8)))
	{
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------
unsigned long TD3DUtil::GetCreateFlags(LPDIRECT3D9 direct3D)
{
	D3DCAPS9 caps;

	direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	unsigned long result = 0;

	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		result = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		result = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	// If using hardware then check for pure device
	if ((caps.DevCaps & D3DDEVCAPS_PUREDEVICE) && result & (D3DCREATE_HARDWARE_VERTEXPROCESSING))
	{
		result |= D3DCREATE_PUREDEVICE;
	}

	return result;
}
