#include "TD3DRenderer.h"
#include "TCamera.h"
#include "TD3DDevice.h"
#include "TShader.h"
#include "TApplicationInterface.h"
#include "TGameStats.h"
#include "TD3DVertexFormat.h"
#include "TD3DVertexFormatRegister.h"
#include "TD3DGraphicsFactory.h"
#include "TLocator.h"
#include "TSurface2DMesh.h"
#include "TWindowsDebug.h"
#include "TMesh.h"
#include "TD3DMeshBuffer.h"
#include "TSubMeshInfo.h"
#include "TLightManager.h"

//-------------------------------------------------------------------------------
TD3DRenderer::TD3DRenderer(HWND window)
{
	m_d3dDevice = TNew TD3DDevice(window);

	m_vertexFormatRegister = TNew TD3DVertexFormatRegister(m_d3dDevice->GetDevice());
	m_vertexFormatRegister->LoadAllFormats();

	TD3DGraphicsFactory* factory = TNew TD3DGraphicsFactory(m_d3dDevice->GetDevice());
	TLocator::RegisterGraphicsFactory(factory);

	m_surfaceMesh = TNew TSurface2DMesh();

	SetDepthBufferMode(RS_DEPTH_READWRITE);
	SetShadeMode(RS_SHADE_SOLID, 1.f);
	SetZFunc(RS_ZFUNC_LESSEQUAL);
	SetCullMode(RS_CULL_CCW);
}

//-------------------------------------------------------------------------------
TD3DRenderer::~TD3DRenderer()
{
	TSafeDelete(m_surfaceMesh);

	TGraphicsFactoryInterface*factory = TLocator::GetGraphicsFactory();
	TSafeDelete(factory);

	TSafeDelete(m_vertexFormatRegister);

	TSafeDelete(m_d3dDevice);
}

//-------------------------------------------------------------------------------
void TD3DRenderer::BeginFrame()
{
    TGameStats::Get()->OnBeginFrame();

	m_d3dDevice->BeginRendering(true,true,false);

	// TODO: activate default shader
}

//-------------------------------------------------------------------------------
void TD3DRenderer::EndFrame()
{
	ActivateShader(NULL);

	m_d3dDevice->EndRendering();
}

//-------------------------------------------------------------------------------
void TD3DRenderer::ActivateShader(TShader* shader)
{
	if (m_activeShader != shader)
	{
		if (m_activeShader != NULL)
		{
			m_activeShader->EndRendering();
		}

		m_activeShader = shader;

		if (m_activeShader != NULL)
		{
			SetAlphaBlending(m_activeShader->UsesAlpha());
			SetZFunc(m_activeShader->GetZFuncState());
			SetCullMode(m_activeShader->GetCullMode());

			TD3DVertexFormat* format = static_cast<TD3DVertexFormat*>(m_activeShader->GetVertexFormat());

			m_d3dDevice->GetDevice()->SetFVF(format->GetFVF());
			m_d3dDevice->GetDevice()->SetVertexDeclaration(format->GetD3DDeclaration());
			
			m_activeShader->BeginRendering();

			m_activeShader->SetVector3("gCameraPosition", m_currentCamera->GetPosition());

			// TODO: move this so it's only called once when the shader is setup
			// or if the light changes, whatever changes it should call this
			// maybe have a flag to say lighting is dirty? (TLightManager->RequestUpdate?)
			// and do that per light (and per shader? so it's a 2x2 grid? or just one value per frame?)
			// how does that cope with shaders that are created after the light is adjusted?
			TLightManager::Get()->ApplyLighting(m_activeShader);
		}
	}
}

//-------------------------------------------------------------------------------
void TD3DRenderer::SetDepthBufferMode(TDepthState rs)
{
	if (m_depthState != rs)
	{
		LPDIRECT3DDEVICE9 device = m_d3dDevice->GetDevice();

		if (rs == RS_DEPTH_READWRITE)
		{
			device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
		else if (rs == RS_DEPTH_READONLY)
		{
			device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		}
		else if (rs == RS_DEPTH_NONE)
		{
			device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		}

		m_depthState = rs;
	}
}

//-------------------------------------------------------------------------------
void TD3DRenderer::SetShadeMode(TShadeState smd, float f)
{
	LPDIRECT3DDEVICE9 device = m_d3dDevice->GetDevice();

	if (m_shadeState == smd)
	{
		//maybe change in size
		if (smd == RS_SHADE_POINTS)
		{
			device->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)&f);
		}

		return;
	}

	if (smd == RS_SHADE_TRIWIRE)
	{
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_shadeState = smd;
	}
	else
	{
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_shadeState = smd;
	}

	if (smd == RS_SHADE_POINTS)
	{
		if (f > 0.0f)
		{
			device->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
			device->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
			device->SetRenderState(D3DRS_POINTSIZE, *(DWORD*)&f);
			device->SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)(0.0f));
			device->SetRenderState(D3DRS_POINTSCALE_A, (DWORD)(0.0f));
			device->SetRenderState(D3DRS_POINTSCALE_B, (DWORD)(0.0f));
			device->SetRenderState(D3DRS_POINTSCALE_B, (DWORD)(1.0f));
		}
		else
		{
			device->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
			device->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
		}
	}
	else
	{
		device->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
		device->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);	
	}
}

//-------------------------------------------------------------------------------
void TD3DRenderer::SetAlphaBlending(bool enable)
{
	// TODO: cache state and change only if necessary
	if (enable)
	{
		m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 100);
	}
	else
	{
		m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//-------------------------------------------------------------------------------
void TD3DRenderer::SetZFunc(TZCompareState smd)
{
	if (m_compareState != smd)
	{
		if (smd == RS_ZFUNC_LESSEQUAL)
		{
			m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}
		else if (smd == RS_ZFUNC_GREATER)
		{
			m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
		}
		else if (smd == RS_ZFUNC_ALWAYS)
		{
			m_d3dDevice->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		}

		m_compareState = smd;
	}
}

//-------------------------------------------------------------------------------
void TD3DRenderer::SetCullMode(TCullMode mode)
{
	if (m_cullMode != mode)
	{
		if (mode == RS_CULL_CCW)
		{
			m_d3dDevice->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		}
		else if (mode == RS_CULL_CW)
		{
			m_d3dDevice->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		}
		else if (mode == RS_CULL_NONE)
		{
			m_d3dDevice->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		}

		m_cullMode = mode;
	}
}

//-------------------------------------------------------------------------------
void TD3DRenderer::DrawMesh(const TMatrix& matWorld, const TMesh& mesh)
{
	ActivateShader(mesh.GetShader());

	m_activeShader->SetMatrix("gWorld", &matWorld);
	m_activeShader->SetMatrix("gWorldViewProjection", &(matWorld * m_currentCamera->GetViewProjectionMatrix()));

	g_matWorld.Invert(matWorld);
	g_matWorld.Transpose();

	m_activeShader->SetMatrix("gWorldInvTrans", &g_matWorld);

	const TMeshBufferInterface* meshBuffer = mesh.GetMeshBuffer();

	if (mesh.GetSharedMesh() != NULL)
	{
		meshBuffer = mesh.GetSharedMesh()->GetMeshBuffer();
	}

	m_d3dDevice->SetMeshBuffer(static_cast<const TD3DMeshBuffer*>(meshBuffer));

	int numSubMeshes = mesh.GetSubMeshCount();
	const TSubMeshInfo* subMeshInfo = NULL;

	// TODO: for each shader pass

	for (int index = 0; index < numSubMeshes; index++)
	{
		subMeshInfo = mesh.GetSubMeshInfo(index);

		if (subMeshInfo->skin != NULL)
		{
			m_activeShader->SetSkin(subMeshInfo->skin);
		}

		m_activeShader->PreRender();

		m_d3dDevice->DrawIndexedPrimitive(meshBuffer->GetNumVertices(), subMeshInfo->startIndex, subMeshInfo->numIndices);
	}

	// TODO: this seems to be getting lost if it's updated at the end of the frame
	// should track two values and swap on the next frame?
	TGameStats::Get()->OnEndFrame(1, meshBuffer->GetNumVertices(), meshBuffer->GetNumIndices() / 3);
}

//-------------------------------------------------------------------------------
void TD3DRenderer::Draw2D(TTexture* texture, const TVector2& position, const TVector4& texCoords, float rotation, float scaleX, float scaleY)
{
	// TODO: could replace this with a mat4x4, pack texCoords into the last column
	// need to send alpha too, though
	m_surfaceMesh->AddSprite(texture, position, texCoords, rotation, scaleX, scaleY);
}

//-------------------------------------------------------------------------------
void TD3DRenderer::DrawLineStrip(const TMesh& mesh)
{
	ActivateShader(mesh.GetShader());

	m_activeShader->SetMatrix("gWorldViewProjection", &(TMatrix::GetIdentity() * m_currentCamera->GetViewProjectionMatrix()));

	m_d3dDevice->SetMeshBuffer(static_cast<const TD3DMeshBuffer*>(mesh.GetMeshBuffer()));

	TSkin* skin = mesh.GetSkin(0);

	m_activeShader->SetSkin(skin);

	m_activeShader->PreRender();

	m_d3dDevice->DrawLineStrip(mesh.GetMeshBuffer()->GetNumVertices() - 1);
}

//-------------------------------------------------------------------------------
void TD3DRenderer::DrawLineList(const TMesh& mesh)
{
	ActivateShader(mesh.GetShader());

	m_activeShader->SetMatrix("gWorldViewProjection", &(TMatrix::GetIdentity() * m_currentCamera->GetViewProjectionMatrix()));

	m_d3dDevice->SetMeshBuffer(static_cast<const TD3DMeshBuffer*>(mesh.GetMeshBuffer()));

	TSkin* skin = mesh.GetSkin(0);

	m_activeShader->SetSkin(skin);

	m_activeShader->PreRender();

	m_d3dDevice->DrawLineList(mesh.GetMeshBuffer()->GetNumVertices() / 2);
}

//-------------------------------------------------------------------------------
TVertexFormat* TD3DRenderer::GetVertexFormat(const TString& name)
{
	return m_vertexFormatRegister->GetVertexFormat(name);
}