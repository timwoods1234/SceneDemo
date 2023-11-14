#ifndef __TPLANE_H__
#define __TPLANE_H__

#ifndef __TVECTOR3_H__
#include "TVector3.h"
#endif

class TMatrix;
class TVector4;

class TPlane
{
public:
	TPlane();
	TPlane(float a, float b, float c, float d);
	TPlane(const TPlane& p);
	TPlane(const TVector3& normal, const TVector3& point);
	TPlane(const TVector3& normal, float c);
	TPlane(const TVector3& p0, const TVector3& p1, const TVector3& p2);
	TPlane(const TVector4& v);
	
	float& operator[](unsigned int i);
	float  operator[](unsigned int i) const;
	TPlane& operator=(const TPlane& p);

	const TVector3& GetNormal() const;
	float GetConstant() const;

	void Set(float nx, float ny, float nz, float c);
	void Set(const TVector3& p0, const TVector3& p1, const TVector3& p2);
	void SetConstant(float constant);

	//bool IntersectTestRay(const TRay& ray) const;
	//bool IntersectRay(const TRay& ray, TVector3& result) const;
	float Magnitude() const;
	float MagnitudeSquared() const;
	bool IsEqualTo(const TPlane& p) const;
	void Transform(const TMatrix& transform);

protected:
	// the plane equation is m_normal.(xyz) = m_constant
	TVector3 m_normal;
	float	 m_constant;
};

TPlane Normalize(const TPlane& plane);

#include "TPlane.inl"

#endif