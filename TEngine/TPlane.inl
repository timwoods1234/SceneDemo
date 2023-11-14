#ifndef __TMATH_H__
#include "TMath.h"
#endif

#ifndef __TVECTOR4_H__
#include "TVector4.h"
#endif

//-------------------------------------------------------------------------------
inline TPlane::TPlane()
{
}

//-------------------------------------------------------------------------------
inline TPlane::TPlane(float a, float b, float c, float d)
:	m_normal(a, b, c),
	m_constant(d)
{
}

//-------------------------------------------------------------------------------
inline TPlane::TPlane(const TPlane& p)
:	m_normal(p.m_normal),
	m_constant(p.m_constant)
{
}

//-------------------------------------------------------------------------------
inline TPlane::TPlane(const TVector3& normal, const TVector3& point)
{
	m_normal = Normalize(normal);
	m_constant = DotProduct(m_normal, point);
}

//-------------------------------------------------------------------------------
inline TPlane::TPlane(const TVector3& normal, float constant)
:	m_normal(normal),
	m_constant(constant) 
{
}

//-------------------------------------------------------------------------------
inline TPlane::TPlane(const TVector3& p0, const TVector3& p1, const TVector3& p2)
{
	Set(p0, p1, p2);
}

//-------------------------------------------------------------------------------
inline TPlane::TPlane(const TVector4& v)
{
	Set(v.x, v.y, v.z, v.w);
}

//-------------------------------------------------------------------------------
inline TPlane& TPlane::operator=(const TPlane& p)
{
	m_normal = p.m_normal;
	m_constant = p.m_constant;
	return *this;
}

//-------------------------------------------------------------------------------
inline const TVector3& TPlane::GetNormal() const
{
	return m_normal;
}

//-------------------------------------------------------------------------------
inline float TPlane::GetConstant() const
{
	return m_constant;
}

//-------------------------------------------------------------------------------
inline void TPlane::Set(float nx, float ny, float nz, float c)
{
	m_normal.x = nx;
	m_normal.y = ny;
	m_normal.z = nz;
	float len = m_normal.Normalize();
	m_constant = c / len;
}

//-------------------------------------------------------------------------------
inline void TPlane::Set(const TVector3& p0, const TVector3& p1, const TVector3& p2)
{
	m_normal = Normalize(CrossProduct(p2 - p0, p1 - p0));
	m_constant = -DotProduct(m_normal, p0);
}

//-------------------------------------------------------------------------------
inline void	TPlane::SetConstant(float constant)
{
	m_constant = constant;
}

//-------------------------------------------------------------------------------
inline float TPlane::Magnitude() const
{
	return sqrtf(MagnitudeSquared());
}

//-------------------------------------------------------------------------------
inline float TPlane::MagnitudeSquared() const
{
	return m_normal.x * m_normal.x + m_normal.y * m_normal.y + m_normal.z * m_normal.z;
}

//-------------------------------------------------------------------------------
inline TPlane Normalize(const TPlane& plane)
{
	float invMagnitude = 1.0f / plane.Magnitude();
	return TPlane(plane.GetNormal() * invMagnitude, plane.GetConstant() * invMagnitude);
}

//-------------------------------------------------------------------------------
inline bool TPlane::IsEqualTo(const TPlane& plane) const
{
	return FLT_EQ(m_normal.x, plane.m_normal.x) &&
		   FLT_EQ(m_normal.y, plane.m_normal.y) &&
		   FLT_EQ(m_normal.z, plane.m_normal.z) &&
		   FLT_EQ(m_constant, plane.m_constant);
}
