#include <stdio.h>

#include "TMath.h"
#include "TVector4.h"

//-------------------------------------------------------------------------------
TVector4::TVector4()
{
	// no initialization
}

//-------------------------------------------------------------------------------
const TVector4& TVector4::Zero()
{
	static TVector4 zero(0.f, 0.f, 0.f, 0.f);
	return zero;
}

//-------------------------------------------------------------------------------
const TVector4& TVector4::One()
{
	static TVector4 one(1.f, 1.f, 1.f, 1.f);
	return one;
}

//-------------------------------------------------------------------------------
TVector4& TVector4::operator/=(float s)
{
	float inv_s = 1.f / s;
	*this *= inv_s;
	return *this;
}

//-------------------------------------------------------------------------------
TVector4 TVector4::operator+(const TVector4& v) const
{
	return TVector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

//-------------------------------------------------------------------------------
TVector4 TVector4::operator-(const TVector4& v) const
{
	return TVector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

//-------------------------------------------------------------------------------
TVector4 TVector4::operator*(float s) const
{
	return TVector4(x*s, y*s, z*s, w*s);
}

//-------------------------------------------------------------------------------
TVector4 TVector4::operator*(const TVector4& v) const
{
	return TVector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

//-------------------------------------------------------------------------------
TVector4 TVector4::operator/(float s) const
{
	return *this * (1.f / s);
}

//-------------------------------------------------------------------------------
TVector4 TVector4::operator-() const
{
	return TVector4(-x, -y, -z, -w);
}

//-------------------------------------------------------------------------------
bool TVector4::operator==(const TVector4& v) const
{
	return FLT_EQ(x, v.x) && FLT_EQ(y, v.y) && FLT_EQ(z, v.z) && FLT_EQ(w, v.w);
}

//-------------------------------------------------------------------------------
bool TVector4::operator!=(const TVector4& v) const
{
	return !operator==(v);
}

//-------------------------------------------------------------------------------
float& TVector4::operator[](unsigned int i)
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TVector4::operator[](unsigned int i) const
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float& TVector4::operator[](int i)
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TVector4::operator[](int i) const
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TVector4::GetSquaredLength() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

//-------------------------------------------------------------------------------
void TVector4::Set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//-------------------------------------------------------------------------------
float TVector4::GetLength() const
{
	return sqrtf(GetSquaredLength());
}

//-------------------------------------------------------------------------------
float TVector4::Normalize()
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
bool TVector4::IsNormalized() const
{
	return FLT_EQ(GetSquaredLength(), 1.0f);
}

//-------------------------------------------------------------------------------
const char* TVector4::GetStr() const
{
	static char buf[1024];
	sprintf_s(buf, "%f, %f, %f, %f", x, y, z, w);
	return buf;
}

//-------------------------------------------------------------------------------
TVector4 Normalize(const TVector4& v)
{
	return v * (1.f / v.GetLength());
}

//-------------------------------------------------------------------------------
float DotProduct(const TVector4& a, const TVector4& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

//-------------------------------------------------------------------------------
float Distance(const TVector4& a, const TVector4& b)
{
	return (b - a).GetLength();
}

//-------------------------------------------------------------------------------
float SquaredDistance(const TVector4& a, const TVector4& b)
{
	return (b - a).GetSquaredLength();
}

//-------------------------------------------------------------------------------
TVector4 GetRandomVec4(unsigned int* seed, const TVector4& min, const TVector4& max)
{
	return TVector4(
		FastRandom(seed, min.x, max.x),
		FastRandom(seed, min.y, max.y),
		FastRandom(seed, min.z, max.z),
		FastRandom(seed, min.w, max.w));
}

//-------------------------------------------------------------------------------
TVector4 GetRandomUnitVec4(unsigned int* seed)
{
	return Normalize( TVector4(
			FastRandom(seed, -1.0f, 1.0f),
			FastRandom(seed, -1.0f, 1.0f),
			FastRandom(seed, -1.0f, 1.0f),
			FastRandom(seed, -1.0f, 1.0f) ));
}
