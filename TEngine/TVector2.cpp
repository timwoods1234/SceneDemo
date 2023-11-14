#include <stdio.h>

#include "TMath.h"
#include "TVector2.h"

//-------------------------------------------------------------------------------
TVector2::TVector2()
{
	// no initialization
}

//-------------------------------------------------------------------------------
const TVector2& TVector2::Zero()
{
	static TVector2 zero(0.f, 0.f);
	return zero;
}

//-------------------------------------------------------------------------------
const TVector2& TVector2::One()
{
	static TVector2 one(1.f, 1.f);
	return one;
}

//-------------------------------------------------------------------------------
TVector2& TVector2::operator/=(float s)
{
	float inv_s = 1.f / s;
	*this *= inv_s;
	return *this;
}

//-------------------------------------------------------------------------------
TVector2 TVector2::operator+(const TVector2& v) const
{
	return TVector2(x + v.x, y + v.y);
}

//-------------------------------------------------------------------------------
TVector2 TVector2::operator-(const TVector2& v) const
{
	return TVector2(x - v.x, y - v.y);
}

//-------------------------------------------------------------------------------
TVector2 TVector2::operator*(float s) const
{
	return TVector2(x*s, y*s);
}

//-------------------------------------------------------------------------------
TVector2 TVector2::operator*(const TVector2& v) const
{
	return TVector2(x * v.x, y * v.y);
}

//-------------------------------------------------------------------------------
TVector2 TVector2::operator/(float s) const
{
	return *this * (1.f / s);
}

//-------------------------------------------------------------------------------
TVector2 TVector2::operator-() const
{
	return TVector2(-x, -y);
}

//-------------------------------------------------------------------------------
bool TVector2::operator==(const TVector2& v) const
{
	return FLT_EQ(x, v.x) && FLT_EQ(y, v.y);
}

//-------------------------------------------------------------------------------
bool TVector2::operator!=(const TVector2& v) const
{
	return !operator==(v);
}

//-------------------------------------------------------------------------------
float& TVector2::operator[](unsigned int i)
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TVector2::operator[](unsigned int i) const
{
	return ((float*)this)[i];
}

//-------------------------------------------------------------------------------
float TVector2::GetSquaredLength() const
{
	return (x * x) + (y * y);
}

//-------------------------------------------------------------------------------
void TVector2::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

//-------------------------------------------------------------------------------
float TVector2::GetLength() const
{
	return sqrtf(GetSquaredLength());
}

//-------------------------------------------------------------------------------
float TVector2::Normalize()
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
bool TVector2::IsNormalized() const
{
	return FLT_EQ(GetSquaredLength(), 1.0f);
}

//-------------------------------------------------------------------------------
const char* TVector2::GetStr() const
{
	static char buf[1024];
	sprintf_s(buf, 1024, "%f, %f", x, y);
	return buf;
}

//-------------------------------------------------------------------------------
TVector2 Normalize(const TVector2& v)
{
	return v * (1.f / v.GetLength());
}

//-------------------------------------------------------------------------------
float DotProduct(const TVector2& a, const TVector2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}

//-------------------------------------------------------------------------------
float Distance(const TVector2& a, const TVector2& b)
{
	return (b - a).GetLength();
}

//-------------------------------------------------------------------------------
float SquaredDistance(const TVector2& a, const TVector2& b)
{
	return (b - a).GetSquaredLength();
}

//-------------------------------------------------------------------------------
TVector2 GetRandomVec2(unsigned int* seed, const TVector2& min, const TVector2& max)
{
	return TVector2(
		FastRandom(seed, min.x, max.x),
		FastRandom(seed, min.y, max.y));
}

//-------------------------------------------------------------------------------
TVector2 GetRandomUnitVec2(unsigned int* seed)
{
	return Normalize( TVector2(
			FastRandom(seed, -1.0f, 1.0f),
			FastRandom(seed, -1.0f, 1.0f) ));
}
