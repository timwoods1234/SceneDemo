#ifndef __TMATH_H__
#include "TMath.h"
#endif

//-------------------------------------------------------------------------------
inline TQuaternion::TQuaternion()
{
}

//-------------------------------------------------------------------------------
inline TQuaternion::TQuaternion(float _w, float _x, float _y, float _z)
:	w(_w),
	x(_x),
	y(_y),
	z(_z)
{
}

//-------------------------------------------------------------------------------
inline TQuaternion::TQuaternion(const TQuaternion& q)
:	w(q.w),
	x(q.x),
	y(q.y),
	z(q.z)
{
}

//-------------------------------------------------------------------------------
inline float TQuaternion::GetW() const
{
	return w;
}

//-------------------------------------------------------------------------------
inline float TQuaternion::GetX() const
{
	return x;
}

//-------------------------------------------------------------------------------
inline float TQuaternion::GetY() const
{
	return y;
}

//-------------------------------------------------------------------------------
inline float TQuaternion::GetZ() const
{
	return z;
}

//-------------------------------------------------------------------------------
inline void TQuaternion::SetW(float _w)
{
	w = _w;
}

//-------------------------------------------------------------------------------
inline void TQuaternion::SetX(float _x)
{
	x = _x;
}

//-------------------------------------------------------------------------------
inline void TQuaternion::SetY(float _y)
{
	y = _y;
}

//-------------------------------------------------------------------------------
inline void TQuaternion::SetZ(float _z)
{
	z = _z;
}

//-------------------------------------------------------------------------------
inline TQuaternion& TQuaternion::operator=(const TQuaternion& q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

//-------------------------------------------------------------------------------
inline TQuaternion TQuaternion::operator+(const TQuaternion& q) const
{
	return TQuaternion(w + q.w,
						x + q.x,
						y + q.y,
						z + q.z);
}

//-------------------------------------------------------------------------------
inline TQuaternion TQuaternion::operator-(const TQuaternion& q) const
{
	return TQuaternion(w - q.w,
						x - q.x,
						y - q.y,
						z - q.z);
}

//-------------------------------------------------------------------------------
inline TQuaternion TQuaternion::operator-() const
{
	return TQuaternion(-w, -x, -y, -z);
}

//-------------------------------------------------------------------------------
inline TQuaternion TQuaternion::operator*(const TQuaternion& q) const
{
    return TQuaternion
    (
        w * q.w - x * q.x - y * q.y - z * q.z,
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y + y * q.w + z * q.x - x * q.z,
        w * q.z + z * q.w + x * q.y - y * q.x
    );
}

//-------------------------------------------------------------------------------
inline TQuaternion TQuaternion::operator*(float c) const
{
    return TQuaternion(w*c, x*c, y*c, z*c);
}

//-------------------------------------------------------------------------------
inline TQuaternion operator*(float scalar, const TQuaternion& q)
{
    return TQuaternion(scalar * q.w, scalar * q.x, scalar * q.y, scalar * q.z);
}

//-------------------------------------------------------------------------------
inline bool TQuaternion::operator==(const TQuaternion& q) const
{
    return FLT_EQ(w, q.w) &&
		   FLT_EQ(x, q.x) &&
		   FLT_EQ(y, q.y) &&
		   FLT_EQ(z, q.z);
}

//-------------------------------------------------------------------------------
inline bool TQuaternion::operator!=(const TQuaternion& q) const
{
    return !operator==(q);
}

//-------------------------------------------------------------------------------
inline float DotProduct(const TQuaternion& p, const TQuaternion& q)
{
	return p.w*q.w + p.x*q.x + p.y*q.y + p.z*q.z;
}

//-------------------------------------------------------------------------------
inline float TQuaternion::GetSquaredLength() const
{
	return w*w + x*x + y*y + z*z;
}

//-------------------------------------------------------------------------------
inline TQuaternion TQuaternion::UnitInverse() const
{
	return TQuaternion(w, -x, -y, -z);
}

//-------------------------------------------------------------------------------
inline float TQuaternion::GetLength() const
{
	return sqrtf(GetSquaredLength());
}

//-------------------------------------------------------------------------------
inline void TQuaternion::Normalize()
{
	float length = 	GetLength();
	*this = *this * (1.0f / length);
}
