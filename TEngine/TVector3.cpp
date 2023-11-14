#include <stdio.h>

#include "TMath.h"
#include "TVector3.h"

//-------------------------------------------------------------------------------
TVector3::TVector3()
{
	// no initialization
}

//-------------------------------------------------------------------------------
const TVector3& TVector3::Zero()
{
	static TVector3 zero(0.f, 0.f, 0.f);
	return zero;
}

//-------------------------------------------------------------------------------
const TVector3& TVector3::One()
{
	static TVector3 one(1.f, 1.f, 1.f);
	return one;
}

//-------------------------------------------------------------------------------
TVector3& TVector3::operator/=(float s)
{
	float inv_s = 1.f / s;
	*this *= inv_s;
	return *this;
}

//-------------------------------------------------------------------------------
TVector3 TVector3::operator+(const TVector3& v) const
{
	return TVector3(x + v.x, y + v.y, z + v.z);
}

//-------------------------------------------------------------------------------
TVector3 TVector3::operator-(const TVector3& v) const
{
	return TVector3(x - v.x, y - v.y, z - v.z);
}

//-------------------------------------------------------------------------------
TVector3 TVector3::operator*(float s) const
{
	return TVector3(x*s, y*s, z*s);
}

//-------------------------------------------------------------------------------
TVector3 TVector3::operator*(const TVector3& v) const
{
	return TVector3(x * v.x, y * v.y, z * v.z);
}

//-------------------------------------------------------------------------------
TVector3 TVector3::operator/(float s) const
{
	return *this * (1.f / s);
}

//-------------------------------------------------------------------------------
TVector3 TVector3::operator-() const
{
	return TVector3(-x, -y, -z);
}

//-------------------------------------------------------------------------------
bool TVector3::operator==(const TVector3& v) const
{
	return FLT_EQ(x, v.x) && FLT_EQ(y, v.y) && FLT_EQ(z, v.z);
}

//-------------------------------------------------------------------------------
bool TVector3::operator!=(const TVector3& v) const
{
	return !operator==(v);
}

//-------------------------------------------------------------------------------
float& TVector3::operator[](unsigned int i)
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TVector3::operator[](unsigned int i) const
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TVector3::GetSquaredLength() const
{
	return (x * x) + (y * y) + (z * z);
}

//-------------------------------------------------------------------------------
void TVector3::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//-------------------------------------------------------------------------------
float TVector3::GetLength() const
{
	return sqrtf(GetSquaredLength());
}

//-------------------------------------------------------------------------------
float TVector3::Normalize()
{
	float length = GetLength();

	if (length == 0.0f)
	{
		return length;
	}

	*this *= (1.0f / length);
	return length;
}

//-------------------------------------------------------------------------------
bool TVector3::IsNormalized() const
{
	return FLT_EQ(GetSquaredLength(), 1.0f);
}

//-------------------------------------------------------------------------------
const char* TVector3::GetStr() const
{
	static char buf[1024];
	sprintf_s(buf, 1024, "%f, %f, %f", x, y, z);
	return buf;
}

//-------------------------------------------------------------------------------
TVector3 CalculateTriangleNormal(const TVector3& a, const TVector3& b, const TVector3& c)
{
	return Normalize(CrossProduct(b - a, c - a));
}

//-------------------------------------------------------------------------------
TVector3 Normalize(const TVector3& v)
{
	return v * (1.f / v.GetLength());
}

//-------------------------------------------------------------------------------
TVector3 CrossProduct(const TVector3& a, const TVector3& b)
{
	return TVector3(
			(a.y * b.z) - (a.z * b.y), 
			(a.z * b.x) - (a.x * b.z), 
			(a.x * b.y) - (a.y * b.x) );
}

//-------------------------------------------------------------------------------
float DotProduct(const TVector3& a, const TVector3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

//-------------------------------------------------------------------------------
float Distance(const TVector3& a, const TVector3& b)
{
	return (b - a).GetLength();
}

//-------------------------------------------------------------------------------
float SquaredDistance(const TVector3& a, const TVector3& b)
{
	return (b - a).GetSquaredLength();
}

//-------------------------------------------------------------------------------
TVector3 GetRandomVec3(unsigned int* seed, const TVector3& min, const TVector3& max)
{
	return TVector3(
		FastRandom(seed, min.x, max.x),
		FastRandom(seed, min.y, max.y),
		FastRandom(seed, min.z, max.z) );
}

//-------------------------------------------------------------------------------
TVector3 GetRandomUnitVec3(unsigned int* seed)
{
	return Normalize( TVector3(
			FastRandom(seed, -1.0f, 1.0f),
			FastRandom(seed, -1.0f, 1.0f),
			FastRandom(seed, -1.0f, 1.0f) ));
}

//-------------------------------------------------------------------------------
TVector3 GetPerpVector(const TVector3& v)
{
	return TVector3(-v.z, v.x, v.y);
}