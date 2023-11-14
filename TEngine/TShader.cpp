#include "TShader.h"
#include "TLocator.h"
#include "TRendererInterface.h"
#include "TGraphicsFactoryInterface.h"
#include "TMemory.h"
#include "TXMLReader.h"
#include "TResourceManager.h"

//-------------------------------------------------------------------------------
TShader::TShader(const char* filename)
:	m_renderOrder(0),
	m_useAlpha(false),
    m_zFuncState(RS_ZFUNC_ALWAYS),
	m_cullMode(RS_CULL_CCW),
	m_vertexFormat(NULL)
{
	TXMLReader reader(filename, *this);

	if (reader.WasError())
	{
        TDebugPrint(("[TShader::Load] Failed to load %s", filename));
	}
}

//-------------------------------------------------------------------------------
TShader::~TShader()
{
}

//-------------------------------------------------------------------------------
const TString& TShader::GetId() const
{
	return m_id;
}

//-------------------------------------------------------------------------------
int TShader::GetRenderOrder() const
{
	return m_renderOrder;
}

//-------------------------------------------------------------------------------
TVertexFormat* TShader::GetVertexFormat() const
{
	return m_vertexFormat;
}

//-------------------------------------------------------------------------------
bool TShader::UsesAlpha() const
{
	return m_useAlpha;
}

//-------------------------------------------------------------------------------
TZCompareState TShader::GetZFuncState() const
{
    return m_zFuncState;
}

//-------------------------------------------------------------------------------
TCullMode TShader::GetCullMode() const
{
	return m_cullMode;
}

//-------------------------------------------------------------------------------
TShader* TShader::Acquire(const char* id)
{
    TString filename = TString::Format("Assets/Shader/%s.xml", id);

    TShader* result = (TShader*)TResourceManager::Get()->Allocate(ResourceType_Shader, filename.GetPointer());

    return result;
}

//-------------------------------------------------------------------------------
void TShader::Release(TShader* shader)
{
    TResourceManager::Get()->Release(ResourceType_Shader, shader);
}

//-------------------------------------------------------------------------------
TRefCountedObject* TShader::Load(const char* path)
{
	TShader* result = TLocator::GetGraphicsFactory()->CreateShader(path);

	return result;
}

//-------------------------------------------------------------------------------
void TShader::Unload(TRefCountedObject* toDelete)
{
    TShader* shader = static_cast<TShader*>(toDelete);

    TLocator::GetGraphicsFactory()->UnloadShader(shader);
}

//-------------------------------------------------------------------------------
void TShader::PreRender()
{
}

//-------------------------------------------------------------------------------
TXMLObject* TShader::HandleLoadElement(const TString& id, TDynamicSet<TDataVariant>& objects)
{
	return NULL;
}

//-------------------------------------------------------------------------------
void TShader::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_id = TDataVariant::Find("id", objects).GetString();
	m_technique = TDataVariant::Find("technique", objects).GetString();
	m_renderOrder = TDataVariant::Find("renderOrder", objects).GetInt();
	m_useAlpha = TDataVariant::Find("alphaBlending", objects).GetBool();

    TString zFuncState = TDataVariant::Find("zcompare", objects).GetString();

    if (zFuncState == "LessEq")
    {
        m_zFuncState = RS_ZFUNC_LESSEQUAL;
    }
    else if (zFuncState == "Always")
    {
        m_zFuncState = RS_ZFUNC_ALWAYS;
    }
	else if (zFuncState == "Greater")
	{
		m_zFuncState = RS_ZFUNC_GREATER;
	}

	TString vertexFormat = TDataVariant::Find("vertexFormat", objects).GetString();
	m_vertexFormat = TLocator::GetRenderer()->GetVertexFormat(vertexFormat.GetPointer());

	TString cullMode = TDataVariant::Find("cullMode", objects).GetString();

	if (cullMode == "CW")
	{
		m_cullMode = RS_CULL_CW;
	}
	else if (cullMode == "None")
	{
		m_cullMode = RS_CULL_NONE;
	}
	else
	{
		m_cullMode = RS_CULL_CCW;
	}
}

//-------------------------------------------------------------------------------
void TShader::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TShader::Write(TXMLWriter& writer)
{
}
