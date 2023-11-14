#include "TCamera.h"
#include "Collision.h"
#include "TSphere.h"
#include "TConfig.h"
#include "TXMLReader.h"

//-------------------------------------------------------------------------------
const TVector3& TCamera::Up()
{
	static TVector3 up(0.f, 1.f, 0.f);
	return up;
}

//-------------------------------------------------------------------------------
TCamera::TCamera(const char* definitionFilename)
:   m_posW(0.0f, 0.0f, 0.0f),
    m_rightW(1.0f, 0.0f, 0.0f),
    m_upW(0.0f, 1.0f, 0.0f),
    m_lookW(0.0f, 0.0f, 1.0f)
{
	m_view.SetIdentity();
	m_proj.SetIdentity();
	m_viewProj.SetIdentity();

    TXMLReader reader(definitionFilename, *this);
}

//-------------------------------------------------------------------------------
TCamera::~TCamera()
{

}

//-------------------------------------------------------------------------------
const TMatrix& TCamera::GetViewMatrix() const
{
	return m_view;
}

//-------------------------------------------------------------------------------
const TMatrix& TCamera::GetProjectionMatrix() const
{
	return m_proj;
}

//-------------------------------------------------------------------------------
const TMatrix& TCamera::GetViewProjectionMatrix() const
{
	return m_viewProj;
}

//-------------------------------------------------------------------------------
const TVector3& TCamera::GetRightVec() const
{
	return m_rightW;
}

//-------------------------------------------------------------------------------
const TVector3& TCamera::GetUpVec() const
{
	return m_upW;
}

//-------------------------------------------------------------------------------
const TVector3& TCamera::GetLookVec() const
{
	return m_lookW;
}

//-------------------------------------------------------------------------------
const TVector3& TCamera::GetPosition() const
{
	return m_posW;
}

//-------------------------------------------------------------------------------
const TVector2 & TCamera::GetScreenDimensions() const
{
	return m_screen;
}

//-------------------------------------------------------------------------------
void TCamera::SetScreenSize(float x, float y)
{
	m_screen.x = x;
	m_screen.y = y;
}

//-------------------------------------------------------------------------------
void TCamera::LookAt(const TVector3& pos, const TVector3& target, const TVector3& up)
{
	TVector3 L = target - pos;
	L.Normalize();

	TVector3 R = CrossProduct(up, L);
	R.Normalize();

	TVector3 U = CrossProduct(L, R);
	U.Normalize();

	m_posW   = pos;
	m_rightW = R;
	m_upW    = U;
	m_lookW  = L;

	BuildView();
	BuildWorldFrustumPlanes();

	m_viewProj = m_view * m_proj;
}

//-------------------------------------------------------------------------------
void TCamera::BuildView()
{
	// Keep camera's axes orthogonal to each other and of unit length.
	m_lookW.Normalize();

	m_upW = CrossProduct(m_lookW, m_rightW);
	m_upW.Normalize();

	m_rightW = CrossProduct(m_upW, m_lookW);
	m_rightW.Normalize();

	// Fill in the view matrix entries.
	float x = -DotProduct(m_posW, m_rightW);
	float y = -DotProduct(m_posW, m_upW);
	float z = -DotProduct(m_posW, m_lookW);

	m_view.m[0][0] = m_rightW.x; 
	m_view.m[1][0] = m_rightW.y; 
	m_view.m[2][0] = m_rightW.z; 
	m_view.m[3][0] = x;   

	m_view.m[0][1] = m_upW.x;
	m_view.m[1][1] = m_upW.y;
	m_view.m[2][1] = m_upW.z;
	m_view.m[3][1] = y;  

	m_view.m[0][2] = m_lookW.x; 
	m_view.m[1][2] = m_lookW.y; 
	m_view.m[2][2] = m_lookW.z; 
	m_view.m[3][2] = z;   

	m_view.m[0][3] = 0.0f;
	m_view.m[1][3] = 0.0f;
	m_view.m[2][3] = 0.0f;
	m_view.m[3][3] = 1.0f;
}

//-------------------------------------------------------------------------------
bool TCamera::IsVisible(const TAABB& box) const
{
	for(int index = 0; index < 6; ++index)
	{
		if (CullingTest(box, m_frustumPlanes[index]) == CULLING_OUTSIDE)
		{
			return false;
		}
	}

	return true;
}

//-------------------------------------------------------------------------------
bool TCamera::IsVisible(const TVector3& point, float radius) const
{
	TSphere testSphere(point, radius);
	return IsVisible(testSphere);
}

//-------------------------------------------------------------------------------
bool TCamera::IsVisible(const TSphere& sphere) const
{
	for(int index = 0; index < 6; ++index)
	{
		if (CullingTest(sphere, m_frustumPlanes[index]) == CULLING_OUTSIDE)
		{
			return false;
		}
	}
	return true;
}

//-------------------------------------------------------------------------------
void TCamera::BuildWorldFrustumPlanes()
{
	// Note: Extract the frustum planes in world space.

	TMatrix VP = m_view * m_proj;

	TVector4 col0(VP.m[0][0], VP.m[1][0], VP.m[2][0], VP.m[3][0]);
	TVector4 col1(VP.m[0][1], VP.m[1][1], VP.m[2][1], VP.m[3][1]);
	TVector4 col2(VP.m[0][2], VP.m[1][2], VP.m[2][2], VP.m[3][2]);
	TVector4 col3(VP.m[0][3], VP.m[1][3], VP.m[2][3], VP.m[3][3]);

	// Planes face inward.
	m_frustumPlanes[0] = (TPlane)(col2);        // near
	m_frustumPlanes[1] = (TPlane)(col3 - col2); // far
	m_frustumPlanes[2] = (TPlane)(col3 + col0); // left
	m_frustumPlanes[3] = (TPlane)(col3 - col0); // right
	m_frustumPlanes[4] = (TPlane)(col3 - col1); // top
	m_frustumPlanes[5] = (TPlane)(col3 + col1); // bottom

	for(int index = 0; index < 6; index++)
	{
		Normalize(m_frustumPlanes[index]);
	}
}

//-------------------------------------------------------------------------------
void TCamera::GetBillboardMatrix(TMatrix& result) const
{
	// invert the 3x3 part (rotation) of the view to give billboard matrix
	result.Set(m_view[0][0], m_view[1][0], m_view[2][0], 0.f,
			  m_view[0][1], m_view[1][1], m_view[2][1], 0.f,
			  m_view[0][2], m_view[1][2], m_view[2][2], 0.f,
			  0.f,			   0.f,				0.f,			 1.f);
}

//-------------------------------------------------------------------------------
bool TCamera::UICamera() const
{
    return m_uiCamera;
}

//-------------------------------------------------------------------------------
bool TCamera::MainCamera() const
{
    return m_mainCamera;
}

//-------------------------------------------------------------------------------
const TString& TCamera::GetName() const
{
	return m_name;
}

//-------------------------------------------------------------------------------
void TCamera::ScreenToWorld(const TVector2& screenInput, TVector3& worldOutput)
{
	TVector3 originW;
	TVector3 dirW;

	// device coords
	float x = ( 2.f * screenInput.x/m_screen.x - 1.f) / m_proj[0][0];
	float y = (-2.f * screenInput.y/m_screen.y + 1.f) / m_proj[1][1];

	// Build picking ray
	TVector3 origin(0.0f, 0.0f, 0.0f);
	TVector3 dir(x, y, 1.0f);

	// transform to world space
	TMatrix invView = m_view;
	invView.Invert();
	invView.TransformVector(&origin, &originW);

	invView = m_view;
	invView.Transpose();
	invView.TransformVector(&dir, &dirW);

	dirW.Normalize();

	// intersect with xz plane
	float dot = DotProduct(TVector3(1,0,1), Up());

	TVector3 position = originW;

	float time = (dot - DotProduct(position, Up() )) / (DotProduct(dirW, Up() ));

	worldOutput = position + (dirW * time);
}

//-------------------------------------------------------------------------------
TXMLObject* TCamera::HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects)
{
    return NULL;
}

//-------------------------------------------------------------------------------
void TCamera::HandleLoadAttributes(TDynamicSet<TDataVariant>& objects)
{
	m_name = TDataVariant::Find("name", objects).GetString();
    m_mainCamera = TDataVariant::Find("mainCamera", objects).GetBool();
    m_uiCamera = TDataVariant::Find("uiCamera", objects).GetBool();

    m_screen.x = (float)TDataVariant::Find("width", objects).GetInt();
    m_screen.y = (float)TDataVariant::Find("height", objects).GetInt();

    if (m_screen.x == 0.f)
    {
        m_screen.x = TConfig::Get()->GetScreenWidth();
    }

    if (m_screen.y == 0.f)
    {
        m_screen.y = TConfig::Get()->GetScreenHeight();
    }

    float fov = TDataVariant::Find("fov", objects).GetFloat();
    float aspect = TDataVariant::Find("aspect", objects).GetFloat();
    float nearZ = TDataVariant::Find("nearZ", objects).GetFloat();
    float farZ = TDataVariant::Find("farZ", objects).GetFloat();

    TString mode = TDataVariant::Find("mode", objects).GetString();

    if (mode == "orthographic")
    {
        m_proj.SetOrthoProjection(m_screen.x, m_screen.y, nearZ, farZ);

        LookAt(	TVector3(m_screen.x * 0.5f, -m_screen.y * 0.5f, -0.1f),
				TVector3(m_screen.x * 0.5f, -m_screen.y * 0.5f, 0),
				TVector3(0, 1, 0));
    }
    else if (mode == "perspective")
    {
        m_proj.SetPerspectiveProjection(fov, aspect, nearZ, farZ);

        BuildWorldFrustumPlanes();

        m_viewProj = m_view * m_proj;
    }
}

//-------------------------------------------------------------------------------
void TCamera::FinaliseLoad()
{
}

//-------------------------------------------------------------------------------
void TCamera::Write(TXMLWriter& writer)
{
}
