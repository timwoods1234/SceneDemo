#include "TD3DGraphicsFactory.h"
#include "TBitmapFont.h"
#include "TD3DShader.h"
#include "TD3DMeshBuffer.h"
#include "TTexture.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TD3DVertexFormat.h"
#include "TD3DFont.h"
#include "TFileSystemInterface.h"

//-------------------------------------------------------------------------------
TD3DGraphicsFactory::TD3DGraphicsFactory(LPDIRECT3DDEVICE9 device)
:	m_device(device)
{
}

//-------------------------------------------------------------------------------
TD3DGraphicsFactory::~TD3DGraphicsFactory()
{
}

//-------------------------------------------------------------------------------
bool TD3DGraphicsFactory::LoadTexture(const char* filename, TTexture* outputTexture)
{
	LPDIRECT3DTEXTURE9 d3dTexture = 0;
	D3DXIMAGE_INFO imageInfo;

	HRESULT hr;
	if (FAILED(hr = D3DXCreateTextureFromFileEx(
						m_device,
						filename,
						D3DX_DEFAULT_NONPOW2,	// get width & height from file
						D3DX_DEFAULT_NONPOW2,
						D3DX_FROM_FILE,	// mip levels
						0,				// usage (0 == not render target)
						D3DFMT_A8R8G8B8,// format
						D3DPOOL_MANAGED,
						D3DX_DEFAULT,	// filtering
						D3DX_DEFAULT,	// mip filter
						0,				// disable color key
						&imageInfo,		// extra source info
						NULL,			// palette
						&d3dTexture)))
	{
		TDebugPrint(("[TD3DRenderInterface::AddTexture] Failed to load %s", filename));

		return false;
	}

	outputTexture->SetData(d3dTexture);
	outputTexture->SetWidth(imageInfo.Width);
	outputTexture->SetHeight(imageInfo.Height);

	return true;
}

//-------------------------------------------------------------------------------
bool TD3DGraphicsFactory::LoadCubeTexture(const char* filename, TTexture* outputTexture)
{
	IDirect3DCubeTexture9* d3dCubeMap;

	HRESULT hr;

	if (FAILED(hr = D3DXCreateCubeTextureFromFile(m_device, filename, &d3dCubeMap)))
	{
		TDebugPrint(("[TD3DRenderInterface::LoadCubeTexture] Failed to load %s", filename));

		return false;
	}

	outputTexture->SetData(d3dCubeMap);
	outputTexture->SetWidth(d3dCubeMap->Width);
	outputTexture->SetHeight(d3dCubeMap->Height);

	return true;
}

//-------------------------------------------------------------------------------
void TD3DGraphicsFactory::UnloadTexture(TTexture& texture)
{
	LPDIRECT3DTEXTURE9 d3dTexture = (LPDIRECT3DTEXTURE9)texture.GetData();

	SafeRelease(d3dTexture);
}

//-------------------------------------------------------------------------------
TShader* TD3DGraphicsFactory::CreateShader(const char* filename)
{
	if (TLocator::GetFileSystem()->FileExists(filename))
	{
		return TNew TD3DShader(filename, m_device);
	}

	return NULL;
}

//-------------------------------------------------------------------------------
void TD3DGraphicsFactory::UnloadShader(TShader* shader)
{
	TSafeDelete(shader);
}

//-------------------------------------------------------------------------------
TFont* TD3DGraphicsFactory::CreateTFont(const char* filename)
{
	TString filenameString = filename;
	TFont* result = NULL;

	if (filenameString.Contains("Debug"))
	{
		result = TNew TD3DFont(filename, m_device);
	}
	else
	{
		result = TNew TBitmapFont(filename);
	}

    return result;
}

//-------------------------------------------------------------------------------
void TD3DGraphicsFactory::UnloadFont(TFont* font)
{
    TSafeDelete(font);
}

//-------------------------------------------------------------------------------
TMeshBufferInterface* TD3DGraphicsFactory::CreateMeshBuffer(const char* vertexTypeName)
{
	TD3DVertexFormat* format = static_cast<TD3DVertexFormat*>(TLocator::GetRenderer()->GetVertexFormat(vertexTypeName));

	TD3DMeshBuffer* entry = TNew TD3DMeshBuffer(m_device, format);

	return entry;
}

//-------------------------------------------------------------------------------
void TD3DGraphicsFactory::UnloadMeshBuffer(TMeshBufferInterface* entry)
{
	TSafeDelete(entry);
}

//-------------------------------------------------------------------------------
bool TD3DGraphicsFactory::CreateTexture(int width, int height, TTexture* outputTexture)
{
	LPDIRECT3DTEXTURE9 d3dTexture = 0;

	HRESULT hr;
	if (FAILED(hr = D3DXCreateTexture(
		m_device,
		width,
		height,
		D3DX_DEFAULT,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&d3dTexture)))
	{
		TDebugPrint(("[TD3DRenderInterface::AddTexture] Failed to create empty texture"));

		return false;
	}

	outputTexture->SetData(d3dTexture);
	outputTexture->SetWidth(width);
	outputTexture->SetHeight(height);

	return true;
}
