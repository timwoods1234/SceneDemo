#ifndef __TVECTOR2_H__
#define __TVECTOR2_H__

class TVector2
{
public:
	static const TVector2& Zero();
	static const TVector2& One();

	TVector2();
	inline TVector2(const TVector2& v);
	inline TVector2(float _x, float _y);

	inline TVector2& operator=(const TVector2& v);
	inline TVector2& operator+=(const TVector2& v);
	inline TVector2& operator-=(const TVector2& v);
	inline TVector2& operator*=(const TVector2& v);
	inline TVector2& operator*=(float s);
	TVector2& operator/=(float s);
	TVector2 operator+(const TVector2& v) const;
	TVector2 operator-(const TVector2& v) const;
	TVector2 operator*(float s) const;
	TVector2 operator*(const TVector2& v) const;
	TVector2 operator/(float s) const;
	TVector2 operator-() const;
	bool operator==(const TVector2& v) const;
	bool operator!=(const TVector2& v) const;
	float& operator[](unsigned int i);
	float  operator[](unsigned int i) const;

	float GetLength() const;
	float GetSquaredLength() const;

	void Set(float x, float y);
	float Normalize();
	bool IsNormalized() const;

	float x;
	float y;

	const char* GetStr() const;		// string representation
};

TVector2	Rotate(const TVector2& v, float angle);
TVector2	Normalize(const TVector2& v);
float		DotProduct(const TVector2& a, const TVector2& b);
float		Distance(const TVector2& a, const TVector2& b);
float		SquaredDistance(const TVector2& a, const TVector2& b);
TVector2	GetRandomVec2(unsigned int* seed, const TVector2& min, const TVector2& max);
TVector2	GetRandomUnitVec2(unsigned int* seed);

#include "TVector2.inl"

#endif
