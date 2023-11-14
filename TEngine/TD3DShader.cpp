#include "TD3DShader.h"
#include "TD3DEventDeviceLost.h"
#include "TD3DEventDeviceReset.h"
#include "TDirect3D.h"
#include "TError.h"
#include "TLocator.h"
#include "TDebugInterface.h"
#include "TMatrix.h"
#include "TD3DDevice.h"
#include "TSkin.h"
#include "TResourceManager.h"
#include "TMaterial.h"
#include "TTexture.h"
#include "TSkin.h"
#include "TVector2.h"
#include "TVector4.h"
#include "TPointLight.h"
#include "TDirectionalLight.h"
#include "TSpotLight.h"

//-------------------------------------------------------------------------------
TD3DShader::TD3DShader(const char* filename, LPDIRECT3DDEVICE9 device)
:	TShader(filename),
	m_d3dEffect(NULL)
{
	TD3DEventDeviceLost::Get()->Register(this, &TD3DShader::OnLostDevice);
	TD3DEventDeviceReset::Get()->Register(this, &TD3DShader::OnResetDevice);

	CreateEffect(device);
}

//-------------------------------------------------------------------------------
TD3DShader::~TD3DShader()
{
	TD3DEventDeviceLost::Get()->Unregister(this, &TD3DShader::OnLostDevice);
	TD3DEventDeviceReset::Get()->Unregister(this, &TD3DShader::OnResetDevice);

	SafeRelease(m_d3dEffect);
}

//-------------------------------------------------------------------------------
void TD3DShader::BeginRendering()
{
	UINT nNumPasses = 0;

	m_d3dEffect->Begin(&nNumPasses, 0);

	m_d3dEffect->BeginPass(0);
}

//-------------------------------------------------------------------------------
void TD3DShader::EndRendering()
{
	m_d3dEffect->EndPass();

	m_d3dEffect->End();
}

//-------------------------------------------------------------------------------
void TD3DShader::OnResetDevice()
{
	m_d3dEffect->OnResetDevice();

	m_d3dEffect->SetTechnique(m_technique.GetPointer());

	m_d3dEffect->CommitChanges();
}

//-------------------------------------------------------------------------------
void TD3DShader::OnLostDevice()
{
	m_d3dEffect->OnLostDevice();
}

//-------------------------------------------------------------------------------
void TD3DShader::CreateEffect(LPDIRECT3DDEVICE9 device)
{
	TString filepath = TString::Format("Assets/Shader/%s.fx", m_id.GetPointer());

	ID3DXBuffer* errors = 0;
	HRESULT hr = D3DXCreateEffectFromFile(device, filepath.GetPointer(), 0, 0, D3DXSHADER_USE_LEGACY_D3DX9_31_DLL, 0, &m_d3dEffect, &errors);

	if (FAILED(hr))
	{
		if (errors)
		{
			TLocator::GetDebugSystem()->Print((char*)errors->GetBufferPointer());
		}

		TASSERT(false, "[TD3DShader] Failed to load shader");
	}
}

//-------------------------------------------------------------------------------
void TD3DShader::SetSkin(const TSkin* skin)
{
	SetMaterial(&(skin->GetMaterial()));

	int numTextures = skin->GetNumTextures();

	for (int index = 0; index < numTextures; index++)
	{
		SetTexture(skin->GetTextureProperty(index), skin->GetTexture(index));
	}
}

//-------------------------------------------------------------------------------
void TD3DShader::SetMaterial(const TMaterial* material)
{
	m_d3dEffect->SetValue("gMtrl", material, sizeof(TMaterial));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetTexture(const char* propertyName, const TTexture* texture)
{
	m_d3dEffect->SetTexture(propertyName, (LPDIRECT3DTEXTURE9)texture->GetData());
}

//-------------------------------------------------------------------------------
void TD3DShader::SetMatrix(const char* propertyName, const TMatrix* matrix)
{
	m_d3dEffect->SetValue(propertyName, matrix, sizeof(TMatrix));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetFloat(const char* propertyName, float value)
{
	m_d3dEffect->SetValue(propertyName, &value, sizeof(float));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetInt(const char* propertyName, int value)
{
	m_d3dEffect->SetValue(propertyName, &value, sizeof(int));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetVector2(const char* propertyName, const TVector2& value)
{
	m_d3dEffect->SetValue(propertyName, &value, sizeof(TVector2));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetVector3(const char* propertyName, const TVector3& value)
{
	m_d3dEffect->SetValue(propertyName, &value, sizeof(TVector3));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetVector4(const char* propertyName, const TVector4& value)
{
	m_d3dEffect->SetValue(propertyName, &value, sizeof(TVector4));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetLight(const char* propertyName, const TDirectionalLight* light)
{
	m_d3dEffect->SetValue(propertyName, light, sizeof(TDirectionalLight));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetLight(const char* propertyName, const TPointLight* light)
{
	m_d3dEffect->SetValue(propertyName, light, sizeof(TPointLight));
}

//-------------------------------------------------------------------------------
void TD3DShader::SetLight(const char* propertyName, const TSpotLight* light)
{
	m_d3dEffect->SetValue(propertyName, light, sizeof(TSpotLight));
}

//-------------------------------------------------------------------------------
void TD3DShader::PreRender()
{
	m_d3dEffect->CommitChanges();
}
