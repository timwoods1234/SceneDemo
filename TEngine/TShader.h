#ifndef __TSHADER_H__
#define __TSHADER_H__

#ifndef __TDYNAMICSET_H__
#include "TDynamicSet.h"
#endif

#ifndef __TSTRING_H__
#include "TString.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

#ifndef __TREFCOUNTEDOBJECT_H__
#include "TRefCountedObject.h"
#endif

#ifndef __TRENDERSTATE_H__
#include "TRenderState.h"
#endif

struct TMaterial;
struct TDirectionalLight;
struct TPointLight;
struct TSpotLight;
class TSkin;
class TCamera;
class TMatrix;
class TTexture;
class TVector2;
class TVector3;
class TVector4;
class TVertexFormat;

class TShader : public TXMLObject,
				public TRefCountedObject
{
public:
    static TShader* Acquire(const char* id);

    static void Release(TShader* shader);

	TShader(const char* filename);
	virtual ~TShader();

	const TString&				GetId() const;
	int							GetRenderOrder() const;
	TVertexFormat*				GetVertexFormat() const;
	bool						UsesAlpha() const;
    TZCompareState              GetZFuncState() const;
	TCullMode					GetCullMode() const;

	virtual void PreRender();
	
	virtual void BeginRendering() = 0;
	virtual void EndRendering() = 0;
	
	virtual void SetSkin(const TSkin* skin) = 0;
	virtual void SetMaterial(const TMaterial* material) = 0;
	virtual void SetTexture(const char* propertyName, const TTexture* texture) = 0;
	virtual void SetMatrix(const char* propertyName, const TMatrix* matrix) = 0;
	virtual void SetFloat(const char* propertyName, float value) = 0;
	virtual void SetInt(const char* propertyName, int value) = 0;
	virtual void SetVector2(const char* propertyName, const TVector2& value) = 0;
	virtual void SetVector3(const char* propertyName, const TVector3& value) = 0;
	virtual void SetVector4(const char* propertyName, const TVector4& value) = 0;
	virtual void SetLight(const char* propertyName, const TDirectionalLight* light) = 0;
	virtual void SetLight(const char* propertyName, const TPointLight* light) = 0;
	virtual void SetLight(const char* propertyName, const TSpotLight* light) = 0;

	TXMLObject* HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects);
	void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
	void Write(TXMLWriter& writer);

	virtual void FinaliseLoad();

protected:
    //todo: add private constructor too?
    friend class TResourceManager;
    static TRefCountedObject* Load(const char* id);
    static void Unload(TRefCountedObject* toDelete);

	TString m_id;
	TString m_technique;

	bool m_useAlpha;

	int m_renderOrder;

	TCullMode m_cullMode;
    TZCompareState m_zFuncState;
	TVertexFormat* m_vertexFormat;
};

#endif
