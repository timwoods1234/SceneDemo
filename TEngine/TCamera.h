#ifndef __TCAMERA_H__
#define __TCAMERA_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

#ifndef __TVECTOR2_H__
#include "TVector2.h"
#endif

#ifndef __TMATRIX_H__
#include "TMatrix.h"
#endif

#ifndef __TPLANE_H__
#include "TPlane.h"
#endif

#ifndef __TXMLOBJECT_H__
#include "TXMLObject.h"
#endif

class TAABB;
class TSphere;

class TCamera : public TXMLObject
{
public:
	static const TVector3& Up();

	TCamera(const char* definitionFilename);
	~TCamera();

	const TMatrix& GetViewMatrix() const;
	const TMatrix& GetProjectionMatrix() const;
	const TMatrix& GetViewProjectionMatrix() const;

	const TVector3& GetRightVec() const;
	const TVector3& GetUpVec() const;
	const TVector3& GetLookVec() const;
	const TVector3& GetPosition() const;

	const TVector2 & GetScreenDimensions() const;

    void LookAt(const TVector3& pos, const TVector3& target, const TVector3& up);

    void GetBillboardMatrix(TMatrix& result) const;

    void ScreenToWorld(const TVector2& screenPosition, TVector3& worldPosition);

    bool UICamera() const;
    bool MainCamera() const;
	const TString& GetName() const;

	bool IsVisible(const TAABB& box) const;
	bool IsVisible(const TVector3& point, float radius) const;
	bool IsVisible(const TSphere& sphere) const;

    TXMLObject* HandleLoadElement(const TString& strID, TDynamicSet<TDataVariant>& objects);
    void HandleLoadAttributes(TDynamicSet<TDataVariant>& objects);
    void FinaliseLoad();
    void Write(TXMLWriter& writer);

private:
    void SetScreenSize(float x, float y);

	void BuildView();
	void BuildWorldFrustumPlanes();

	TVector2	m_screen;

	TMatrix m_view;
	TMatrix m_proj;
	TMatrix m_viewProj;

	// Relative to world space.
	TVector3 m_posW;
	TVector3 m_rightW;
	TVector3 m_upW;
	TVector3 m_lookW;

	// Frustum Planes
	TPlane m_frustumPlanes[6];	// [0] = near
	                            // [1] = far
	                            // [2] = left
	                            // [3] = right
	                            // [4] = top
	                            // [5] = bottom

	TString m_name;

    bool m_uiCamera;

    bool m_mainCamera;
};

#endif
