#ifndef __TD3DSHADER_H__
#define __TD3DSHADER_H__

#ifndef __TSHADER_H__
#include "TShader.h"
#endif

#ifndef __TDIRECT3D_H__
#include "TDirect3D.h"
#endif

#ifndef __TEVENTLISTENER_H__
#include "TEventListener.h"
#endif

struct ID3DXEffect;

class TD3DShader :	public TShader, 
					public TEventListener
{
public:
	TD3DShader(const char* filename, LPDIRECT3DDEVICE9 device);
	~TD3DShader();

	void PreRender();
	
	void BeginRendering();
	void EndRendering();
	
	void SetSkin(const TSkin* skin);
	void SetMaterial(const TMaterial* material);
	void SetTexture(const char* propertyName, const TTexture* texture);
	void SetMatrix(const char* propertyName, const TMatrix* matrix);
	void SetFloat(const char* propertyName, float value);
	void SetInt(const char* propertyName, int value);
	void SetVector2(const char* propertyName, const TVector2& value);
	void SetVector3(const char* propertyName, const TVector3& value);
	void SetVector4(const char* propertyName, const TVector4& value);
	void SetLight(const char* propertyName, const TDirectionalLight* light);
	void SetLight(const char* propertyName, const TPointLight* light);
	void SetLight(const char* propertyName, const TSpotLight* light);

private:
	void CreateEffect(LPDIRECT3DDEVICE9 device);
	void OnResetDevice();
	void OnLostDevice();

	ID3DXEffect* m_d3dEffect;
};

#endif
